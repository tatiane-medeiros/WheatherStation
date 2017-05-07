#include "line.h"

Line::Line()
{

}

Line::~Line()
{

}

void Line::printL()
{
    using namespace std;
    qDebug() << m_data << m_hora;
    for(int i = 0; i< 17; ++i){
        std::cout << colums[i] << "*";
    }
    qDebug() <<"";
}

void Line::clear()
{
    m_hora = 0;
    for(int i = 0; i< 17; ++i){
         colums[i] = 0;
    }
}

 QString Line::data() const
{
    QString aux;
    aux.append(QString::number(m_data.day()).rightJustified(2,'0'));
    aux.append("/" );
    aux.append(QString::number(m_data.month()).rightJustified(2,'0'));
    aux.append("/" );
    aux.append(QString::number(m_data.year()).rightJustified(2,'0'));
    return aux;
}

QString Line::hora() const
{
    QString  aux;
    aux.append(QString::number(m_hora).rightJustified(2,'0'));
    return aux;
}

