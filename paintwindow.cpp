#include "paintwindow.h"
#include "ui_paintwindow.h"

CPaintWindow::CPaintWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CPaintWindow)
{
    ui->setupUi(this);
}

CPaintWindow::~CPaintWindow()
{
    delete ui;
}
