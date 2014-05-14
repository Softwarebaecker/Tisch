#ifndef CALIBRATIONWINDOW_H
#define CALIBRATIONWINDOW_H

#include <QWidget>
#include <tracking.h>

namespace Ui {
class CCalibrationwindow;
}

class CCalibrationwindow : public QWidget
{
    Q_OBJECT
     
private:
    Ui::CCalibrationwindow *ui;
    CTracking *m_Stream;

public:
    explicit CCalibrationwindow(CTracking* stream,QWidget *parent = 0);
    ~CCalibrationwindow();
    

public slots:
    void updateGUI();
};

#endif // CALIBRATIONWINDOW_H
