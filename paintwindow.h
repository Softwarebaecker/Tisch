#ifndef PAINTWINDOW_H
#define PAINTWINDOW_H

#include <QWidget>

namespace Ui {
class CPaintWindow;
}

class CPaintWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CPaintWindow(QWidget *parent = 0);
    ~CPaintWindow();

private:
    Ui::CPaintWindow *ui;
};

#endif // PAINTWINDOW_H
