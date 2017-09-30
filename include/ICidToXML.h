#pragma once
#include <string>
#include <map>
#include <list>

class ICidToXML
{
public:
	virtual int ConvertCid2XML(std::string csInitFile,std::string csCidFile,std::string& rsDocument,std::list<std::string> &lstErrors) = 0;
};

#ifdef CIDTOXML_EXPORTS
#	define CIDTOXML_API __declspec(dllexport)
#else
#	define CIDTOXML_API __declspec(dllimport)
#endif

extern "C"
{
	__declspec(dllexport) ICidToXML* CreateModule(void* pIService);
	__declspec(dllexport)  void DeleteModule(ICidToXML* pModule);
}

 


 

