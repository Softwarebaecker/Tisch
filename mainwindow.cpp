
#include "ui_mainwindow.h"
#include "mainwindow.h"

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
}

CMainWindow::~CMainWindow()
{
    delete ui;
}


//Einstellungen aufrufen
void CMainWindow::on_button_properties_clicked()
{
    propertiesWindow = new CPropertiesWindow;
    propertiesWindow->show();
}

//Kalibrierung aufrufen
void CMainWindow::on_button_calibration_clicked()
{
    calibrationWindow = new CCalibrationwindow;
    calibrationWindow->showFullScreen();
    calibrationWindow->updateGUI();
}

//Maussimulation starten
void CMainWindow::on_button_simulation_clicked()
{
    simulationwindow = new CSimulationswindow;
    simulationwindow->show();
}

void CMainWindow::on_button_pong_clicked()
{
    pongwindow = new CPongWindow;
    pongwindow->show();
}
