#include "ui_simulationswindow.h"
#include "QMessageBox"
#include "simulationswindow.h"
#include "math.h"

CSimulationswindow::CSimulationswindow(CTracking* stream, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSimulationswindow)
{
    ui->setupUi(this);

    m_Mouse = new CMouse(stream);

    m_Mouse->start();

}

CSimulationswindow::~CSimulationswindow()
{
    delete m_Mouse;
    delete ui;
}

void CSimulationswindow::on_buttonBeenden_clicked()
{
    m_Mouse->stop(true);
    m_Mouse->quit();
    close();
}
