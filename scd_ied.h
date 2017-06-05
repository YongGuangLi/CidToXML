#ifndef SCD_IED_H
#define SCD_IED_H



#include <QtCore>
#include <QtXml>

#include <map>
#include <vector>
#include <string>
#include <list>

using namespace std;

extern list<string> listErrorInfo;

struct IED;
struct AccessPoint;
struct Server;
struct LDevice;
struct LN;
struct DataSet;


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

    QString getGlobalName(QString name);

    QStringList getGlobalNames();

    IED* getIed();

    AccessPoint* getAccessPoint();

    Server* getServer();

    LDevice* getLDevice();

    DataSet* dataSet_;

    FCDA(DataSet* p)
    {
        dataSet_ = p;
    }



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

struct LN;

typedef struct DataSet
{
    QString desc_;
    QString name_;


    QVector<stFCDA*> vtFCDA_;
    QVector<stFCCB*> vtFCCB_;

    LN* LN_;

    void initFCDA(QDomElement &e);
    void initFCCB(QDomElement &e);

    map<string,vector<string> >& initDataSetToAddress();

    map<string,vector<string> > mpDataSetToAddress_;

    DataSet(LN* p)
    {
        LN_ = p;
    }

}stDataSet;

typedef struct TrgOps
{
    QString dchg_;
    QString qchg_;
    QString dupd_;
    QString period_;
    QString gi_;
    QString includeAll_;

}stTrgOps;

typedef struct OptFields
{
    QString seqNum_;
    QString timeStamp_;
    QString dataSet_;
    QString reasonCode_;
    QString dataRef_;
    QString entryID_;
    QString configRef_;
    QString bufOvfl_;
    QString segmentation_;
}stOptFields;


typedef struct ClientLN
{
    QString desc_;
    QString iedName_;
    QString ldInst_;
    QString prefix_;
    QString lnClass_;
    QString lnInst_;

}stClientLN;



typedef struct RptEnabled
{
    QString desc_;
    QString max_;

    QVector<stClientLN*> vtClientLN_;

    void initClientLN(QDomElement &e);

}stRptEnabled;

typedef struct ReportControl
{
    QString desc_;
    QString name_;
    QString datSet_;
    QString intgPd_;
    QString rptID_;
    QString confRev_;
    QString buffered_;
    QString bufTime_;
    QString indexed_;

    stTrgOps *pTrgOps_;
    stOptFields *pOptFields_;
    stRptEnabled *pRptEnabled_;

    void initTrgOps(QDomElement &e);

    void initOptFields(QDomElement &e);

    void initRptEnabled(QDomElement &e);

}stReportControl;

typedef struct LogControl
{
    QString desc_;
    QString name_;
    QString datSet_;
    QString intgPd_;
    QString ldInst_;
    QString prefix_;
    QString lnClass_;
    QString lnInst_;
    QString logName_;
    QString logEna_;
    QString reasonCode_;


    stTrgOps* pTrgOps_;

    void initTrgOps(QDomElement &e);


}stLogControl;

typedef struct Val
{
    QString sGroup_;
    QString val_;

}stVal;

typedef struct DAI
{
    QString desc_;
    QString name_;
    QString sAddr_;
    QString valKind_;
    QString ix_;

    QVector<stVal*> vtVal_;

    void initVal(QDomElement &e);

}stDAI;

typedef struct SDI
{
    QString desc_;
    QString name_;
    QString ix_;

    QMap<QString,SDI*> mpSDI_;
    QMap<QString,DAI*> mpDAI_;

}stSDI;



typedef struct DOI
{
    QString desc_;
    QString name_;
    QString ix_;
    QString accessControl_;

    QMap<QString,stSDI*> mpSDI_;
    QMap<QString,stDAI*> mpDAI_;

	LN* LN_;

    void initSDI(QDomElement &e);

    void initDAI(QDomElement &e);

	map<QString,vector<string> >& initDoiToAddress();

    map<QString,vector<string> > mpDoiToAddress_;

	DOI(LN* p)
    {
        LN_ = p;
    }

}stDOI;

