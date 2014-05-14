#include "pannel.h"

Pannel::Pannel(QWidget * pannel)
{
    m_Pannel=pannel;
}

void Pannel::SetPosition(int y)
{
    int newpos=y-50;
    if(newpos < 0)
        newpos=0;
    if(newpos > 800-100)
        newpos=800-100;
    m_Pannel->move(QPoint(m_Pannel->pos().x(),newpos));
}
