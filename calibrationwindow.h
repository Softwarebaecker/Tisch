#ifndef CALIBRATIONWINDOW_H
#define CALIBRATIONWINDOW_H

#include <QWidget>
#include <QTimer>
#include <tracking.h>

namespace Ui {
class CCalibrationwindow;
}

class CCalibrationwindow : public QWidget
{
    Q_OBJECT
     
private:
    Ui::CCalibrationwindow *ui;
    QTimer* m_Timer;
    CTracking m_Stream;

public:
    explicit CCalibrationwindow(QWidget *parent = 0);
    ~CCalibrationwindow();
    

public slots:
    void updateGUI();
};

#endif // CALIBRATIONWINDOW_H
