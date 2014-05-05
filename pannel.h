#ifndef PANNEL_H
#define PANNEL_H

#include <QtWidgets>

class Pannel
{
private:
    QWidget * m_Pannel;
public:
    Pannel(QWidget * pannel);
    void SetPosition(int y);

    QWidget * get_Widget(){return m_Pannel;}
};

#endif // PANNEL_H
