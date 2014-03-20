#include "Properties.h"
#include <fstream>
#include <iostream>
#define FILENAME "Properties.txt"

using namespace std;

CProperties::CProperties()
{
    loadData();
}

CProperties::~CProperties()
{

}


////Get-Methoden////
int CProperties::get_m_HMax()
{
    return m_HMax;
}

int CProperties::get_m_HMin()
{
    return m_HMin;

}

int CProperties::get_m_SMax()
{
    return m_SMax;
}

int CProperties::get_m_SMin()
{
    return m_SMin;
}

int CProperties::get_m_VMax()
{
    return m_VMax;
}

int CProperties::get_m_VMin()
{
    return m_VMin;
}

int CProperties::get_m_Dilate()
{
    return m_Dilate;
}

int CProperties::get_m_Erode()
{
    return m_Erode;
}

int CProperties::get_m_BlubMin()
{
    return m_BlubMin;
}

int CProperties::get_m_BlubMax()
{
    return m_BlubMax;
}

int CProperties::get_m_CamHeight()
{
    return m_CamHeight;
}

int CProperties::get_m_CamWight()
{
    return m_CamWight;
}


int CProperties::get_m_DisplayHeight()
{
    return m_DisplayHeight;
}

int CProperties::get_m_DisplayWight()
{
    return m_DisplayWight;
}

cv::Mat CProperties::get_m_TransformMatrix()
{
    return m_TransformMatrix;
}

cv::Point2f CProperties::get_m_DisplaycornerRightTop()
{
    return m_DisplayCorner[0];
}

cv::Point2f CProperties::get_m_DisplaycornerRightBottom()
{
    return m_DisplayCorner[2];
}

cv::Point2f CProperties::get_m_DisplaycornerLeftTop()
{
    return m_DisplayCorner[1];
}

cv::Point2f CProperties::get_m_DisplaycornerLeftBottom()
{
    return m_DisplayCorner[3];
}

////Get-Methoden////


////Set-Methoden////
void CProperties::set_m_HMax(int tmp)
{
    m_HMax = tmp;
}

void CProperties::set_m_HMin(int tmp)
{
    m_HMin = tmp;
}

void CProperties::set_m_SMax(int tmp)
{
    m_SMax = tmp;
}

void CProperties::set_m_SMin(int tmp)
{
    m_SMin = tmp;
}

void CProperties::set_m_VMax(int tmp)
{
    m_VMax = tmp;
}

void CProperties::set_m_VMin(int tmp)
{
    m_VMin = tmp;
}

void CProperties::set_m_Dilate(int tmp)
{
    m_Dilate = tmp;
}

void CProperties::set_m_Erode(int tmp)
{
    m_Erode = tmp;
}

void CProperties::set_m_BlubMin(int tmp)
{
    m_BlubMin = tmp;
}

void CProperties::set_m_BlubMax(int tmp)
{
    m_BlubMax = tmp;
}

void CProperties::set_m_CamHeight(int tmp)
{
    m_CamHeight = tmp;
}

void CProperties::set_m_CamWight(int tmp)
{
    m_CamWight = tmp;
}


void CProperties::set_m_DisplayHeight(int tmp)
{
    m_DisplayHeight = tmp;
}

void CProperties::set_m_DisplayWight(int tmp)
{
    m_DisplayWight = tmp;
}
void CProperties::set_m_DisplaycornerRightTop(cv::Point2f tmp)
{
    m_DisplayCorner[1] = tmp;
}

void CProperties::set_m_DisplaycornerRightBottom(cv::Point2f tmp)
{
    m_DisplayCorner[3] = tmp;
}

void CProperties::set_m_DisplaycornerLeftTop(cv::Point2f tmp)
{
    m_DisplayCorner[0] = tmp;
}
void CProperties::set_m_DisplaycornerLeftBottom(cv::Point2f tmp)
{
    m_DisplayCorner[2] = tmp;
}

void CProperties::set_m_TransformMatrix(cv::Mat tmp)
{
    tmp.copyTo(m_TransformMatrix);
}

////Set-Methoden////


