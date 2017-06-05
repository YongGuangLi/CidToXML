#include "scd.h"
#include "scd_datatypetemplates.h"
#include "scd_ied.h"
#include "scd_Communication.h"

#include <QtCore>
#include <QtXml>

#if 0

SCD::SCD()
{

}



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
        else
            if(name == "AccessPoint")
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
        else
            if(name == "DOType")
            {
                dataTypeTemplates_->initDOType(tmp);
            }
            else
                if(name == "DAType")
                {
                    dataTypeTemplates_->initDAType(tmp);
                }
                else
                    if(name == "EnumType")
                    {
                        dataTypeTemplates_->initEnumType(tmp);
                    }

                n = n.nextSibling();
    }

 }
#endif
