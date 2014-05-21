#ifndef MOUSE_H
#define MOUSE_H


#include <tracking.h>
#include <cmacro.h>
#include "X11/Xutil.h"
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

class CMouse : public QThread
{
private:
    Display* m_display;
    int m_button;
    CTracking* m_Stream;
    CMacro m_Macro;
    bool m_stop;
    QMutex m_MutexStop;
public:
    CMouse(CTracking* stream);
    ~CMouse();
    void setPosition(cv::Point2f);
    void click(int);
    void releaseClick();

    void stop(bool);

public slots:

    void run();

};

#endif // MOUSE_H
