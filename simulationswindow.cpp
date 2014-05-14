#include "ui_simulationswindow.h"
#include "QMessageBox"
#include "simulationswindow.h"
#include "math.h"

CSimulationswindow::CSimulationswindow(CTracking* stream, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSimulationswindow)
{
    ui->setupUi(this);

    m_Stream = stream;

    m_Timer = new QTimer(this); //Timer erstellen

    connect(m_Timer, SIGNAL(timeout()), this, SLOT(updateGUI()));   //Timer mit Funktion verbinden

    m_Timer->start(20);     //Timer starten

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
    cv::Point2f coordinate;

    if(m_Stream->get_m_CoordinateMoment_number()!=0)
    {
       coordinate = m_Stream->get_m_CoordinateMoment(0);

       if(coordinate.x < -10)
       {
           //Macros
           for(int i = 0 ; i < 8 ; i++)
           if(coordinate.y <((i+1)*100))
           {
               m_Macro.doMacro(i);
               while(m_Stream->get_m_CoordinateMoment_number()!=0)    //läuft solange die Berührung existiert
               {

               }
               return;
           }
       }
       else
       {
           m_Mouse.setPosition(coordinate);

           int i = 0;

           while(m_Stream->get_m_CoordinateMoment_number()!=0)    //läuft solange die Berührung existiert
           {

               if(m_Stream->get_m_CoordinateMoment_number()>1)
               {
                   while(m_Stream->get_m_CoordinateMoment_number()!=0)    //läuft solange die Berührung existiert
                   {
                       if(m_Stream->get_m_CoordinateMoment(0).y < coordinate.y)
                       {
                           m_Mouse.click(5);
                       }
                       if(m_Stream->get_m_CoordinateMoment(0).y > coordinate.y)
                       {
                           m_Mouse.click(4);
                       }
                       m_Mouse.releaseClick();

                       coordinate = m_Stream->get_m_CoordinateMoment(0);

                       m_Mouse.setPosition(coordinate);

                   }
                   return;
               }

               if(fabs((coordinate.x-m_Stream->get_m_CoordinateMoment(0).x))>10 && fabs((coordinate.y-m_Stream->get_m_CoordinateMoment(0).y))>10 )
               {
                   m_Mouse.click(1);

                   while(m_Stream->get_m_CoordinateMoment_number()!=0)    //läuft solange die Berührung existiert
                   {
                       m_Mouse.setPosition(m_Stream->get_m_CoordinateMoment(0));
                       cv::waitKey(30);
                   }
                   m_Mouse.releaseClick();
                   return;
               }
               if(i>30)
               {
                   m_Mouse.click(3);
                   m_Mouse.releaseClick();
                   while(m_Stream->get_m_CoordinateMoment_number()!=0)    //läuft solange die Berührung existiert
                   {
                   }

                   return;
               }


               i++;
               cv::waitKey(30);
           }

           m_Mouse.click(1);

           m_Mouse.releaseClick();
       }
       cv::waitKey(20);
    }
}
