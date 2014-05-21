#ifndef PONGWINDOW_H
#define PONGWINDOW_H

#include <QDialog>
#include "pannel.h"
#include "ball.h"
#include "tracking.h"

namespace Ui {
class CPongWindow;
}

class CPongWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CPongWindow(CTracking* stream, QWidget *parent = 0);
    ~CPongWindow();

    void StartMenue();

private slots:
    void on_button_starte_clicked();
    void Update();
    void UpdateTracking();


    void on_button_benden_clicked();

private:
    Ui::CPongWindow *ui;
    QTimer* m_Timer;
    QTimer*  m_TimerTracking;
    QTimer* m_TimerMenue;


    Pannel * m_LeftPannel;
    Pannel * m_RightPannel;
    Ball * m_Ball;
    CTracking* m_Stream;
};

#endif // PONGWINDOW_H
