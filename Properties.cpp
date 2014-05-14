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
    m_MutexHMax.lock();
    int tmp = m_HMax;
    m_MutexHMax.unlock();
    return tmp;
}

int CProperties::get_m_HMin()
{
    m_MutexHMin.lock();
    int tmp = m_HMin;
    m_MutexHMin.unlock();
    return tmp;

}

int CProperties::get_m_SMax()
{
    m_MutexSMax.lock();
    int tmp = m_SMax;
    m_MutexSMax.unlock();
    return tmp;
}

int CProperties::get_m_SMin()
{
    m_MutexSMin.lock();
    int tmp = m_SMin;
    m_MutexSMin.unlock();
    return tmp;
}

int CProperties::get_m_VMax()
{
    m_MutexVMax.lock();
    int tmp = m_VMax;
    m_MutexVMax.unlock();
    return tmp;
}

int CProperties::get_m_VMin()
{
    m_MutexVMin.lock();
    int tmp = m_VMin;
    m_MutexVMin.unlock();
    return tmp;
}

int CProperties::get_m_Dilate()
{
    m_MutexDilate.lock();
    int tmp = m_Dilate;
    m_MutexDilate.unlock();
    return tmp;
}

int CProperties::get_m_Erode()
{
    m_MutexErode.lock();
    int tmp = m_Erode;
    m_MutexErode.unlock();
    return tmp;
}

int CProperties::get_m_BlubMin()
{
    m_MutexBlubMin.lock();
    int tmp = m_BlubMin;
    m_MutexBlubMin.unlock();
    return tmp;
}

int CProperties::get_m_BlubMax()
{
    m_MutexBlubMax.lock();
    int tmp = m_BlubMax;
    m_MutexBlubMax.unlock();
    return tmp;
}

int CProperties::get_m_CamHeight()
{
    m_MutexCamHeight.lock();
    int tmp = m_CamHeight;
    m_MutexCamHeight.unlock();
    return tmp;
}

int CProperties::get_m_CamWight()
{
    m_MutexCamWight.lock();
    int tmp = m_CamWight;
    m_MutexCamWight.unlock();
    return tmp;
}


int CProperties::get_m_DisplayHeight()
{
    m_MutexDisplayHeight.lock();
    int tmp = m_DisplayHeight;
    m_MutexDisplayHeight.unlock();
    return tmp;
}

int CProperties::get_m_DisplayWight()
{
    m_MutexDisplayWight.lock();
    int tmp = m_DisplayWight;
    m_MutexDisplayWight.unlock();
    return tmp;
}

cv::Mat CProperties::get_m_TransformMatrix()
{
    m_MutexTransformMatrix.lock();
    cv::Mat tmp = m_TransformMatrix;
    m_MutexTransformMatrix.unlock();
    return tmp;
}

cv::Point2f CProperties::get_m_DisplaycornerRightTop()
{
    m_MutexDisplayCorner.lock();
    cv::Point2f tmp = m_DisplayCorner[0];
    m_MutexDisplayCorner.unlock();
    return tmp;
}

cv::Point2f CProperties::get_m_DisplaycornerRightBottom()
{
    m_MutexDisplayCorner.lock();
    cv::Point2f tmp = m_DisplayCorner[2];
    m_MutexDisplayCorner.unlock();
    return tmp;
}

cv::Point2f CProperties::get_m_DisplaycornerLeftTop()
{
    m_MutexDisplayCorner.lock();
    cv::Point2f tmp = m_DisplayCorner[1];
    m_MutexDisplayCorner.unlock();
    return tmp;
}

cv::Point2f CProperties::get_m_DisplaycornerLeftBottom()
{
    m_MutexDisplayCorner.lock();
    cv::Point2f tmp = m_DisplayCorner[3];
    m_MutexDisplayCorner.unlock();
    return tmp;
}

////Get-Methoden////


