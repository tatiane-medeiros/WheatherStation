#ifndef LINE_H
#define LINE_H
#include <QDate>
#include <QDebug>
#include <iostream>

class Line
{
public:
    Line();
    ~Line();

    void printL();
    void clear();
    QDate getDate() const;
    int getHour() const;
    double getVariable(int i) const;
    void setDate(QDate date);
    void setHour(int hour);
    void setVariable(int i, double value);
    QString data ()const;
    QString hora ()const;
private:
    QDate m_data;
    int m_hora;
protected:
    double colums[17];   //temp_inst,temp_max,temp_min,umid_inst,umid_max,umid_min,pto_orvalho_inst,pto_orvalho_max,pto_orvalho_min,pressao,pressao_max,pressao_min,vento_direcao,vento_vel, vento_rajada,radiacao,precipitacao

};

#endif // LINE_H
