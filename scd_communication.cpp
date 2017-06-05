#include "scd_Communication.h"

#include <QtCore>
#include <QtXml>

QList<QString> ip; 
 

void SubNetwork::initConnectedAP(QDomElement &e)
{
    stConnectedAP *p = new stConnectedAP();
    p->desc_ = e.attribute("desc","");
    p->iedName_ = e.attribute("iedName","");
    p->apName_ = e.attribute("apName","");

    this->mpConnectedAP_.insert(p->iedName_,p);

    QDomNode n = e.firstChild();
    QDomElement tmp;
    QString name;

    while(!n.isNull())
    {
        tmp = n.toElement();
        name = tmp.tagName();

        if(name == "Address")
        {
            p->initAddress(tmp);
        }
        else if(name == "GSE")
		{
			p->initGSE(tmp);
		}
		else if(name == "SMV")
		{
			p->initSMV(tmp);
		}
		else if(name == "PhysConn")
		{
			p->initPhysConn(tmp);
		} 
        n = n.nextSibling();
    }  
}


void SubNetwork::getAllIedAddress(QList<QString> &listIp)
{
	 QMap<QString,stConnectedAP*>::Iterator it;
	 for (it = mpConnectedAP_.begin(); it != mpConnectedAP_.end(); ++it)
	 {
		 it.value()->getAllIedAddress(listIp);
	 }
}

void stConnectedAP::initPhysConn(QDomElement &/*e*/)
{

}

void stSubNetwork::initBitRate(QDomElement &/*e*/)
{

}

void Communication::initSubNetwork(QDomElement &e)
{
    stSubNetwork* p = new stSubNetwork();

    p->desc_ = e.attribute("desc","");
    p->name_ = e.attribute("name","");
    p->type_ = e.attribute("type","");

    this->mpSubNetwork_.insert(p->name_,p);

    QDomNode n = e.firstChild();
    QDomElement tmp;
    QString name;

    while(!n.isNull())
    {
        tmp = n.toElement();
        name = tmp.tagName();

        if(name == "ConnectedAP")
        {
            p->initConnectedAP(tmp);
        }
        else if(name == "BitRate")
        {
            p->initBitRate(tmp);
        }

        n = n.nextSibling();
    }
}

void Communication::getAllIedAddress(QList<QString> &listIp)
{

}

void stSMV::initAddress(QDomElement &e)
{
    this->address_ = stAddress::InitAddress(e);
}

void stConnectedAP::initSMV(QDomElement &e)
{
    stSMV *p = new stSMV();

    p->cbName_ = e.attribute("cbName","");
    p->desc_ = e.attribute("desc","");
    p->ldInst_ = e.attribute("ldInst","");

   this->vtSMV_.append(p);

   QDomNode n = e.firstChild();
   QDomElement tmp;
   QString name;

   while(!n.isNull())
   {
       tmp = n.toElement();
       name = tmp.tagName();

       if(name == "Address")
       {
           p->initAddress(tmp);
       }


       n = n.nextSibling();
   }


}

void stConnectedAP::initGSE(QDomElement &e)
{
  stGSE* p = new stGSE();

  p->desc_ = e.attribute("desc","");
  p->ldInst_ = e.attribute("ldInst","");
  p->cbName_ = e.attribute("cbName","");

  this->vtGSE_.append(p);

  QDomNode n = e.firstChild();
  QDomElement tmp;
  QString name;

  while(!n.isNull())
  {
      tmp = n.toElement();
      name = tmp.tagName();

      if(name == "Address")
      {
          p->initAddress(tmp);
      }
      else
          if(name == "MinTime")
          {
             p->initMinTime(tmp);
          }
          else
              if(name == "MaxTime")
              {
                p->initMaxTime(tmp);
              }

      n = n.nextSibling();
  }

}

void stGSE::initAddress(QDomElement &e)
{
    this->address_ = stAddress::InitAddress(e);
}

void stGSE::initMinTime(QDomElement &e)
{
    stMinTime* p= new stMinTime();

    p->unit_ =  e.attribute("unit","");
    p->multiplier_ = e.attribute("multiplier","");

    p->value_ = e.nodeValue();

    this->minTime_ = p;
}

void stGSE::initMaxTime(QDomElement &e)
{
    stMaxTime* p= new stMaxTime();

    p->unit_ =  e.attribute("unit","");
    p->multiplier_ = e.attribute("multiplier","");

    p->value_ = e.nodeValue();

    this->maxTime_ = p;
}

void stConnectedAP::initAddress(QDomElement &e)
{
    this->address_ = stAddress::InitAddress(e);
}
 

Address* Address::InitAddress(QDomElement &e)
{
    stAddress* p = new stAddress();


    QDomNode n = e.firstChild();
    QDomElement tmp;
    QString name;

    QString k,v;
    while(!n.isNull())
    {
        tmp = n.toElement();
        name = tmp.tagName();

        if(name == "P")
        {
			k = tmp.attribute("type","");
			v = tmp.text();

			if (k == "IP")
			{
				ip.push_back(tmp.text());
			}

			p->mpAddress_.insert(k,v);
        }  
        n = n.nextSibling();
    }

    return p;

}



void Address::getAllIedAddress(QList<QString> &listIp)
{
	QMap<QString,QString>::Iterator it;
	for (it = mpAddress_.begin(); it != mpAddress_.end(); ++it)
	{
		if (it.key() == "IP")
		{
			listIp.push_back(it.value());
		}
	}
}



