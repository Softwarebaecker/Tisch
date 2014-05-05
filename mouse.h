#ifndef MOUSE_H
#define MOUSE_H
#include "opencv2/core/core.hpp"
#include "QCursor"

#include "X11/Xlib.h"
#include "X11/Xutil.h"
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/extensions/XTest.h>
#include <stdio.h>

class CMouse
{
private:
    Display* m_display;
    int m_button;
public:
    CMouse();
    ~CMouse();
    void setPosition(cv::Point2f);
    void click(int);
    void releaseClick();

};

#endif // MOUSE_H
