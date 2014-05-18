
#include "ui_mainwindow.h"
#include "mainwindow.h"

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);

    m_stream = new CTracking;
    m_stream->start();

    propertiesWindow = NULL;
    calibrationWindow = NULL;
    simulationwindow = NULL;
    pongwindow = NULL;
    macroWindow = NULL;


}

CMainWindow::~CMainWindow()
{
    m_stream->quit();
    delete ui;
}


//Einstellungen aufrufen
void CMainWindow::on_button_properties_clicked()
{
    if(propertiesWindow!= NULL)
    {
        delete propertiesWindow;
        propertiesWindow = NULL;
    }
    propertiesWindow = new CPropertiesWindow(m_stream);
    propertiesWindow->show();
}

//Kalibrierung aufrufen
void CMainWindow::on_button_calibration_clicked()
{
    if(calibrationWindow!= NULL)
    {
        delete calibrationWindow;
        calibrationWindow = NULL;
    }
    calibrationWindow = new CCalibrationwindow(m_stream);
    calibrationWindow->showFullScreen();
    calibrationWindow->updateGUI();
}

//Maussimulation starten
void CMainWindow::on_button_simulation_clicked()
{
    if(simulationwindow!= NULL)
    {
        delete simulationwindow;
        simulationwindow = NULL;
    }
    simulationwindow = new CSimulationswindow(m_stream);
    simulationwindow->show();
}

void CMainWindow::on_button_pong_clicked()
{
    if(pongwindow!= NULL)
    {
        delete pongwindow;
        pongwindow = NULL;
    }
    pongwindow = new CPongWindow(m_stream);
    pongwindow->show();
}

void CMainWindow::on_button_macro_clicked()
{
    if(macroWindow!= NULL)
    {
        delete macroWindow;
        macroWindow = NULL;
    }
    macroWindow = new CMacroWindow(m_stream);

    macroWindow->show();
}
