#ifndef CIDTOXML_H
#define CIDTOXML_H

#ifdef CIDTOXML_LIB
# define CIDTOXML_EXPORT __declspec(dllexport)
#else
# define CIDTOXML_EXPORT __declspec(dllimport)
#endif

#include "../include/ICidToXML.h"
#include <string>
#include <map>
#include <list>

class QDomDocument;
class QDomElement;
class QString;

using namespace std;





class  CidToXML : public ICidToXML
{
public: 
	CidToXML();
	~CidToXML(); 
	//加载cid文件
	int ConvertCid2XML(std::string csInitFile,std::string csCidFile,std::string& rsDocument,std::list<std::string> &lstErrors);
private:
	//生成ied节点
	void CreateIedNode(QDomDocument& document, QDomElement& Ied_Ele, QString& ipA, QString& ipB, QString& portA, QString& portB);
	
	//生成Report_Control_Block节点
	void CreateRptCtrlBlkNode(QDomDocument& document, QDomElement& rptGroup_Ele, QString& name);
	
	//生成Order节点
	void CreateOrderNode(QDomDocument& document, QDomElement& tagList_Ele, QString& index, QString& doname, QString& point, QString& desc, QString& type);
	
	//读取配置文件
	bool InitCfgFile(std::string csInitFile);
	
	//按照功能约束过滤,在配置文件中设置
	/*
		MX=0
		ST=1
		CO=2 
		EX=2
		SV=2
		CF=2
		DC=2
	*/
	map<string,string> mapFilterFC_;
	
	map<string,string> mapFilterType_;
};
 
#endif // CIDTOXML_H
