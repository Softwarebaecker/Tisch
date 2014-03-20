#include "mouse.h"

#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <string.h>

CMouse::CMouse()
{

    m_display = XOpenDisplay(NULL);     //öffnet Display
}
CMouse::~CMouse()
{
    XCloseDisplay(m_display);       //schließt Display
    delete m_display;
}

void CMouse::setPosition(cv::Point2f coordinates)
{
    m_Cursor.setPos(coordinates.x, coordinates.y);    //setzt den Mauszeiger auf die Koordinaten

}

void CMouse::clickLeft()
{

    memset(&m_event, 0x00, sizeof(m_event));    //überschreibt alles mit 0

    //Eventeigenschaften
    m_event.type = ButtonPress;
    m_event.xbutton.button = Button1; //Button1 = Linksklick ; Button2 = Mittlere Taste ; Butten3 = Rechtsklick
    m_event.xbutton.same_screen = True;
    //Eventeigenschaften

    //setzt den Zeiger auf das oberste Fenster
    XQueryPointer(m_display, RootWindow(m_display, DefaultScreen(m_display)), &m_event.xbutton.root, &m_event.xbutton.window, &m_event.xbutton.x_root, &m_event.xbutton.y_root, &m_event.xbutton.x, &m_event.xbutton.y, &m_event.xbutton.state);

    m_event.xbutton.subwindow = m_event.xbutton.window;

    //sucht das unterste Fenster
    while(m_event.xbutton.subwindow)
    {
        m_event.xbutton.window = m_event.xbutton.subwindow;

        XQueryPointer(m_display, m_event.xbutton.window, &m_event.xbutton.root, &m_event.xbutton.subwindow, &m_event.xbutton.x_root, &m_event.xbutton.y_root, &m_event.xbutton.x, &m_event.xbutton.y, &m_event.xbutton.state);
    }

    //schickt das Event an das Fenster
    if(XSendEvent(m_display, PointerWindow, True, 0xfff, &m_event) == 0) fprintf(stderr, "Error\n");

    XFlush(m_display);  //zeichnet das Fenster neu

}

void CMouse::releaseClick()
{
    //setzt das Event so, dass die Taste losgelassen wird
    m_event.type = ButtonRelease;
    m_event.xbutton.state = 0x100;

    //schickt das Event an das Fenster
    if(XSendEvent(m_display, PointerWindow, True, 0xfff, &m_event) == 0) fprintf(stderr, "Error\n");

    XFlush(m_display);  //zeichnet das Fenster neu
}
