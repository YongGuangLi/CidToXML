#ifndef SCD_INTERFACE_H
#define SCD_INTERFACE_H

#include <string>
#include <vector>
#include <map>


class SCD_Interface
{
public:
     SCD_Interface();
     ~SCD_Interface();
}



#if 0

struct Header;
struct Substation;
struct Communication;
struct IED;
struct DataTypeTemplates;

class SCD
{
public:
    SCD();

    std::map<std::string,std::vector<std::string> >& init(std::string filename);

private:
    Header *header_;
    QMap<QString,Substation*> mpSubstation_;
    Communication *communication_;
    QMap<QString,IED*> mpIED_;
    DataTypeTemplates *dataTypeTemplates_;

    bool init_;

    std::map<std::string,std::vector<std::string> > mpDataSetToDa_;

private:
    void initHeader(QDomElement& e);
    void initSubstation(QDomElement& e);
    void initCommunication(QDomElement& e);
    void initIED(QDomElement& e);
    void initDataTypeTemplates(QDomElement& e);


};
#endif




#endif // SCD_H
