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
    qDebug() << data << hora;
    for(int i = 0; i< 17; ++i){
        std::cout << colums[i] << "*";
    }
    qDebug() <<"";
}

void Line::clear()
{
    hora = 0;
    for(int i = 0; i< 17; ++i){
         colums[i] = 0;
    }
}