////Set-Methoden////
void CProperties::set_m_HMax(int tmp)
{
    m_MutexHMax.lock();
    m_HMax = tmp;
    m_MutexHMax.unlock();
}

void CProperties::set_m_HMin(int tmp)
{
    m_MutexHMin.lock();
    m_HMin = tmp;
    m_MutexHMin.unlock();
}

void CProperties::set_m_SMax(int tmp)
{
    m_MutexSMax.lock();
    m_SMax = tmp;
    m_MutexSMax.unlock();
}

void CProperties::set_m_SMin(int tmp)
{
    m_MutexSMin.lock();
    m_SMin = tmp;
    m_MutexSMin.unlock();
}

void CProperties::set_m_VMax(int tmp)
{
    m_MutexVMax.lock();
    m_VMax = tmp;
    m_MutexVMax.unlock();
}

void CProperties::set_m_VMin(int tmp)
{
    m_MutexVMin.lock();
    m_VMin = tmp;
    m_MutexVMin.unlock();
}

void CProperties::set_m_Dilate(int tmp)
{
    m_MutexDilate.lock();
    m_Dilate = tmp;
    m_MutexDilate.unlock();
}

void CProperties::set_m_Erode(int tmp)
{
    m_MutexErode.lock();
    m_Erode = tmp;
    m_MutexErode.unlock();
}

void CProperties::set_m_BlubMin(int tmp)
{
    m_MutexBlubMin.lock();
    m_BlubMin = tmp;
    m_MutexBlubMin.unlock();
}

void CProperties::set_m_BlubMax(int tmp)
{
    m_MutexBlubMax.lock();
    m_BlubMax = tmp;
    m_MutexBlubMax.unlock();
}

void CProperties::set_m_CamHeight(int tmp)
{
    m_MutexCamHeight.lock();
    m_CamHeight = tmp;
    m_MutexCamHeight.unlock();
}

void CProperties::set_m_CamWight(int tmp)
{
    m_MutexCamWight.lock();
    m_CamWight = tmp;
    m_MutexCamWight.unlock();
}


void CProperties::set_m_DisplayHeight(int tmp)
{
    m_MutexDisplayHeight.lock();
    m_DisplayHeight = tmp;
    m_MutexDisplayHeight.unlock();
}

void CProperties::set_m_DisplayWight(int tmp)
{
    m_MutexDisplayWight.lock();
    m_DisplayWight = tmp;
    m_MutexDisplayWight.unlock();
}
void CProperties::set_m_DisplaycornerRightTop(cv::Point2f tmp)
{
    m_MutexDisplayCorner.lock();
    m_DisplayCorner[1] = tmp;
    m_MutexDisplayCorner.unlock();
}

void CProperties::set_m_DisplaycornerRightBottom(cv::Point2f tmp)
{
    m_MutexDisplayCorner.lock();
    m_DisplayCorner[3] = tmp;
    m_MutexDisplayCorner.unlock();
}

void CProperties::set_m_DisplaycornerLeftTop(cv::Point2f tmp)
{
    m_MutexDisplayCorner.lock();
    m_DisplayCorner[0] = tmp;
    m_MutexDisplayCorner.unlock();
}
void CProperties::set_m_DisplaycornerLeftBottom(cv::Point2f tmp)
{
    m_MutexDisplayCorner.lock();
    m_DisplayCorner[2] = tmp;
    m_MutexDisplayCorner.unlock();
}

void CProperties::set_m_TransformMatrix(cv::Mat tmp)
{
    m_MutexTransformMatrix.lock();
    tmp.copyTo(m_TransformMatrix);
    m_MutexTransformMatrix.unlock();
}

////Set-Methoden////


