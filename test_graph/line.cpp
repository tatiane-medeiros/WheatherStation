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

QDate Line::getDate() const
{
    return m_data;
}

int Line::getHour() const
{
    return m_hora;
}

double Line::getVariable(int i) const
{
    return colums[i];
}

void Line::setDate(QDate date)
{
    m_data = date;
}

void Line::setHour(int hour)
{
    m_hora = hour;
}

void Line::setVariable(int i, double value)
{
    colums[i] = value;
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
