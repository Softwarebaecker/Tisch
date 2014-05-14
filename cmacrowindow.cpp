
#include "ui_cmacrowindow.h"
#include <QMessageBox>

#include "cmacrowindow.h"

CMacroWindow::CMacroWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CMacroWindow)
{
    ui->setupUi(this);
    //Kamerastream öffnen
    if(m_Stream.openWebcam() == true)
    {
        m_Timer = new QTimer(this); //Timer erstellen

        connect(m_Timer, SIGNAL(timeout()), this, SLOT(update()));   //Timer mit Funktion verbinden

        m_Timer->start(20);     //Timer starten
    }
    else
    {
        m_Timer->stop();    //Timer stoppen

        //Fehlermeldung ausgeben
        QMessageBox warning;
        warning.setText("Achtung!!\n Kamera konnte nicht geöffnet werden!");
        warning.exec();
        //Fehlermeldung ausgeben

        exit(1);
    }

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
    //analysiert einen Frame
    m_Stream.convertFrame();
    QString coordinats;

    coordinats.clear();

    if(m_Stream.tracking())
    {
        m_Stream.convertCoordinate();

        //Koordinaten ausgeben
        coordinats.sprintf("X : %02d , Y : %02d",(int)m_Stream.get_m_CoordinateMoment(0).x,(int)m_Stream.get_m_CoordinateMoment(0).y);
        ui->textEdit->append(coordinats);

    }
}

void CMacroWindow::on_buttonBox_accepted()
{
    m_Macro.saveData();
}
