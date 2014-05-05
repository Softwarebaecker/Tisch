#ifndef PONGWINDOW_H
#define PONGWINDOW_H

#include <QDialog>
#include "pannel.h"
#include "ball.h"

namespace Ui {
class CPongWindow;
}

class CPongWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CPongWindow(QWidget *parent = 0);
    ~CPongWindow();

    void StartMenue();

private slots:
    void on_button_starte_clicked();
    void Update();


private:
    Ui::CPongWindow *ui;
    QTimer * m_Timer;

    Pannel * m_LeftPannel;
    Pannel * m_RightPannel;
    Ball * m_Ball;
};

#endif // PONGWINDOW_H
