#ifndef BALL_H
#define BALL_H

#include <QtWidgets>
#include "pannel.h"

class Ball
{
private:
    QWidget * m_Widget;
    float m_DirectionX;
    float m_DirectionY;
    float m_PosRefX;//weil int für berechnung nicht reicht
    float m_PosRefY;
    float m_Speed;
public:
    Ball(QWidget * widget);
    bool Update();
    void SetStart();
    void CheckCollision(Pannel * panel);
    void SetBallDerection(int winkel);
};

#endif // BALL_H