typedef struct ExtRef
{
    QString desc_;
    QString iedName_;
    QString ldInst_;
    QString prefix_;
    QString lnClass_;
    QString lnInst_;
    QString doName_;
    QString daName_;
    QString intAddr_;

}stExtRef;

typedef struct Inputs
{
    QString desc_;

    QVector<stExtRef*> vtExtRef_;

    void initExtRef(QDomElement &e);

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

struct LDevice;

typedef struct LN
{
    QString desc_;
    QString lnType_;
    QString prefix_;
    QString lnClass_;
    QString inst_;

    QMap<QString,stDOI*> mpDOI_;
    QMap<QString,stDataSet*> mpDataSet_;
    QMap<QString,stReportControl*> mpReportControl_;
    QMap<QString,stLogControl*> mpLogControl_;

    stInputs *pInputs_;

    void initDataSet(QDomElement &e);
    void initReportControl(QDomElement &e);
    void initLogControl(QDomElement &e);
    void initDOI(QDomElement &e);
    void initInputs(QDomElement &e);
    void initLog(QDomElement &e);

    LDevice *LDevice_;

    map<string,vector<string> >& initDataSetToAddress();

    map<string,vector<string> > mpDataSetToAddress_;

	map<QString,vector<string> >& initDoiToAddress();

    map<QString,vector<string> > mpDoiToAddress_;

    LN(LDevice* p)
    {
        LDevice_ = p;
    }
	void getAllRptCtrlBlk(QList<QString> &listRptCtrlBlk, QString rptName);
}stLN;

struct Server;

typedef struct LDevice
{
    QString desc_;
    QString inst_;
    QString ldName_;

    stLN *LN0_;

    Server *Server_;

    QVector<stLN*> vtLN_;

    void initLN0(QDomElement &e);
    void initLN(QDomElement &e);

    map<string,vector<string> >& initDataSetToAddress();

    map<string,vector<string> > mpDataSetToAddress_;

	map<QString,vector<string> >& initDoiToAddress();

    map<QString,vector<string> > mpDoiToAddress_;

    stLN* getLN(QString prefix,QString lnClass,QString inst);



    LDevice(Server* p)
    {
        Server_ =p;
    }

	void getAllRptCtrlBlk(QList<QString> &listRptCtrlBlk, QString rptName);
}stLDevice;


typedef struct Authentication
{

}stAuthentication;


struct AccessPoint;

typedef struct Server
{
    QString desc_;
    QString timeout_;

    stAuthentication Authentication_;
    QMap<QString,stLDevice*> mpLDevice_;

    void initAuthentication(QDomElement &e);
    void initLDevice(QDomElement &e);

    map<string,vector<string> >& initDataSetToAddress();

    map<string,vector<string> > mpDataSetToAddress_;

	map<QString,vector<string> >& initDoiToAddress();

    map<QString,vector<string> > mpDoiToAddress_;

    AccessPoint *AccessPoint_;

    stLDevice* getLDevice(QString &name);

    Server(AccessPoint* p)
    {
        AccessPoint_ = p;
    }

	void getAllRptCtrlBlk(QList<QString> &listRptCtrlBlk, QString rptName);
}stServer;


struct IED;

typedef struct AccessPoint
{
    QString desc_;
    QString name_;
    QString router_;
    QString clock_;

    stServer *Server_;

    void initServer(QDomElement &e);

    map<string,vector<string> >& initDataSetToAddress();

    map<string,vector<string> > mpDataSetToAddress_;

	map<QString,vector<string> >& initDoiToAddress();

    map<QString,vector<string> > mpDoiToAddress_;

    IED* IED_;

    AccessPoint(IED* p)
    {
        IED_ = p;
    }

	void getAllRptCtrlBlk(QList<QString> &listRptCtrlBlk, QString rptName);

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

  void initServices(QDomElement &e);
  void initAccessPoint(QDomElement &e);
  map<string,vector<string> >& initDataSetToAddress();

  map<string,vector<string> > mpDataSetToAddress_;
  map<QString,vector<string> >& initDoiToAddress();

  map<QString,vector<string> > mpDoiToAddress_;

  //数据集TO成员

  void getAllRptCtrlBlk(QList<QString> &listRptCtrlBlk, QString rptName);

}stIED;



#endif // SCD_IED_H
