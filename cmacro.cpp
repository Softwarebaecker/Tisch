#include "cmacro.h"

CMacro::CMacro()
{
    m_display = XOpenDisplay(NULL);     //öffnet Display
    lodeData();
}

CMacro::~CMacro()
{
    XCloseDisplay(m_display);       //schließt Display
}

std::string CMacro::get_Macro(int index)
{
    return m_Macro[index];
}

int CMacro::get_MacroWert(int index)
{
    return m_MacroWert[index];
}

void CMacro::set_Macro(std::string macro, int index)
{
    m_Macro[index] = macro;
}

void CMacro::set_MacroWert(int macroWert, int index)
{
    m_MacroWert[index] = macroWert;
}

void CMacro::doMacro(int index)
{
     if(m_MacroTaste2 != 0) XTestFakeKeyEvent( m_display, m_MacroTaste2[index], true, 10);
     XFlush(m_display);

     // 3rd param. : keypressed = true :: keyreleased = false
     XTestFakeKeyEvent( m_display, m_MacroWert[index], true, 0);
     XFlush(m_display);
     XTestFakeKeyEvent( m_display, m_MacroWert[index], false, 0 );
     XFlush(m_display);

     if(m_MacroTaste2 != 0) XTestFakeKeyEvent( m_display, m_MacroTaste2[index], false, 10);
     XFlush(m_display);
}

void CMacro::lodeData()
{
    cv::FileStorage file;

    file.open("Macro.yml", cv::FileStorage::READ);

    if(file.isOpened())
    {
        std::string tmp, tmpWert, tmp2Taste;

        for(int i = 0 ; i < 8 ; i++)
        {
            tmp = "Macro ";
            tmp += std::to_string(i);
            tmpWert = "MacroWert";
            tmpWert += std::to_string(i);
            tmp2Taste = "MacroTaste2";
            tmp2Taste += std::to_string(i);
            file[tmp] >> m_Macro[i];
            file[tmpWert] >> m_MacroWert[i];
            file[tmp2Taste] >> m_MacroTaste2[i];
        }

        file.release();
    }
    else
    {
        std::string tmp;

        for(int i = 0 ; i < 8 ; i++)
        {
            tmp = "Macro ";
            tmp += std::to_string(i);
            m_Macro[i] = tmp;
            m_MacroWert[i] = 0;
            m_MacroTaste2[i] = 0;
        }
    }

}

bool CMacro::saveData()
{
    cv::FileStorage file("Macro.yml", cv::FileStorage::WRITE);

    if(file.isOpened())
    {
        std::string tmp, tmpWert, tmp2Taste;

        for(int i = 0 ; i < 8 ; i++)
        {
            tmp = "Macro ";
            tmp += std::to_string(i);
            tmpWert = "MacroWert";
            tmpWert += std::to_string(i);
            tmp2Taste = "MacroTaste2";
            tmp2Taste += std::to_string(i);
            file << tmp << m_Macro[i];
            file << tmpWert << m_MacroWert[i];
            file << tmp2Taste << m_MacroTaste2[i];
        }

        file.release();

        return true;
    }
    else
        return false;

}