void CProperties::loadData()
{
    cv::FileStorage file;

    file.open("Properties.yml", cv::FileStorage::READ);

    if(file.isOpened())
    {
        file["Filter_HMax"] >> m_HMax;
        file["Filter_HMin"] >> m_HMin;
        file["Filter_SMax"] >> m_SMax;
        file["Filter_SMin"] >> m_SMin;
        file["Fitler_VMax"] >> m_VMax;
        file["Filter_VMin"] >> m_VMin;

        file["Filter_Dilate"] >> m_Dilate;
        file["Filter_Erode"] >> m_Erode;

        file["Filter_BlubMin"] >> m_BlubMin;
        file["Filter_BlubMax"] >> m_BlubMax;
              //Filterwerte

              //Kameraauflösung
        file["CamHeight"] >>  m_CamHeight;
        file["CamWight"] >> m_CamWight;
              //Kameraauflösung

              //Monitorauflösung
        file["DisplayHeight"] >> m_DisplayHeight;
        file["DisplayWight"] >> m_DisplayWight;
              //Monitorauflösung

        file["Displaycorner0"] >> m_DisplayCorner[0].x;
        file["Displaycorner1"] >> m_DisplayCorner[1].x;
        file["Displaycorner2"] >> m_DisplayCorner[2].x;
        file["Displaycorner3"] >> m_DisplayCorner[3].x;

        file["Displaycorner0y"] >> m_DisplayCorner[0].y;
        file["Displaycorner1y"] >> m_DisplayCorner[1].y;
        file["Displaycorner2y"] >> m_DisplayCorner[2].y;
        file["Displaycorner3y"] >> m_DisplayCorner[3].y;
              //Monitorecken Koordinaten
        file["TransformMatrix"] >> m_TransformMatrix;
              //Monitorecken Koordinaten
        file.release();
    }
    else
    {
        //Filterwerte
        m_HMax = 256;
        m_HMin = 0;
        m_SMax = 256;
        m_SMin = 0;
        m_VMax = 256;
        m_VMin = 0;

        m_Dilate = 0;
        m_Erode  = 0;

        m_BlubMin = 0;
        m_BlubMax = 100;
        //Filterwerte

        //Kameraauflösung
        m_CamHeight = 720;
        m_CamWight = 1280;
        //Kameraauflösung

        //Monitorauflösung
        m_DisplayHeight = 720;
        m_DisplayWight = 1280;
        //Monitorauflösung

        //Monitorecken Koordinaten
        m_TransformMatrix.create(2,3,CV_32FC1);
        //Monitorecken Koordinaten
    }

}

bool CProperties::saveData()
{
    cv::FileStorage file("Properties.yml", cv::FileStorage::WRITE);

    if(file.isOpened())
    {
        //Filterwerte
        file << "Filter_HMax" << m_HMax;
        file << "Filter_HMin" << m_HMin;
        file << "Filter_SMax" << m_SMax;
        file << "Filter_SMin" << m_SMin;
        file << "Fitler_VMax" << m_VMax;
        file << "Filter_VMin" << m_VMin;

        file << "Filter_Dilate" << m_Dilate;
        file << "Filter_Erode" << m_Erode;

        file << "Filter_BlubMin" << m_BlubMin;
        file << "Filter_BlubMax" << m_BlubMax;
        //Filterwerte

        //Kameraauflösung
        file << "CamHeight" <<  m_CamHeight;
        file << "CamWight" << m_CamWight;
        //Kameraauflösung

        //Monitorauflösung
        file << "DisplayHeight" << m_DisplayHeight;
        file << "DisplayWight" << m_DisplayWight;
        //Monitorauflösung

        //Monitorecken Koordinaten
        file << "Displaycorner0" << m_DisplayCorner[0].x;
        file << "Displaycorner1" << m_DisplayCorner[1].x;
        file << "Displaycorner2" << m_DisplayCorner[2].x;
        file << "Displaycorner3" << m_DisplayCorner[3].x;

        file << "Displaycorner0y" << m_DisplayCorner[0].y;
        file << "Displaycorner1y" << m_DisplayCorner[1].y;
        file << "Displaycorner2y" << m_DisplayCorner[2].y;
        file << "Displaycorner3y" << m_DisplayCorner[3].y;
        //Monitorecken Koordinaten

        file << "TransformMatrix" << m_TransformMatrix;

        file.release();
        return true;
    }
    else
        return false;

}
