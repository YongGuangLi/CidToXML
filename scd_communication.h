#ifndef SCD_COMMUNICATION_H
#define SCD_COMMUNICATION_H



#include <QtCore>
#include <QtXml>


extern QList<QString> ip; 

typedef struct Address
{
    QMap<QString,QString> mpAddress_;
    static Address* InitAddress(QDomElement &e);

    void dump();
	void getAllIedAddress(QList<QString> &listIp);
}stAddress;

typedef struct MinTime
{
    QString unit_;
    QString multiplier_;
    QString value_;

    void dump();

}stMinTime;

typedef struct MaxTime
{
    QString unit_;
    QString multiplier_;
    QString value_;

    void dump();

}stMaxTime;



typedef struct GSE
{
    QString desc_;
    QString ldInst_;
    QString cbName_;

    stAddress *address_;

    stMinTime *minTime_;

    stMaxTime *maxTime_;

    void initAddress(QDomElement &e);

    void initMinTime(QDomElement &e);

    void initMaxTime(QDomElement &e);

    void dump();

}stGSE;


typedef struct SMV
{
    QString desc_;
    QString ldInst_;
    QString cbName_;

    stAddress *address_;

    void initAddress(QDomElement &e);

    void dump();

}stSMV;



typedef struct ConnectedAP
{
    QString desc_;
    QString iedName_;
    QString apName_;

    stAddress* address_;

    QVector<stGSE*> vtGSE_;

    QVector<stSMV*> vtSMV_;

    void initAddress(QDomElement &e);

    void initGSE(QDomElement &e);

    void initSMV(QDomElement &e);

    void initPhysConn(QDomElement &e);

    void dump();
	void getAllIedAddress(QList<QString> &listIp);
}stConnectedAP;

typedef struct BitRate
{
    QString unit_;
    QString multiplier_;
    QString value_;

    void dump();
}stBitRate;

typedef struct SubNetwork
{
    QString name_;
    QString desc_;
    QString type_;

    void initConnectedAP(QDomElement &e);

    void initBitRate(QDomElement &e);

    QMap<QString,stConnectedAP*> mpConnectedAP_;

    stBitRate *pBitRate_;

    SubNetwork()
    {
        pBitRate_ = NULL;
    }

    void dump();
	void getAllIedAddress(QList<QString> &listIp);
}stSubNetwork;


typedef struct Communication
{
  QString desc_;

  QMap<QString,stSubNetwork*> mpSubNetwork_;

  void initSubNetwork(QDomElement &e);

  void dump();
  void getAllIedAddress(QList<QString> &listIp);
}stCommunication;



#endif // SCD_IED_H
