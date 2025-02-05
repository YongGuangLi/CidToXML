#include "cidtoxml.h"
#include "scd.h"
#include "scd_communication.h"
#include <QCoreApplication>
#include <QSettings>
#include <QDomDocument>
#include <QDomElement>
#include <QTextCodec>
#include <QMap>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <string>
#include <windows.h>
#include <fstream>
#include <iostream>

using namespace std;

CidToXML::CidToXML()
{
	isEnable_ = false;
}

CidToXML::~CidToXML()
{

}


int CidToXML::ConvertCid2XML(std::string csInitFile,std::string csCidFile,std::string& rsDocument,std::list<std::string> &lstErrors)
{     
	if(!SCD::instance()->init(csCidFile))
	{ 
		SCD::instance()->getErrorList(lstErrors);
		return -1;
	} 
	 
	if (!InitCfgFile(csInitFile))
	{  
		lstErrors.push_back("config file load failed\n");
		return -1;
	} 

	//do_da 
	//SCD::instance()->initDoiToAddress();  

	//data_da 
	SCD::instance()->initDataSetToAddress();
	 
	SCD::instance()->getErrorList(lstErrors);

	QList<QString> listRptCtrlBlk;
	SCD::instance()->getAllRptCtrlBlk(listRptCtrlBlk);

	QDomDocument document;  

	QString strHeader( "version=\"1.0\" encoding=\"GBK\"");  
	document.appendChild(document.createProcessingInstruction("xml", strHeader));  

	QDomElement ied_Ele;
	 
	if (ip.size() > 1)    //A网  B网都有
	{
		CreateIedNode(document, ied_Ele,QString(ip.at(0)), QString(ip.at(1)), QString("102"), QString("102"));
	}
	else if(ip.size() == 1) //只有A网  
	{
		CreateIedNode(document, ied_Ele,QString(ip.at(0)), QString(ip.at(0)), QString("102"), QString("102")); 
	}
	else
	{
		lstErrors.push_back("cid ip not find");
		return -1;
	}

	QDomElement rptGroup_Ele = document.createElement( "ReportGroup" );  
	rptGroup_Ele.setAttribute( "desc",QString::fromLocal8Bit("报告控制块名称列表"));   
	ied_Ele.appendChild( rptGroup_Ele );  

	for(int i = 0; i < listRptCtrlBlk.size(); ++i)
	{
		CreateRptCtrlBlkNode(document, rptGroup_Ele, QString(listRptCtrlBlk.at(i)));   
	}

	QDomElement tagList_Ele = document.createElement( "TagList" );  
	tagList_Ele.setAttribute( "desc", QString::fromLocal8Bit("采集点列表"));   
	ied_Ele.appendChild( tagList_Ele );  

 

	map<string,vector<string> >::iterator it2 = SCD::instance()->getDataSetToAddress().begin();
	int iCnt = 0;
	while(it2 != SCD::instance()->getDataSetToAddress().end())
	{
		for(int i = 0; i < it2->second.size(); i++)
		{ 
			QString value = QString::fromLocal8Bit(it2->second.at(i).c_str());
			qDebug()<<value;
			QString fc = value.split(":").at(1);
			QString Type = value.split(":").at(2);
			if(mapFilterFC_.count(fc.toStdString()) != 0 && mapFilterType_.count(Type.toStdString()) != 0)
			{  
				CreateOrderNode(document, tagList_Ele,
					QString::number(iCnt),										 		   //index
					QString(value.split(":").at(4)),									   //doname
					QString(value.split(":").at(0)).replace("myfc",fc),								       //point
					QString(value.split(":").at(3)),					                   //desc   
					QString(mapFilterType_[value.split(":").at(2).toStdString()].c_str()),
					QString(value.split(":").at(5)));    
				iCnt++;
			}  
		} 
		it2++;
	} 
	 
	QString src ; 
	QTextStream out(&src);
	document.save( out, 4);   
	rsDocument = src.toLocal8Bit().data(); 
	 
	SCD::close_singleton();
 
	return 0;
}


