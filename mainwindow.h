#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <pongwindow.h>
#include <propertieswindow.h>
#include <calibrationwindow.h>
#include <simulationswindow.h>


namespace Ui {
class CMainWindow;
}

class CMainWindow : public QMainWindow
{
    Q_OBJECT

    
public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();
    
private slots:


    void on_button_properties_clicked();

    void on_button_calibration_clicked();

    void on_button_simulation_clicked();

    void on_button_pong_clicked();

private:
    Ui::CMainWindow *ui;
    CPropertiesWindow* propertiesWindow;
    CCalibrationwindow* calibrationWindow;
    CSimulationswindow* simulationwindow;
    CPongWindow* pongwindow;

};

#endif // MAINWINDOW_H