void CProperties::loadData()
{
    cv::FileStorage file;

    file.open("Properties.yml", cv::FileStorage::READ);

    if(file.isOpened())
    {
        m_MutexHMax.lock();
        file["Filter_HMax"] >> m_HMax;
        m_MutexHMax.unlock();
        m_MutexHMin.lock();
        file["Filter_HMin"] >> m_HMin;
        m_MutexHMin.unlock();
        m_MutexSMax.lock();
        file["Filter_SMax"] >> m_SMax;
        m_MutexSMax.unlock();
        m_MutexSMin.lock();
        file["Filter_SMin"] >> m_SMin;
        m_MutexSMin.unlock();
        m_MutexVMax.lock();
        file["Fitler_VMax"] >> m_VMax;
        m_MutexVMax.unlock();
        m_MutexVMin.lock();
        file["Filter_VMin"] >> m_VMin;
        m_MutexVMin.unlock();

        m_MutexDilate.lock();
        file["Filter_Dilate"] >> m_Dilate;
        m_MutexDilate.unlock();
        m_MutexErode.lock();
        file["Filter_Erode"] >> m_Erode;
        m_MutexErode.unlock();

        m_MutexBlubMin.lock();
        file["Filter_BlubMin"] >> m_BlubMin;
        m_MutexBlubMin.unlock();
        m_MutexBlubMax.lock();
        file["Filter_BlubMax"] >> m_BlubMax;
        m_MutexBlubMax.unlock();
              //Filterwerte

              //Kameraauflösung
        m_MutexCamHeight.lock();
        file["CamHeight"] >>  m_CamHeight;
        m_MutexCamHeight.unlock();
        m_MutexCamWight.lock();
        file["CamWight"] >> m_CamWight;
        m_MutexCamWight.unlock();
              //Kameraauflösung

              //Monitorauflösung
        m_MutexDisplayHeight.lock();
        file["DisplayHeight"] >> m_DisplayHeight;
        m_MutexDisplayHeight.unlock();
        m_MutexDisplayWight.lock();
        file["DisplayWight"] >> m_DisplayWight;
        m_MutexDisplayWight.unlock();
              //Monitorauflösung

        m_MutexDisplayCorner.lock();
        file["Displaycorner0"] >> m_DisplayCorner[0].x;
        file["Displaycorner1"] >> m_DisplayCorner[1].x;
        file["Displaycorner2"] >> m_DisplayCorner[2].x;
        file["Displaycorner3"] >> m_DisplayCorner[3].x;

        file["Displaycorner0y"] >> m_DisplayCorner[0].y;
        file["Displaycorner1y"] >> m_DisplayCorner[1].y;
        file["Displaycorner2y"] >> m_DisplayCorner[2].y;
        file["Displaycorner3y"] >> m_DisplayCorner[3].y;
        m_MutexDisplayCorner.unlock();
              //Monitorecken Koordinaten
        m_MutexTransformMatrix.lock();
        file["TransformMatrix"] >> m_TransformMatrix;
        m_MutexTransformMatrix.unlock();
              //Monitorecken Koordinaten
        file.release();
    }
    else
    {
        //Filterwerte
        m_MutexHMax.lock();
        m_HMax = 256;
        m_MutexHMax.unlock();
        m_MutexHMin.lock();
        m_HMin = 0;
        m_MutexHMin.unlock();
        m_MutexSMax.lock();
        m_SMax = 256;
        m_MutexSMax.unlock();
        m_MutexSMin.lock();
        m_SMin = 0;
        m_MutexSMin.unlock();
        m_MutexVMax.lock();
        m_VMax = 256;
        m_MutexVMax.unlock();
        m_MutexVMin.lock();
        m_VMin = 0;
        m_MutexVMin.unlock();

        m_MutexDilate.lock();
        m_Dilate = 1;
        m_MutexDilate.unlock();
        m_MutexErode.lock();
        m_Erode  = 1;
        m_MutexErode.unlock();

        m_MutexBlubMin.lock();
        m_BlubMin = 0;
        m_MutexBlubMin.unlock();
        m_MutexBlubMax.lock();
        m_BlubMax = 100;
        m_MutexBlubMax.unlock();
        //Filterwerte

        //Kameraauflösung
        m_MutexCamHeight.lock();
        m_CamHeight = 720;
        m_MutexCamHeight.unlock();
        m_MutexCamWight.lock();
        m_CamWight = 1280;
        m_MutexCamWight.unlock();
              //Kameraauflösung

              //Monitorauflösung
        m_MutexDisplayHeight.lock();
        m_DisplayHeight = 800;
        m_MutexDisplayHeight.unlock();
        m_MutexDisplayWight.lock();
        m_DisplayWight = 1280;
        m_MutexDisplayWight.unlock();
        //Monitorauflösung

        //Monitorecken Koordinaten
        m_MutexTransformMatrix.lock();
        m_TransformMatrix.create(2,3,CV_32FC1);
        m_MutexTransformMatrix.unlock();
        //Monitorecken Koordinaten
    }

}

