#ifndef SIMULATIONSWINDOW_H
#define SIMULATIONSWINDOW_H

#include <QDialog>
#include "QTimer"
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

private:
    Ui::CSimulationswindow *ui;
    CMouse *m_Mouse;
};

#endif // SIMULATIONSWINDOW_H
