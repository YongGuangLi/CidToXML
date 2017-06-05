#ifndef SCD_DATATYPETEMPLATES_H
#define SCD_DATATYPETEMPLATES_H

#include <QString>
#include <QMap>

#include <QtXml>


typedef struct DO
{
    QString desc_;
    QString name_;
    QString type_;
    QString accessControl_;
    QString transient_;

}stDO;

typedef struct LNodeType
{
    QString id_;
    QString desc_;
    QString iedType_;
    QString lnClass_;
    QMap<QString,stDO*> mpDO_;

    stDO* findDO(QString n);

    void initDO(QDomElement &e);

}stLNodeType;

typedef struct DA
{
    QString desc_;
    QString name_;
    QString sAddr_;
    QString bType_;
    QString valKind_;
    QString type_;
    QString count_;
    QString dchg_;
    QString qchg_;
    QString dupd_;
    QString fc_;

}stDA;

typedef struct SDO
{
    QString desc_;
    QString name_;
    QString type_;

}stSDO;


typedef struct DOType
{
    QString id_;
    QString desc_;
    QString iedType_;
    QString cdc_;
	enum LabType
	{
		DALAB,
		SDOLAB
	};
	struct DoIndex
	{
		QString key;
		LabType labType;
	};

    QMap<QString,stDA*> mpDA_;

    QVector<stDA*> vtDA_;
	QVector<DoIndex> vtIndex;

    QMap<QString,stSDO*> mpSDO_;

    stDA* findDA(QString name);
    stSDO* findSDO(QString name);

    QVector<stDA*>& getDA();

    void initDA(QDomElement &e);
    void initSDO(QDomElement &e);

}stDOType;

typedef struct BDA
{
    QString desc_;
    QString name_;
    QString sAddr_;
    QString bType_;
    QString valKind_;
    QString type_;
    QString count_;

}stBDA;

typedef struct DAType
{
    QString id_;
    QString desc_;
    QString iedType_;
    QMap<QString,stBDA*> mpBDA_;

	QVector<stBDA*> vtBDA_;

    stBDA* findBDA(QString name);

    void initBDA(QDomElement &e);

}stDAType;

typedef struct EnumVal
{
    QString ord_;
    QString desc_;

}stEnumVal;

typedef struct EnumType
{
    QString id_;
    QString desc_;
    QMap<QString,stEnumVal*> mpEnumVal_;
    stEnumVal* findEnumVal(QString name);

    void initEnumVal(QDomElement &e);

}stEnumType;


typedef struct DataTypeTemplates
{
    QMap<QString,stLNodeType*> mpLNodeType_;
    QMap<QString,stDOType*> mpDOType_;
    QMap<QString,stDAType*> mpDAType_;
    QMap<QString,stEnumType*> mpEnumType_;

    stLNodeType* findLNodeType(QString name);
    stDOType* findDOType(QString name);
    stDAType* findDAType(QString name);
    stEnumType* findEnumType(QString name);

    void initLNodeType(QDomElement &e);
    void initDOType(QDomElement &e);
    void initDAType(QDomElement &e);
    void initEnumType(QDomElement &e);

}stDataTypeTemplates;

#endif // SCD_DATATYPETEMPLATES_H
