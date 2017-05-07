#ifndef DATA
#define DATA
#include <QDebug>

class Data{
public:
    Data(){
      QStringList l;
      l <<"não"<<"ligo"<<"que";
        v.append(l);
        l.clear();
        l <<"falem"<<"de"<<"mim";
        v.append(l);
        l.clear();
        l <<"o"<<"meu"<<"lema";
        v.append(l);
        l.clear();
        l <<"é"<<"viver"<<"bem";
        v.append(l);
    }
    ~Data(){}

    QVector<QStringList> v;
};



#endif // DATA

