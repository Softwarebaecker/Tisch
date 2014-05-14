#ifndef CMACRO_H
#define CMACRO_H

#include <opencv2/core/core.hpp>
#include <X11/Xlib.h>
#include "X11/Xutil.h"
#include <X11/extensions/XTest.h>
#include <string>

class CMacro
{
public:
    CMacro();
    ~CMacro();

    std::string get_Macro(int index);
    int get_MacroWert(int index);
    void set_Macro(std::string macro, int index);
    void set_MacroWert(int macroWert, int index);

    void doMacro(int index);
    void lodeData();
    bool saveData();

private:

    Display* m_display;

    std::string m_Macro[8];
    int m_MacroWert[8];
    int m_MacroTaste2[8];

};

#endif // CMACRO_H