bool CProperties::saveData()
{
    cv::FileStorage file("Properties.yml", cv::FileStorage::WRITE);

    if(file.isOpened())
    {
        //Filterwerte
        m_MutexHMax.lock();
        file << "Filter_HMax" << m_HMax;
        m_MutexHMax.unlock();
        m_MutexHMin.lock();
        file << "Filter_HMin" << m_HMin;
        m_MutexHMin.unlock();
        m_MutexSMax.lock();
        file << "Filter_SMax" << m_SMax;
        m_MutexSMax.unlock();
        m_MutexSMin.lock();
        file << "Filter_SMin" << m_SMin;
        m_MutexSMin.unlock();
        m_MutexVMax.lock();
        file << "Fitler_VMax" << m_VMax;
        m_MutexVMax.unlock();
        m_MutexVMin.lock();
        file << "Filter_VMin" << m_VMin;
        m_MutexVMin.unlock();

        m_MutexDilate.lock();
        file << "Filter_Dilate" << m_Dilate;
        m_MutexDilate.unlock();
        m_MutexErode.lock();
        file << "Filter_Erode" << m_Erode;
        m_MutexErode.unlock();

        m_MutexBlubMin.lock();
        file << "Filter_BlubMin" << m_BlubMin;
        m_MutexBlubMin.unlock();
        m_MutexBlubMax.lock();
        file << "Filter_BlubMax" << m_BlubMax;
        m_MutexBlubMax.unlock();
        //Filterwerte

        //Kameraauflösung
        m_MutexCamHeight.lock();
        file << "CamHeight" <<  m_CamHeight;
        m_MutexCamHeight.unlock();
        m_MutexCamWight.lock();
        file << "CamWight" << m_CamWight;m_MutexCamWight.unlock();
        //Kameraauflösung

        //Monitorauflösung
        m_MutexDisplayHeight.lock();
        file << "DisplayHeight" << m_DisplayHeight;
        m_MutexCamHeight.unlock();
        m_MutexCamWight.lock();
        file << "DisplayWight" << m_DisplayWight;
        m_MutexCamWight.unlock();
        //Monitorauflösung

        //Monitorecken Koordinaten
        m_MutexDisplayCorner.lock();
        file << "Displaycorner0" << m_DisplayCorner[0].x;
        file << "Displaycorner1" << m_DisplayCorner[1].x;
        file << "Displaycorner2" << m_DisplayCorner[2].x;
        file << "Displaycorner3" << m_DisplayCorner[3].x;

        file << "Displaycorner0y" << m_DisplayCorner[0].y;
        file << "Displaycorner1y" << m_DisplayCorner[1].y;
        file << "Displaycorner2y" << m_DisplayCorner[2].y;
        file << "Displaycorner3y" << m_DisplayCorner[3].y;
        m_MutexDisplayCorner.unlock();
        //Monitorecken Koordinaten

        m_MutexTransformMatrix.lock();
        file << "TransformMatrix" << m_TransformMatrix;
        m_MutexTransformMatrix.unlock();

        file.release();
        return true;
    }
    else
        return false;

}
