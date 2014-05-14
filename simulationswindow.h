#ifndef SIMULATIONSWINDOW_H
#define SIMULATIONSWINDOW_H

#include <QDialog>
#include "tracking.h"
#include "QTimer"

#include "cmacro.h"
#include "mouse.h"


namespace Ui {
class CSimulationswindow;
}

class CSimulationswindow : public QDialog
{
    Q_OBJECT

public:
    explicit CSimulationswindow(CTracking* stream, QWidget *parent = 0);
    ~CSimulationswindow();

private slots:
    void on_buttonBeenden_clicked();

public slots:
    void updateGUI();

private:
    Ui::CSimulationswindow *ui;
    QTimer* m_Timer;
    CTracking* m_Stream;
    CMouse m_Mouse;
    CMacro m_Macro;
};

#endif // SIMULATIONSWINDOW_H
