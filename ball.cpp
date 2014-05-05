#include "ball.h"

Ball::Ball(QWidget * widget)
{
    m_Widget=widget;
    SetStart();
}

bool Ball::Update()
{
    m_PosRefX+=m_DirectionX;
    m_PosRefY+=m_DirectionY;
    //y koordinate checken
    if(m_PosRefY>720-10 || m_PosRefY<0+10)
    {
        m_DirectionY*=-1;
    }

    if(m_PosRefX>1280-10 || m_PosRefX<0+10)
    {
        return false;
    }

    m_Speed+=0.001;

    //x koordinate checken (spieler verloren)
    m_Widget->move(QPoint((int)m_PosRefX-10,(int)m_PosRefY-10));
    return true;
}

void Ball::SetStart()
{
    m_Speed=4;
    m_DirectionX=5;
    m_DirectionY=0;
    m_PosRefX=200;
    m_PosRefY=720/2;
}

void Ball::CheckCollision(Pannel * panel)
{
    int pos_x=panel->get_Widget()->pos().x()+10;
    int pos_y=panel->get_Widget()->pos().y()+50;

    int dif=m_PosRefX-pos_x;
    if(dif<20 && dif>(-20))
    {//ball in reichweite in pannel zu berüren
        dif=m_PosRefY-pos_y;
        if(dif<60 && dif>(-60))
        {
            int pos=m_DirectionX;
            //neuen winkel setzen
            SetBallDerection(dif);
            if(pos>0)
            {
               m_DirectionX*=-1;
            }

            if(m_DirectionX<0)
            {
                m_PosRefX=1280-40;
            }
            else
            {
                m_PosRefX=40;
            }
        }
    }
}

void Ball::SetBallDerection(int winkel)
{
    m_DirectionX=cos(winkel*3.14158/180)*m_Speed;
    m_DirectionY=sin(winkel*3.14158/180)*m_Speed;
}
