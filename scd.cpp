#include "scd.h"
#include "scd_datatypetemplates.h"
#include "scd_ied.h"
#include "scd_Communication.h"

#include <QtCore>
#include <QtXml>


SCD* SCD::instance_ = NULL;


SCD::SCD()
{
    instance_ = NULL;
}

SCD::~SCD()
{

}


SCD* SCD::instance()
{
    if(NULL == SCD::instance_)
    {
        SCD::instance_ = new SCD();
    }

    return SCD::instance_;
}

void SCD::close_singleton()
{
    if(instance_ != NULL)
    {
        delete instance_;

        instance_ = NULL;
    }
}

DataTypeTemplates* SCD::getDataTypeTemplates()
{
    return this->dataTypeTemplates_;
}

bool SCD::init(string &filename)
{
    QFile file(QString::fromLocal8Bit(filename.c_str()));
 
    if(file.open(QIODevice::ReadOnly))
    {
        QDomDocument doc;
        doc.setContent(&file);
        QDomElement root = doc.documentElement();

        QDomNode node = root.firstChild();
        QString tagName;

        while(!node.isNull())
        {
            QDomElement e = node.toElement();
            tagName = e.tagName();

            if(tagName == QString("Header"))
            {
                this->initHeader(e);
            }
            else if(tagName == QString("Communication"))
			{
				this->initCommunication(e);
			}
			else if(tagName == QString("IED"))
			{
				this->initIED(e);            
			}
			else if(tagName == QString("DataTypeTemplates"))
			{
				this->initDataTypeTemplates(e);
			}

            node = node.nextSibling();
        } 
    }
    else
    {
		listErrorInfo.push_back("cid file not find"); 
        return false;
    }

	file.close(); 
	return true;
}

//数据集
void SCD::initDataSetToAddress()
{
    #define KEY_NAME    ("%1/%2$%3")

    IED* pIed = NULL;
    QString name;

    map<string,IED*>::iterator it;

    map<string,vector<string> > tmp;

    for(it=mpIED_.begin(); it != mpIED_.end();++it)
    {

        name = QString::fromStdString(it->first);
        //qDebug()<<"IED "<<name<<"begin. "<<endl;

        pIed = it->second;
        tmp = pIed->initDataSetToAddress();

        this->mpDataSetToDa_.insert(tmp.begin(),tmp.end());

        
    }


}

//我改1 DOI，由于SCD的问题，DOI解析定义的类型
void SCD::initDoiToAddress()
{ 
    IED* pIed = NULL; 
    map<string,IED*>::iterator it;

    map<QString,vector<string> > tmp;

    for(it=mpIED_.begin(); it != mpIED_.end();++it)
    {  
        pIed = it->second;
        tmp = pIed->initDoiToAddress();

        this->mpDoiToDa_.insert(tmp.begin(),tmp.end()); 
    }  
}

void SCD::getAllRptCtrlBlk(QList<QString> &listRptCtrlBlk)
{  
	IED* pIed = NULL;  
	map<string,IED*>::iterator it;  

	for(it=mpIED_.begin(); it != mpIED_.end();++it)
	{ 
		pIed = it->second; 
		QString rptName("%1%2/%3$RP$%4");
		pIed->getAllRptCtrlBlk(listRptCtrlBlk,rptName); 
	}
}

void SCD::getAllIedAddress(QList<QString> &listIp)
{
	this->communication_->getAllIedAddress(listIp);
}

void SCD::getErrorList(list<string> &listError)
{ 
	listError = listErrorInfo;
}

map<string,vector<string> >& SCD::getDataSetToAddress()
{
    return this->mpDataSetToDa_;
}

map<QString,vector<string> >& SCD::getDoiToAddress()
{
    return this->mpDoiToDa_;
}