void ConnectedAP::getAllIedAddress(QList<QString> &listIp)
{
	this->address_->getAllIedAddress(listIp);
}



/*
void IED::initServices(QDomElement &e)
{

}

void IED::initAccessPoint(QDomElement &e)
{
	stAccessPoint* ap = new stAccessPoint();

	ap->desc_ = e.attribute("desc","");
	ap->name_ = e.attribute("name","");
	ap->router_ = e.attribute("router","");
	ap->clock_ = e.attribute("clock","");

	this->mpAccessPoint_.insert(ap->name_,ap);

	QDomNode n = e.firstChild();
	QDomElement tmp;
	QString name;
	while(!n.isNull())
	{
		tmp = n.toElement();
		name = tmp.tagName();

		if(name == "Server")
		{
			ap->initServer(tmp);
		}


		n = n.nextSibling();
	}


}

void AccessPoint::initServer(QDomElement &e)
{
	this->Server_ = new stServer();

	Server_->desc_ = e.attribute("desc","");
	Server_->timeout_ = e.attribute("timeout","");

	QDomNode n = e.firstChild();
	QDomElement tmp;
	QString name;
	while(!n.isNull())
	{
		tmp = n.toElement();
		name = tmp.tagName();

		if(name == "Authentication")
		{
			Server_->initAuthentication(tmp);
		}
		else
			if(name = "LDevice")
			{
				Server_->initLDevice(tmp);
			}


			n = n.nextSibling();
	}
}

void Server::initAuthentication(QDomElement &e)
{

}
void Server::initLDevice(QDomElement &e)
{
	stLDevice* ld = new stLDevice();

	ld->desc_ = e.attribute("desc","");
	ld->inst_ = e.attribute("inst","");
	ld->ldName_ = e.attribute("ldName","");

	this->mpLDevice_.insert(ld->inst_,ld);

	QDomNode n = e.firstChild();
	QDomElement tmp;
	QString name;
	while(!n.isNull())
	{
		tmp = n.toElement();
		name = tmp.tagName();

		if(name == "LN0")
		{
			ld->initLN0(tmp);
		}
		else
			if(name == "LN")
			{
				ld->initLN(tmp);
			}


			n = n.nextSibling();
	}

}

void LDevice::initLN0(QDomElement &e)
{
	this->LN0_ = new stLN();

	LN0_->desc_ = e.attribute("desc","");
	LN0_->lnType_ = e.attribute("lnType","");
	LN0_->lnClass_ = e.attribute("lnClass","");
	LN0_->inst_ = e.attribute("inst","");

	QDomNode n = e.firstChild();
	QDomElement tmp;
	QString name;
	while(!n.isNull())
	{
		tmp = n.toElement();
		name = tmp.tagName();

		if(name == "DataSet")
		{
			LN0_->initDataSet(tmp);
		}
		else
			if(name == "ReportControl")
			{
				LN0_->initReportControl(tmp);
			}
			else
				if(name == "LogControl")
				{
					LN0_->initLogControl(tmp);
				}
				else
					if(name == "DOI")
					{
						LN0_->initDOI(tmp);
					}
					else
						if(name == "Inputs")
						{
							LN0_->initInputs(tmp);
						}
						else
							if(name == "Log")
							{
								LN0_->initLog(tmp);
							}
							else
								if(name == "GSEControl")
								{
								}
								else
									if(name == "SampledValueControl")
									{
									}
									else
										if(name == "SettingControl")
										{

										}
										else
											if(name == "SCLControl")
											{

											}


											n = n.nextSibling();
	}
}
void LDevice::initLN(QDomElement &e)
{

}

void LN::initDataSet(QDomElement &e)
{
	stDataSet *ds = new stDataSet();

	ds->desc_ = e.attribute("desc","");
	ds->name_ = e.attribute("name","");

	this->mpDataSet_.insert(ds->name_,ds);

	while(!n.isNull())
	{
		tmp = n.toElement();
		name = tmp.tagName();

		if(name == "FCDA")
		{
			ds->initFCDA(tmp);
		}
		else
			if(name == "FCDB")
			{
				ds->initFCDB(tmp);
			}

			n = n.nextSibling();
	}
}

void DataSet::initFCCB(QDomElement &e)
{
	stFCCB *fb = new stFCCB();
	fb->cbName_ = e.attribute("cbName","");
	fb->daName_ = e.attribute("daName","");
	fb->fc_ = e.attribute("fc","");
	fb->ldInst_ = e.attribute("ldInst");
	fb->lnClass_ = e.attribute("lnClass");
	fb->mustUnderstand_ = e.attribute("mustUnderstand","");
	fb->prefix_ = e.attribute("prefix","");

	this->vtFCCB_.append(fb);

}

void DataSet::initFCDA(QDomElement &e)
{
	stFCDA *fa = new stFCDA();
	fa->ldInst_ = e.attribute("ldInst","");
	fa->prefix_ = e.attribute("prefix","");
	fa->lnClass_ = e.attribute("lnClass","");
	fa->lnInst_ = e.attribute("lnInst","");
	fa->doName_ =e.attribute("doName","");
	fa->daName_ = e.attribute("daName","");
	fa->fc_ = e.attribute("fc","");
	fa->ix_ = e.attribute("ix","");

	this->vtFCDA_.append(fa);

}
*/