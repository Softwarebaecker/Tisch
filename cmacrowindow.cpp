
#include "ui_cmacrowindow.h"
#include <QMessageBox>

#include "cmacrowindow.h"

CMacroWindow::CMacroWindow(CTracking* stream, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CMacroWindow)
{
    ui->setupUi(this);

    m_Stream = stream;
    m_Timer = new QTimer(this); //Timer erstellen

    connect(m_Timer, SIGNAL(timeout()), this, SLOT(update()));   //Timer mit Funktion verbinden

    m_Timer->start(20);     //Timer starten

    ui->pushButton->setText(QString::fromStdString(m_Macro.get_Macro(0)));
    ui->pushButton_2->setText(QString::fromStdString(m_Macro.get_Macro(1)));
    ui->pushButton_3->setText(QString::fromStdString(m_Macro.get_Macro(2)));
    ui->pushButton_4->setText(QString::fromStdString(m_Macro.get_Macro(3)));
    ui->pushButton_5->setText(QString::fromStdString(m_Macro.get_Macro(4)));
    ui->pushButton_6->setText(QString::fromStdString(m_Macro.get_Macro(5)));
    ui->pushButton_7->setText(QString::fromStdString(m_Macro.get_Macro(6)));
    ui->pushButton_8->setText(QString::fromStdString(m_Macro.get_Macro(7)));

}

CMacroWindow::~CMacroWindow()
{
    delete ui;
}


void CMacroWindow::update()
{
    QString coordinats;

    coordinats.clear();

    if(0 != m_Stream->get_m_CoordinateMoment_number())
    {
        //Koordinaten ausgeben
        coordinats.sprintf("X : %02d , Y : %02d",(int)m_Stream->get_m_CoordinateMoment(0).x,(int)m_Stream->get_m_CoordinateMoment(0).y);
        ui->textEdit->append(coordinats);
    }
}

void CMacroWindow::on_buttonBox_accepted()
{
    //m_Macro.saveData();
}
