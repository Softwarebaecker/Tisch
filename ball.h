#ifndef BALL_H
#define BALL_H

#include <QtWidgets>
#include <QThread>
#include "pannel.h"

class Ball : public QThread
{
private:
    QWidget * m_Widget;
    float m_DirectionX;
    float m_DirectionY;
    float m_PosRefX;//weil int für berechnung nicht reicht
    float m_PosRefY;
    float m_Speed;

    Pannel* m_pannelLinks;
    Pannel* m_pannelRechts;
public:
    Ball(QWidget * widget, Pannel* links, Pannel* rechts);
    bool Update();
    void SetStart();
    void CheckCollision(Pannel * panel);
    void SetBallDerection(int winkel);

public slots:
    void run();

};

#endif // BALL_H



