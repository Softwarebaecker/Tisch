#ifndef PROPERTIESWINDOW_H
#define PROPERTIESWINDOW_H

#include <QDialog>
#include <QTimer>
#include <tracking.h>

#include "cmacro.h"
#include "mouse.h"
namespace Ui {
class CPropertiesWindow;
}

class CPropertiesWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit CPropertiesWindow(CTracking* stream, QWidget *parent = 0);
    ~CPropertiesWindow();
    
private:
    Ui::CPropertiesWindow *ui;
    QTimer* m_Timer;
    CTracking* m_Stream;
    CMouse m_Mouse;
    CMacro m_Macro;


public slots:
    void updateGUI();   //Timerfunktion

private slots:
    void on_button_OK_clicked();
    void on_button_cancel_clicked();
    void on_button_reset_clicked();
    void on_slider_H_MIN_valueChanged(int value);
    void on_slider_H_MAX_valueChanged(int value);
    void on_slider_S_MIN_valueChanged(int value);
    void on_slider_S_MAX_valueChanged(int value);
    void on_slider_V_MIN_valueChanged(int value);
    void on_slider_V_MAX_valueChanged(int value);
    void on_dial_Erode_valueChanged(int value);
    void on_dial_Dilate_valueChanged(int value);
    void on_slider_BLUB_MAX_valueChanged(int value);
    void on_slider_BLUB_MIN_valueChanged(int value);
};

#endif // PROPERTIESWINDOW_H
