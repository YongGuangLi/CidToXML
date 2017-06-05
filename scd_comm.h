#ifndef SCD_COMM_H
#define SCD_COMM_H

#include <QMap>
#include <QString>

template<typename T>

T* FindMap(QString n,QMap<QString,T*> &m)
{
  return  m.find(n,NULL);
}



class SCD
{
public:
    virtual void dump() = 0;
    SCD();
    ~SCD();
};

#endif // SCD_COMM_H
