#ifndef MOUSE_H
#define MOUSE_H
#include "opencv2/core/core.hpp"
#include "QCursor"

#include "X11/Xlib.h"
#include "X11/Xutil.h"

class CMouse
{
private:
    QCursor m_Cursor;
    Display* m_display;
    XEvent m_event;

public:
    CMouse();
    ~CMouse();
    void setPosition(cv::Point2f);
    void clickLeft();
    void releaseClick();

};

#endif // MOUSE_H