void CidToXML::CreateIedNode(QDomDocument& document, QDomElement& Ied_Ele, QString& ipA, QString& ipB, QString& portA, QString& portB)
{
	Ied_Ele = document.createElement( "ied" );  
	Ied_Ele.setAttribute( "ipA", ipA);  
	Ied_Ele.setAttribute( "ipB", ipB);  
	Ied_Ele.setAttribute( "portA", portA);  
	Ied_Ele.setAttribute( "portB", portB);  
	document.appendChild(Ied_Ele);   
}

void CidToXML::CreateRptCtrlBlkNode(QDomDocument& document, QDomElement& rptGroup_Ele, QString& name)
{
	QDomElement rptCtrlBlk_Ele = document.createElement( "Report_Control_Block" );  
	rptCtrlBlk_Ele.setAttribute( "name", name);   
	rptGroup_Ele.appendChild( rptCtrlBlk_Ele ); 
}

void CidToXML::CreateOrderNode(QDomDocument& document, QDomElement& tagList_Ele, QString& index, QString& doname,QString& point, QString& desc, QString& type, QString &lnInst)
{
	QDomElement order_Ele = document.createElement( "Order" );   
	order_Ele.setAttribute( "index", index);  
	if (isEnable_ && mapIED_Alias_.count(doname) == 1)
	{
		order_Ele.setAttribute( "doname", mapIED_Alias_[doname]);
	}
	else if (isEnable_ && mapIED_Alias_.count(doname) == 0)
	{
		order_Ele.setAttribute( "doname", doname + "#");
	}
	else
	{
		order_Ele.setAttribute( "doname", doname);
	}
	order_Ele.setAttribute( "point", point);    
	order_Ele.setAttribute( "desc", desc);    
	order_Ele.setAttribute( "type", type);  
	order_Ele.setAttribute( "lnInst", lnInst);    
	tagList_Ele.appendChild(order_Ele );  
}

bool CidToXML::InitCfgFile(std::string csInitFile)
{
	QFile file(QString::fromLocal8Bit(csInitFile.c_str()));

	if(file.open(QIODevice::ReadOnly))
	{
		QSettings *settings = new QSettings(QString::fromLocal8Bit(csInitFile.c_str()),QSettings::IniFormat,NULL); 
		if (settings != NULL)
		{ 
			settings->beginGroup("FC");
			QStringList FCkeys = settings->allKeys();
			for (int i = 0 ; i < FCkeys.size(); ++i)
			{
				if (settings->value(FCkeys.at(i)).toString() == "1")
				{
					mapFilterFC_[FCkeys.at(i).toStdString()] = settings->value(FCkeys.at(i)).toString().toStdString();
				} 
			} 
			settings->endGroup();

			settings->beginGroup("TYPE");
			QStringList TYPEkeys = settings->allKeys();
			for (int i = 0 ; i < TYPEkeys.size(); ++i)
			{ 
				mapFilterType_[TYPEkeys.at(i).toStdString()] = settings->value(TYPEkeys.at(i)).toString().toStdString(); 
			} 
			settings->endGroup();

			settings->beginGroup("ENABLE"); 
			if(settings->value("enable_i2").toInt())
			{
				isEnable_ = true;
			}
			settings->endGroup();

			settings->beginGroup("I2");
			QStringList AliasKeys = settings->allKeys();
			for (int i = 0 ; i < AliasKeys.size(); ++i)
			{ 
				mapIED_Alias_[AliasKeys.at(i)] = settings->value(AliasKeys.at(i)).toString(); 
			} 
			settings->endGroup();
			

			return true;
		}
		file.close();
	} 
	else
	{ 
		return false;
	}
}

  
extern "C" __declspec(dllexport) ICidToXML* CreateModule(void* pIService)
{
	CidToXML* pModule = new CidToXML();
	return pModule;
}

extern "C" __declspec(dllexport) void DeleteModule(ICidToXML* pModule)
{
	if(pModule == NULL)
		return ;
	delete (CidToXML*)pModule;
}
