#ifndef PROPERTIES_H
#define PROPERTIES_H
#include <opencv2/core/core.hpp>

class CProperties
{
private:
    //Filterwerte
    int m_HMax;
    int m_HMin;
    int m_SMax;
    int m_SMin;
    int m_VMax;
    int m_VMin;

    int m_Dilate;
    int m_Erode;

    int m_BlubMin;
    int m_BlubMax;
    //Filterwerte

    //Kameraauflösung
    int m_CamHeight;
    int m_CamWight;
    //Kameraauflösung

    //Monitorauflösung
    int m_DisplayHeight;
    int m_DisplayWight;
    //Monitorauflösung

    //
    cv::Point2f m_DisplayCorner[4];

    //Transformmatrix
    cv::Mat m_TransformMatrix;
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