#if 0


 std::map<std::string,std::vector<std::string> >&
         SCD::init(std::string filename)
 {
    QString name(filename.c_str());
    QFile file(name);

    if(file.open(QIODevice::ReadOnly))
    {
        QDomDocument doc;
        doc.setContent(&file);
        QDomElement root = doc.documentElement();

        QDomNode node = root.firstChild();
        QString tagName;

        while(!node.isNull())
        {
            QDomElement e = node.toElement();
            tagName = e.tagName();

            if(tagName == QString("Header"))
            {
                 qDebug()<<"begin handler Header... \n ";

                this->initHeader(e);

                qDebug()<<"end handler Header... \n ";
            }
            else
                if(tagName == QString("Communication"))
                {

                    qDebug()<<"begin handler initCommunication... \n ";

                    this->initCommunication(e);

                   qDebug()<<"end handler initCommunication... \n ";
                }
                else
                    if(tagName == QString("IED"))
                    {

                        qDebug()<<"begin handler initIED... \n ";

                        this->initIED(e);

                       qDebug()<<"end handler initIED... \n ";

                    }
                    else
                        if(tagName == QString("DataTypeTemplates"))
                        {

                            qDebug()<<"begin handler initDataTypeTemplates... \n ";

                           this->initDataTypeTemplates(e);

                           qDebug()<<"end handler initDataTypeTemplates... \n ";
                        }

            node = node.nextSibling();
        }

    }
    else
    {
        qDebug()<<"scd file is  open faild.\n ";
    }

   return mpDataSetToDa_;
 }
#endif



 void SCD::initHeader(QDomElement& /*e*/)
 {

 }
 void SCD::initSubstation(QDomElement& /*e*/)
 {

 }
 void SCD::initCommunication(QDomElement& e)
 {
     stCommunication* comm = new stCommunication();

     comm->desc_ = e.attribute("desc","");

     QDomNode n = e.firstChild();
     QDomElement tmp;
     QString name;
     while(!n.isNull())
     {
         tmp = n.toElement();
         name = tmp.tagName();

         if(name == "SubNetwork")
         {
             comm->initSubNetwork(tmp); 
         }

         n = n.nextSibling();
     }

 }

 void SCD::initIED(QDomElement& e)
 {
    stIED* ied = new stIED();

    ied->desc_ = e.attribute("desc","");
    ied->name_ = e.attribute("name","");
    ied->type_ = e.attribute("type","");
    ied->manufacturer_ = e.attribute("manufacturer","");
    ied->configVersion_ = e.attribute("configVersion","");
    ied->originalSclVersion_ = e.attribute("orignalSclVersion","");
    ied->originalSclRevision_ = e.attribute("originalSclRevision","");
    ied->engRight_ = e.attribute("engRight","");
    ied->owner_ = e.attribute("owner","");

    this->mpIED_.insert(map<string,stIED*>
                        ::value_type(ied->name_.toStdString(),ied));


    QDomNode n = e.firstChild();
    QDomElement tmp;
    QString name;
    while(!n.isNull())
    {
        tmp = n.toElement();
        name = tmp.tagName();

        if(name == "Services")
        {
            ied->initServices(tmp);
        }
        else if(name == "AccessPoint")
        {
            ied->initAccessPoint(tmp);
        }

        n = n.nextSibling();
    }


 }

 void SCD::initDataTypeTemplates(QDomElement& e)
 {
    dataTypeTemplates_ = new DataTypeTemplates();

    QDomNode n = e.firstChild();
    QDomElement tmp;
    QString name;
    while(!n.isNull())
    {
        tmp = n.toElement();
        name = tmp.tagName();

        if(name == "LNodeType")
        {
            dataTypeTemplates_->initLNodeType(tmp);
        }
        else if(name == "DOType")
        {
            dataTypeTemplates_->initDOType(tmp);
        }
        else if(name == "DAType")
		{
			dataTypeTemplates_->initDAType(tmp);
		}
		else if(name == "EnumType")
		{
			dataTypeTemplates_->initEnumType(tmp);
		}

        n = n.nextSibling();
    }

 }
