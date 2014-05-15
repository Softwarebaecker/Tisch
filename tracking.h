#ifndef TRACKING_H
#define TRACKING_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QDesktopWidget>
#include <QThread>
#include <QMutex>
#include "Properties.h"

class CTracking : public QThread
{
private:
    cv::VideoCapture m_Webcam;

    cv::Mat m_webcamFrame;
    cv::Mat m_webcamFrameInRange;
    cv::Mat m_webcamFrameErode;
    cv::Mat m_webcamFrameDilate;
    cv::Mat m_WebcamFrameDraw;

    cv::vector<cv::Point2f> m_CoordinateMoment;

    CProperties m_Properties;

    QMutex m_MutexWebcamFrame;
    QMutex m_MutexWebcamFrameInRange;
    QMutex m_MutexWebcamFrameErode;
    QMutex m_MutexWebcamFrameDilate;
    QMutex m_MutexWebcamFrameDraw;
    QMutex m_MutexCoordinateMoment;
    QMutex m_MutexProperties;
    QMutex m_MutexStop;
    QMutex m_MutexDrawcoordinates;
    QMutex m_MutexConvertCoordinates;

    bool m_stop;
    bool m_drawcoordinates;
    bool m_convertCoordinates;


public:
    CTracking();
    ~CTracking();

    bool openWebcam();              //öffnet die Kamera
    bool closeWebcam();             //schließt die Kamera

    void convertFrame();            //konvertiert das Bild
    bool tracking();                //sucht die größte Berührung heraus
    void convertCoordinate();       //konvertiert die Koordinaten der Kamera in Bildschirmkoordinaten
    void drawcoordinates();          //zeichnet einen Kreis um die Berührung

    void stopThread();
    void set_drawcoordinates(bool);
    void set_convertCoordinates(bool);

    ////Get-Methoden////
    cv::Mat get_m_webcamFrame();
    cv::Mat get_m_webcamFrameDiff();
    cv::Mat get_m_webcamFrameInRange();
    cv::Mat get_m_webcamFrameErode();
    cv::Mat get_m_webcamFrameDilate();
    cv::Mat get_m_webcamFrameDraw();
    cv::Point2f get_m_CoordinateMoment(unsigned int pos);
    int get_m_CoordinateMoment_number();
    CProperties* get_m_Properties();
    ////Get-Methoden////

public slots:

    void run();

};

#endif // TRACKING_H
