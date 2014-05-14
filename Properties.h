#ifndef PROPERTIES_H
#define PROPERTIES_H
#include <opencv2/core/core.hpp>
#include <QMutex>

class CProperties
{
private:
    //Filterwerte
    int m_HMax;
    QMutex m_MutexHMax;
    int m_HMin;
    QMutex m_MutexHMin;
    int m_SMax;
    QMutex m_MutexSMax;
    int m_SMin;
    QMutex m_MutexSMin;
    int m_VMax;
    QMutex m_MutexVMax;
    int m_VMin;
    QMutex m_MutexVMin;

    int m_Dilate;
    QMutex m_MutexDilate;
    int m_Erode;
    QMutex m_MutexErode;

    int m_BlubMin;
    QMutex m_MutexBlubMin;
    int m_BlubMax;
    QMutex m_MutexBlubMax;
    //Filterwerte

    //Kameraauflösung
    int m_CamHeight;
    QMutex m_MutexCamHeight;
    int m_CamWight;
    QMutex m_MutexCamWight;
    //Kameraauflösung

    //Monitorauflösung
    int m_DisplayHeight;
    QMutex m_MutexDisplayHeight;
    int m_DisplayWight;
    QMutex m_MutexDisplayWight;
    //Monitorauflösung

    //
    cv::Point2f m_DisplayCorner[4];
    QMutex m_MutexDisplayCorner;

    //Transformmatrix
    cv::Mat m_TransformMatrix;
    QMutex m_MutexTransformMatrix;
    //Transformmatrix
public:
    CProperties();
    ~CProperties();


    ////Get-Methoden////
    int get_m_HMax();
    int get_m_HMin();
    int get_m_SMax();
    int get_m_SMin();
    int get_m_VMax();
    int get_m_VMin();

    int get_m_Dilate();
    int get_m_Erode();

    int get_m_BlubMin();
    int get_m_BlubMax();

    int get_m_CamHeight();
    int get_m_CamWight();

    int get_m_DisplayHeight();
    int get_m_DisplayWight();

    cv::Point2f get_m_DisplaycornerRightTop();
    cv::Point2f get_m_DisplaycornerRightBottom();
    cv::Point2f get_m_DisplaycornerLeftTop();
    cv::Point2f get_m_DisplaycornerLeftBottom();

    cv::Mat get_m_TransformMatrix();
    ////Get-Methoden////


    ////Set-Methoden////
    void set_m_HMax(int);
    void set_m_HMin(int);
    void set_m_SMax(int);
    void set_m_SMin(int);
    void set_m_VMax(int);
    void set_m_VMin(int);

    void set_m_Dilate(int);
    void set_m_Erode(int);

    void set_m_BlubMin(int);
    void set_m_BlubMax(int);

    void set_m_CamHeight(int);
    void set_m_CamWight(int);

    void set_m_DisplayHeight(int);
    void set_m_DisplayWight(int);

    void set_m_DisplaycornerRightTop(cv::Point2f);
    void set_m_DisplaycornerRightBottom(cv::Point2f);
    void set_m_DisplaycornerLeftTop(cv::Point2f);
    void set_m_DisplaycornerLeftBottom(cv::Point2f);

    void set_m_TransformMatrix(cv::Mat);
    ////Set-Methoden////

    void loadData();        //liest die Einstellungen aus der Datei
    bool saveData();        //schreibt die Einstellungen in die Datei
};

#endif // PROPERTIES_H
