#include "ui_simulationswindow.h"
#include "QMessageBox"
#include "simulationswindow.h"
#include "math.h"

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
    cv::Point2f coordinate;

    if(m_Stream.tracking())
    {
       m_Stream.convertCoordinate();

       coordinate = m_Stream.get_m_CoordinateMoment(0);

       m_Mouse.setPosition(coordinate);

       m_Stream.convertFrame();

       int i = 0;

       while(m_Stream.tracking()==true)    //läuft solange die Berührung existiert
       {
           m_Stream.convertCoordinate();
           
           if(m_Stream.get_m_CoordinateMoment_number()>1)
           {

               m_Stream.convertFrame();
               while(m_Stream.tracking()==true)    //läuft solange die Berührung existiert
               {
                   m_Stream.convertCoordinate();
                   if(m_Stream.get_m_CoordinateMoment(0).y < coordinate.y)
                   {
                       m_Mouse.click(5);
                   }
                   if(m_Stream.get_m_CoordinateMoment(0).y > coordinate.y)
                   {
                       m_Mouse.click(4);
                   }
                   m_Mouse.releaseClick();

                   m_Mouse.setPosition(m_Stream.get_m_CoordinateMoment(0));

                   coordinate = m_Stream.get_m_CoordinateMoment(0);

                   m_Stream.convertFrame();

                   m_Mouse.releaseClick();

               }
               return;
           }
           
           if(fabs((coordinate.x-m_Stream.get_m_CoordinateMoment(0).x))>10 && fabs((coordinate.y-m_Stream.get_m_CoordinateMoment(0).y))>10 )
           {
               m_Mouse.click(1);

               m_Stream.convertFrame();
               while(m_Stream.tracking()==true)    //läuft solange die Berührung existiert
               {
                   m_Stream.convertCoordinate();
                   m_Mouse.setPosition(m_Stream.get_m_CoordinateMoment(0));
                   m_Stream.convertFrame();

               }
               break;
           }
           if(i>10)
           {
               m_Mouse.click(3);
               m_Stream.convertFrame();
               while(m_Stream.tracking()==true)    //läuft solange die Berührung existiert
               {
                   m_Stream.convertFrame();
               }
               break;
           }


           i++;

           m_Stream.convertFrame();

       }
       if(i<=10)
       {
           m_Mouse.click(1);
       }


       m_Mouse.releaseClick();
       cv::waitKey(20);
    }
}
