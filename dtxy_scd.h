#ifndef DTXY_SCD_H
#define DTXY_SCD_H

#include <QString>
#include <QMap>
#include <QVector>






typedef struct Communication
{

}stCommunication;

typedef struct FCDA
{
    QString ldInst_;
    QString prefix_;
    QString lnClass_;
    QString lnInst_;
    QString doName_;
    QString daName_;
    QString fc_;
    QString ix_;


}stFCDA;

typedef struct FCCB
{
    QString ldInst_;
    QString prefix_;
    QString lnClass_;
    QString lnInst_;
    QString cbName_;
    QString daName_;
    QString fc_;
    QString mustUnderstand_;


}stFCCB;

typedef struct DataSet
{
    QString desc_;
    QString name_;

}stDataSet;

typedef struct ReportControl
{

}stReportControl;

typedef struct LogControl
{

}stLogControl;

typedef struct DOI
{

}stDOI;

typedef struct Inputs
{

}stInputs;

typedef struct Log
{

}stLog;

typedef struct GSEControl
{

}stGSEControl;

typedef struct SampledValueControl
{

}stSampledValueControl;

typedef struct SettingControl
{

}stSettingControl;

typedef struct SCLControl
{

}stSCLControl;

typedef struct LN
{
    QString desc_;
    QString lnType_;
    QString prefix_;
    QString lnClass_;
    QString inst_;

    QMap<QString,stDataSet*> mpDataSet_;
    QMap<QString,stReportControl*> mpReportControl_;

}stLN;



typedef struct LDevice
{
    QString desc_;
    QString inst_;
    QString ldName_;

    stLN *LN0_;

    QVector<stLN*> vtLN_;

}stLDevice;


typedef struct Authentication
{

}stAuthentication;



typedef struct Server
{
    QString desc_;
    QString timeout_;

    stAuthentication Authentication_;
    QMap<QString,stLDevice*> mpLDevice_;

}stServer;

typedef struct AccessPoint
{
    QString desc_;
    QString name_;
    QString router_;
    QString clock_;

    stServer Server_;

}stAccessPoint;


typedef struct ConfDataSet
{
    int max_;
    int maxAttributes_;

}stConfDataSet;

typedef struct Services
{
    stConfDataSet ConfDataSet_;

}stServices;

typedef struct IED
{
  QString desc_;
  QString name_;
  QString type_;
  QString manufacturer_;
  QString configVersion_;
  QString originalSclVersion_;
  QString originalSclRevision_;
  QString engRight_;
  QString owner_;


  stServices Services_;

  QMap<QString,stAccessPoint*> mpAccessPoint_;

}stIED;


class DTXY_Scd
{
public:
    DTXY_Scd();
};

#endif // DTXY_SCD_H
