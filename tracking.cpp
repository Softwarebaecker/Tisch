#include "tracking.h"
#include <vector>

CTracking::CTracking()
{
    openWebcam();
    m_stop = false;
    m_drawcoordinates = false;
    m_convertCoordinates = true;
}

CTracking::~CTracking()
{
    closeWebcam();
}

bool CTracking::openWebcam()
{
    m_Webcam.open("http://192.168.0.254:8080/?action=stream&amp;type=.mjpg");   //öffnet die Kamera //wenn 1 übergeben wird, dann Webcam, die am PC angeschlossen ist

    if(!m_Webcam.isOpened())    //überprüft, ob die Kamera geöffnet ist
    {
        exit();
    }
    return true;
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
    m_MutexWebcamFrame.lock();
    m_Webcam.read(m_webcamFrame);
    m_MutexWebcamFrame.unlock();
    m_MutexDrawcoordinates.lock();
    m_webcamFrame.copyTo( m_WebcamFrameDraw);
    m_MutexDrawcoordinates.unlock();

    //Schwellwertverfahren
    m_MutexWebcamFrameInRange.lock();
    cv::inRange(m_webcamFrame,
                cv::Scalar(m_Properties.get_m_HMin(),m_Properties.get_m_SMin(),m_Properties.get_m_VMin()),
                cv::Scalar(m_Properties.get_m_HMax(),m_Properties.get_m_SMax(),m_Properties.get_m_VMax()),
                m_webcamFrameInRange);
    m_MutexWebcamFrameInRange.unlock();

    //Erosionsverfahren
    m_MutexWebcamFrameErode.lock();
    cv::erode(m_webcamFrameInRange, m_webcamFrameErode, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(m_Properties.get_m_Erode(),m_Properties.get_m_Erode())));
    m_MutexWebcamFrameErode.unlock();

    //Dilationsverfahren
    m_MutexWebcamFrameDilate.lock();
    cv::dilate(m_webcamFrameErode, m_webcamFrameDilate, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(m_Properties.get_m_Dilate(), m_Properties.get_m_Dilate())));
    m_MutexWebcamFrameDilate.unlock();
}



bool CTracking::tracking()
{

    cv::vector< cv::vector<cv::Point> > contours;
    cv::vector< cv::Vec4i> hierarchy;
    cv::Point2f coordinatsTMP;

    bool objectFound = false;
    double area;

    int blubMin = m_Properties.get_m_BlubMin();
    int blubMax = m_Properties.get_m_BlubMax();

    m_MutexWebcamFrameDilate.lock();
    cv::Mat tmp(m_webcamFrameDilate);
    m_MutexWebcamFrameDilate.unlock();

    cv::findContours(tmp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);  //Konturen finden

    m_MutexCoordinateMoment.lock();
    m_CoordinateMoment.clear();
    if(hierarchy.size() > 0)
    {
        if(hierarchy.size() < 50) //überprüft, ob höchstens 50 Elemente vorhanden sind
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

                    m_CoordinateMoment.push_back(coordinatsTMP);
                    objectFound = true;
                }
            }
        }
    }
    return objectFound;
}
void CTracking::convertCoordinate()
{
    cv::perspectiveTransform(m_CoordinateMoment, m_CoordinateMoment, m_Properties.get_m_TransformMatrix()); //multipliziert die Koordinaten mit der Matrix
}

void CTracking::drawcoordinates()
{
    m_MutexWebcamFrameDraw.lock();
    for(unsigned int index = 0 ; index < m_CoordinateMoment.size() ; index++)
    cv::circle(m_WebcamFrameDraw, cv::Point(m_CoordinateMoment.at(index).x,m_CoordinateMoment.at(index).y),20,cv::Scalar(0,255,0),2); //setzt einen Kreis um die Koordinaten
    m_MutexWebcamFrameDraw.unlock();
}

////Get-Methoden////
cv::Mat CTracking::get_m_webcamFrame()
{
    cv::Mat tmp;
    m_MutexWebcamFrame.lock();
    m_webcamFrame.copyTo(tmp);
    m_MutexWebcamFrame.unlock();
    return tmp;
}


cv::Mat CTracking::get_m_webcamFrameInRange()
{
    cv::Mat tmp;
    m_MutexWebcamFrameInRange.lock();
    m_webcamFrameInRange.copyTo(tmp);
    m_MutexWebcamFrameInRange.unlock();
    return tmp;
}


cv::Mat CTracking::get_m_webcamFrameErode()
{
    cv::Mat tmp;
    m_MutexWebcamFrameErode.lock();
    m_webcamFrameErode.copyTo(tmp);
    m_MutexWebcamFrameErode.unlock();
    return tmp;
}

cv::Mat CTracking::get_m_webcamFrameDilate()
{
    cv::Mat tmp;
    m_MutexWebcamFrameDilate.lock();
    m_webcamFrameDilate.copyTo(tmp);
    m_MutexWebcamFrameDilate.unlock();
    return tmp;
}
cv::Mat CTracking::get_m_webcamFrameDraw()
{
    cv::Mat tmp;
    m_MutexWebcamFrameDraw.lock();
    m_WebcamFrameDraw.copyTo(tmp);
    m_MutexWebcamFrameDraw.unlock();
    return tmp;
}

cv::Point2f CTracking::get_m_CoordinateMoment(unsigned int pos)
{
    cv::Point2f tmp;
    m_MutexCoordinateMoment.lock();
    if(m_CoordinateMoment.size() > pos)
    {
        tmp = m_CoordinateMoment.at(pos);
    }
    else
    {
        tmp = m_CoordinateMoment.back();
    }
    m_MutexCoordinateMoment.unlock();
    return tmp;
}

int CTracking::get_m_CoordinateMoment_number()
{
    m_MutexCoordinateMoment.lock();
    int tmp = m_CoordinateMoment.size();
    m_MutexCoordinateMoment.unlock();
    return tmp;
}

CProperties* CTracking::get_m_Properties()
{
    return &m_Properties;
}

void CTracking::stopThread()
{
    m_MutexStop.lock();
    m_stop = true;
    m_MutexStop.unlock();
}


void CTracking::set_drawcoordinates(bool tmp)
{
    m_MutexDrawcoordinates.lock();
    m_drawcoordinates = tmp;
    m_MutexDrawcoordinates.unlock();
}


void CTracking::set_convertCoordinates(bool tmp)
{
    m_MutexConvertCoordinates.lock();
    m_convertCoordinates = tmp;
    m_MutexConvertCoordinates.unlock();
}

////Get-Methoden////


void CTracking::run()
{
    while(!m_stop)
    {
        convertFrame();

        if(tracking())
        {
            m_MutexDrawcoordinates.lock();
            if(m_drawcoordinates)
            {
                drawcoordinates();
            }
            m_MutexDrawcoordinates.unlock();

            m_MutexConvertCoordinates.lock();
            if(m_convertCoordinates)
            {
                convertCoordinate();
            }
            m_MutexConvertCoordinates.unlock();
        }

        m_MutexCoordinateMoment.unlock();
    }
}
