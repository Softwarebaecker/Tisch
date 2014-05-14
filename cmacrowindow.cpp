#include "cmacrowindow.h"
#include "ui_cmacrowindow.h"

CMacroWindow::CMacroWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CMacroWindow)
{
    ui->setupUi(this);
}

CMacroWindow::~CMacroWindow()
{
    delete ui;
}
