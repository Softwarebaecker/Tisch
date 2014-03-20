#ifndef TRACKING_H
#define TRACKING_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QDesktopWidget>
#include <Properties.h>

class CTracking
{
private:
    cv::VideoCapture m_Webcam;

    cv::Mat m_webcamFrame;
    cv::Mat m_webcamFrameInRange;
    cv::Mat m_webcamFrameErode;
    cv::Mat m_webcamFrameDilate;

    cv::vector<cv::Point2f> m_CoordinateMoment;

    CProperties m_Properties;

public:
    CTracking();
    ~CTracking();

    bool openWebcam();              //öffnet die Kamera
    bool closeWebcam();             //schließt die Kamera

    void convertFrame();            //konvertiert das Bild
    bool tracking();                //sucht die größte Berührung heraus
    bool convertCoordinate();       //konvertiert die Koordinaten der Kamera in Bildschirmkoordinaten
    void drawcoordinates();          //zeichnet einen Kreis um die Berührung


    ////Get-Methoden////
    cv::Mat get_m_webcamFrame();
    cv::Mat get_m_webcamFrameDiff();
    cv::Mat get_m_webcamFrameInRange();
    cv::Mat get_m_webcamFrameErode();
    cv::Mat get_m_webcamFrameDilate();
    cv::Point2f get_m_CoordinateMoment(int pos);
    CProperties* get_m_Properties();
    ////Get-Methoden////

};

#endif // TRACKING_H
