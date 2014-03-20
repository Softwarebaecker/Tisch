#include "ui_simulationswindow.h"
#include "QMessageBox"

#include "simulationswindow.h"

CSimulationswindow::CSimulationswindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSimulationswindow)
{
    ui->setupUi(this);

    //Kamerastream öffnen
    if(m_Stream.openWebcam() == true)
    {
        m_Timer = new QTimer(this); //Timer erstellen

        connect(m_Timer, SIGNAL(timeout()), this, SLOT(updateGUI()));   //Timer mit Funktion verbinden

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
}

CSimulationswindow::~CSimulationswindow()
{
    delete ui;
}

void CSimulationswindow::on_buttonBeenden_clicked()
{
    m_Timer->stop();    //Timer stoppen
    delete m_Timer;     //löscht Timer

    close();
}
void CSimulationswindow::updateGUI()
{
    m_Stream.convertFrame();

    if(m_Stream.tracking())
    {
        m_Stream.convertCoordinate();

       m_Mouse.setPosition(m_Stream.get_m_CoordinateMoment(0));
       m_Mouse.clickLeft();

       do
       {
           m_Stream.convertFrame();
       }while(!m_Stream.tracking());    //läuft solange die Berührung existiert

       m_Mouse.releaseClick();
    }
}
