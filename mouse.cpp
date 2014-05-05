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
