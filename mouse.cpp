#include "mouse.h"

#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <string.h>

CMouse::CMouse(CTracking* stream)
{
    m_stop = false;
    m_Stream = stream;
    m_display = XOpenDisplay(NULL);     //öffnet Display
}
CMouse::~CMouse()
{
    XCloseDisplay(m_display);       //schließt Display
}

void CMouse::setPosition(cv::Point2f coordinates)
{
    XTestFakeMotionEvent(m_display, DefaultScreen(m_display),coordinates.x, coordinates.y, 0);
    XFlush(m_display);
}

void CMouse::click(int button)
{
    m_button = button;

    //Button1 = Linksklick ; Button2 = Mittlere Taste ; Butten3 = Rechtsklick ; Button4 = Srollen nach oben ; Button5 = Scrollen nach unten

    switch (m_button)
    {
    case 1:
        XTestFakeButtonEvent(m_display, Button1, true, 0);
        break;
    case 2:
        XTestFakeButtonEvent(m_display, Button2, true, 0);
        break;
    case 3:
        XTestFakeButtonEvent(m_display, Button3, true, 0);
        break;
    case 4:
        XTestFakeButtonEvent(m_display, Button4, true, 0);
        break;
    case 5:
        XTestFakeButtonEvent(m_display, Button5, true, 0);
        break;
    }
    XFlush(m_display);  //zeichnet das Fenster neu

}

void CMouse::stop(bool tmp)
{
    m_MutexStop.lock();
    m_stop = tmp;
    m_MutexStop.unlock();
}

void CMouse::releaseClick()
{
    switch (m_button)
    {
    case 1:
        XTestFakeButtonEvent(m_display, Button1, false, 0);
        break;
    case 2:
        XTestFakeButtonEvent(m_display, Button4, false, 0);
        break;
    case 3:
        XTestFakeButtonEvent(m_display, Button3, false, 0);
        break;
    case 4:
        XTestFakeButtonEvent(m_display, Button4, false, 0);
        break;
    case 5:
        XTestFakeButtonEvent(m_display, Button5, false, 0);
        break;
    }
    XFlush(m_display);  //zeichnet das Fenster neu

}

void CMouse::run()
{
    while(true)
    {
        m_MutexStop.lock();
        if(m_stop)
        {
            m_MutexStop.unlock();
            break;
        }
        m_MutexStop.unlock();
        cv::Point2f coordinate;
        bool normelclick = true;

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
                       msleep(10);
                   }
                   normelclick = false;
                   break;
               }
           }
           else
           {
               setPosition(coordinate);

               int i = 0;

               while(m_Stream->get_m_CoordinateMoment_number()!=0)    //läuft solange die Berührung existiert
               {

                   if(m_Stream->get_m_CoordinateMoment_number()>1)
                   {
                       while(m_Stream->get_m_CoordinateMoment_number()!=0)    //läuft solange die Berührung existiert
                       {
                           if(m_Stream->get_m_CoordinateMoment(0).y < coordinate.y)
                           {
                               click(5);
                           }
                           if(m_Stream->get_m_CoordinateMoment(0).y > coordinate.y)
                           {
                               click(4);
                           }
                           releaseClick();

                           coordinate = m_Stream->get_m_CoordinateMoment(0);

                           setPosition(coordinate);
                           msleep(10);

                       }
                       normelclick = false;
                   }
                   else
                   {
                        if(fabs((coordinate.x-m_Stream->get_m_CoordinateMoment(0).x))>10 || fabs((coordinate.y-m_Stream->get_m_CoordinateMoment(0).y))>10 )
                       {
                           click(1);

                           while(m_Stream->get_m_CoordinateMoment_number()!=0)    //läuft solange die Berührung existiert
                           {
                               setPosition(m_Stream->get_m_CoordinateMoment(0));
                               msleep(10);
                           }

                           releaseClick();
                           normelclick = false;
                       }
                       if(i>50)
                       {
                           click(3);
                           releaseClick();
                           while(m_Stream->get_m_CoordinateMoment_number()!=0)    //läuft solange die Berührung existiert
                           {
                               msleep(10);
                           }
                           normelclick = false;
                       }
                   }


                   i++;
                   msleep(10);
               }

               if(true == normelclick)
               {
                   click(1);
                   releaseClick();
               }
           }
        }
        msleep(10);
    }
}
