
#include "ui_mainwindow.h"
#include "mainwindow.h"

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);

    m_stream = new CTracking;
    m_stream->start();


}

CMainWindow::~CMainWindow()
{
    m_stream->quit();
    delete ui;
}


//Einstellungen aufrufen
void CMainWindow::on_button_properties_clicked()
{
    propertiesWindow = new CPropertiesWindow(m_stream);
    propertiesWindow->show();
}

//Kalibrierung aufrufen
void CMainWindow::on_button_calibration_clicked()
{
    calibrationWindow = new CCalibrationwindow(m_stream);
    calibrationWindow->showFullScreen();
    calibrationWindow->updateGUI();
}

//Maussimulation starten
void CMainWindow::on_button_simulation_clicked()
{
    simulationwindow = new CSimulationswindow(m_stream);
    simulationwindow->show();
}

void CMainWindow::on_button_pong_clicked()
{
    pongwindow = new CPongWindow(m_stream);
    pongwindow->show();
}

void CMainWindow::on_button_macro_clicked()
{
    CMacroWindow macroWindow;

    macroWindow.exec();
}
