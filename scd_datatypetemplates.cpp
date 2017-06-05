#include "scd_datatypetemplates.h"


stLNodeType* DataTypeTemplates::findLNodeType(QString name)
{
    return this->mpLNodeType_.value(name,NULL);
}
stDOType* DataTypeTemplates::findDOType(QString name)
{
    return this->mpDOType_.value(name,NULL);
}
stDAType* DataTypeTemplates::findDAType(QString name)
{
    return this->mpDAType_.value(name,NULL);
}
stEnumType* DataTypeTemplates::findEnumType(QString name)
{
    return this->mpEnumType_.value(name,NULL);
}

stDO* LNodeType::findDO(QString n)
{
    return this->mpDO_.value(n,NULL);
}

stDA* DOType::findDA(QString name)
{
    return this->mpDA_.value(name,NULL);
}

QVector<stDA*>& DOType::getDA()
{
    return this->vtDA_;
}

stSDO* DOType::findSDO(QString name)
{
    return this->mpSDO_.value(name,NULL);
}
stBDA* DAType::findBDA(QString name)
{
    return this->mpBDA_.value(name,NULL);
}

stEnumVal* EnumType::findEnumVal(QString name)
{
    return this->mpEnumVal_.value(name,NULL);
}


void LNodeType::initDO(QDomElement &e)
{
    stDO *d = new stDO();

    d->desc_ = e.attribute("desc","");
    d->name_ = e.attribute("name","");
    d->type_ = e.attribute("type","");
    d->accessControl_ = e.attribute("accessControl","");
    d->transient_ = e.attribute("transient","");

    this->mpDO_.insert(d->name_,d);


}

void DataTypeTemplates::initLNodeType(QDomElement &e)
{
    stLNodeType* ln = new stLNodeType();

    ln->id_ = e.attribute("id","");
    ln->desc_ = e.attribute("desc","");
    ln->iedType_ = e.attribute("iedType","");
    ln->lnClass_ = e.attribute("lnClass","");

    this->mpLNodeType_.insert(ln->id_,ln);

    QDomNode n = e.firstChild();
    QDomElement tmp;
    while(!n.isNull())
    {
        tmp = n.toElement();

        if(tmp.tagName() == "DO")
        {
            ln->initDO(tmp);
        }

        n = n.nextSibling();
    }

}

void DOType::initDA(QDomElement &e)
{
    stDA* da = new stDA();

    da->desc_ = e.attribute("desc","");
    da->name_ = e.attribute("name","");
    da->sAddr_ = e.attribute("sAddr","");
    da->bType_ = e.attribute("bType","");
    da->valKind_ = e.attribute("valKind","");
    da->type_ = e.attribute("type","");
    da->count_ = e.attribute("count","");
    da->dchg_ = e.attribute("dchg","");
    da->qchg_ = e.attribute("qchg","");
    da->dupd_ = e.attribute("dupd","");
    da->fc_ = e.attribute("fc","");

    this->mpDA_.insert(da->name_,da);
	DoIndex doIndex;
	doIndex.key = da->name_;
	doIndex.labType = DALAB;
	this->vtIndex.push_back(doIndex);
    //this->vtDA_.append(da);
}

void DOType::initSDO(QDomElement &e)
{
    stSDO *sdo = new stSDO();

    sdo->desc_ = e.attribute("desc","");
    sdo->name_ = e.attribute("name","");
    sdo->type_ = e.attribute("type","");
	DoIndex doIndex;
	doIndex.key = sdo->name_;
	doIndex.labType = SDOLAB;
	this->vtIndex.push_back(doIndex);
    this->mpSDO_.insert(sdo->name_,sdo);

}

void DataTypeTemplates::initDOType(QDomElement &e)
{
    stDOType* d = new stDOType();
    d->id_ = e.attribute("id","");
    d->desc_ = e.attribute("desc","");
    d->iedType_ = e.attribute("iedType","");
    d->cdc_ = e.attribute("cdc","");


   this->mpDOType_.insert(d->id_,d);

    QDomNode n = e.firstChild();
    QDomElement tmp;
    while(!n.isNull())
    {
        tmp = n.toElement();

        if(tmp.tagName() == "SDO")
        {
            d->initSDO(tmp);

        }
        else
            if(tmp.tagName() == "DA")
            {
                d->initDA(tmp);
            }

        n = n.nextSibling();
    }



}

void DAType::initBDA(QDomElement &e)
{
    BDA* bda = new BDA();

    bda->desc_ = e.attribute("desc","");
    bda->name_ = e.attribute("name","");
    bda->sAddr_ = e.attribute("sAddr","");
    bda->bType_ = e.attribute("bType","");
    bda->valKind_ = e.attribute("valKind","");
    bda->type_ = e.attribute("type","");
    bda->count_ =e.attribute("count","");

    this->mpBDA_.insert(bda->name_,bda);

	this->vtBDA_.append(bda);


}

void DataTypeTemplates::initDAType(QDomElement &e)
{
    stDAType *da = new stDAType();

    da->desc_ = e.attribute("desc","");
    da->id_ = e.attribute("id","");
    da->iedType_ = e.attribute("iedType_","");

    this->mpDAType_.insert(da->id_,da);

    QDomNode n = e.firstChild();
    QDomElement tmp;
    while(!n.isNull())
    {
        tmp = n.toElement();

        if(tmp.tagName() == "BDA")
        {
            da->initBDA(tmp);
        }

        n = n.nextSibling();
    }



}

void EnumType::initEnumVal(QDomElement &e)
{
    stEnumVal* en = new stEnumVal();

    en->ord_ = e.attribute("ord","");
    en->desc_ = e.attribute("desc","");

    this->mpEnumVal_.insert(en->ord_,en);
}

void DataTypeTemplates::initEnumType(QDomElement &e)
{

    EnumType *en = new EnumType();

    en->desc_ = e.attribute("desc","");
    en->id_ = e.attribute("id","");

    this->mpEnumType_.insert(en->id_,en);

    QDomNode n = e.firstChild();
    QDomElement tmp;

    while(!n.isNull())
    {
        tmp = n.toElement();

        if(tmp.tagName() == "EnumVal")
        {
            en->initEnumVal(tmp);
        }

        n = n.nextSibling();
    }

}
