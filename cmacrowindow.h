#ifndef CMACROWINDOW_H
#define CMACROWINDOW_H

#include <QDialog>

namespace Ui {
class CMacroWindow;
}

class CMacroWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CMacroWindow(QWidget *parent = 0);
    ~CMacroWindow();

private:
    Ui::CMacroWindow *ui;
};

#endif // CMACROWINDOW_H
