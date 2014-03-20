#include "tracking.h"
#include <vector>

CTracking::CTracking()
{

}

CTracking::~CTracking()
{

}

bool CTracking::openWebcam()
{

    m_Webcam.open("http://192.168.0.254:8080/?action=stream&amp;type=.mjpg");   //öffnet die Kamera //wenn 1 übergeben wird, dann Webcam, die am PC angeschlossen ist

    if(!m_Webcam.isOpened())    //überprüft, ob die Kamera geöffnet ist
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool CTracking::closeWebcam()
{
    if(m_Webcam.isOpened())     //überprüft, ob die Kamera geöffnet ist
    {
        m_Webcam.release();

        if(!m_Webcam.isOpened())    //überprüft, ob die Kamera noch geöffnet ist
        {
            return true;
        }
    }
   return false;
}

void CTracking::convertFrame()
{
    //einen Frame aus der Kammera lesen
    m_Webcam.read(m_webcamFrame);

    //Schwellwertverfahren
    cv::inRange(m_webcamFrame,
                cv::Scalar(m_Properties.get_m_HMin(),m_Properties.get_m_SMin(),m_Properties.get_m_VMin()),
                cv::Scalar(m_Properties.get_m_HMax(),m_Properties.get_m_SMax(),m_Properties.get_m_VMax()),
                m_webcamFrameInRange);

    //Erosionsverfahren
    cv::erode(m_webcamFrameInRange, m_webcamFrameErode, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(m_Properties.get_m_Erode(),m_Properties.get_m_Erode())));

    //Dilationsverfahren
    cv::dilate(m_webcamFrameErode, m_webcamFrameDilate, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(m_Properties.get_m_Dilate(), m_Properties.get_m_Dilate())));
}



bool CTracking::tracking()
{

    cv::vector< cv::vector<cv::Point> > contours;
    cv::vector< cv::Vec4i> hierarchy;
    cv::Point2f coordinatsTMP;

    int numObjects;
    bool objectFound = false;
    double area;
    double areaLast = 0;

    int blubMin = m_Properties.get_m_BlubMin();
    int blubMax = m_Properties.get_m_BlubMax();

    m_CoordinateMoment.clear();

    cv::findContours(m_webcamFrameDilate, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);  //Konturen finden

    if(hierarchy.size() > 0)
    {
        numObjects = hierarchy.size();

        if(numObjects < 50) //überprüft, ob höchstens 50 Elemente vorhanden sind
        {
            for (int index = 0; index >= 0; index = hierarchy[index][0])
            {
                cv::Moments moment = moments((cv::Mat)contours[index]);
                area = moment.m00;

                if(area > (blubMin * blubMin) && area < (blubMax * blubMax))    //überprüft, ob das Element die richtige Größe hat
                {
                    //Setzen der Koordinaten
                    coordinatsTMP.y = moment.m01/area;
                    coordinatsTMP.x = moment.m10/area;
                    //Setzen der Koordinaten

                    if(areaLast < area) //überprüft, ob das Element größer als das Letzte ist
                    {
                        if(!m_CoordinateMoment.empty())
                        {
                            m_CoordinateMoment.at(0) = coordinatsTMP;
                        }
                        else
                        {
                            m_CoordinateMoment.push_back(coordinatsTMP);
                        }
                        areaLast = area;    //setzt das jetzige Element als das bis jetzt größte

                        objectFound = true;
                    }
                    else
                    {
                        m_CoordinateMoment.push_back(coordinatsTMP);
                    }

                }
            }
        }
    }

    return objectFound;
}
bool CTracking::convertCoordinate()
{
    cv::perspectiveTransform(m_CoordinateMoment, m_CoordinateMoment, m_Properties.get_m_TransformMatrix()); //multipliziert die Koordinaten mit der Matrix

    return true;
}

void CTracking::drawcoordinates()
{
    for(int index = 0;index<m_CoordinateMoment.size();index++)
    cv::circle(m_webcamFrame, cv::Point(m_CoordinateMoment.at(index).x,m_CoordinateMoment.at(index).y),20,cv::Scalar(0,255,0),2); //setzt einen Kreis um die Koordinaten
}

////Get-Methoden////
cv::Mat CTracking::get_m_webcamFrame()
{
    return m_webcamFrame;
}


cv::Mat CTracking::get_m_webcamFrameInRange()
{
    return m_webcamFrameInRange;
}


cv::Mat CTracking::get_m_webcamFrameErode()
{
    return m_webcamFrameErode;
}

cv::Mat CTracking::get_m_webcamFrameDilate()
{
    return m_webcamFrameDilate;
}

cv::Point2f CTracking::get_m_CoordinateMoment(int pos)
{

    return m_CoordinateMoment.at(pos);
}

CProperties* CTracking::get_m_Properties()
{
    return &m_Properties;
}

////Get-Methoden////
