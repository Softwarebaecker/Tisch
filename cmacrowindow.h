#ifndef CMACROWINDOW_H
#define CMACROWINDOW_H

#include <QDialog>
#include <QTimer>
#include <tracking.h>
#include <cmacro.h>


namespace Ui {
class CMacroWindow;
}

class CMacroWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CMacroWindow(CTracking* stream, QWidget *parent = 0);
    ~CMacroWindow();

private:
    Ui::CMacroWindow *ui;
    QTimer* m_Timer;
    CTracking* m_Stream;
    CMacro m_Macro;

private slots:
    void update();
    void on_buttonBox_accepted();
};

#endif // CMACROWINDOW_H
