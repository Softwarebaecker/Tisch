#include "propertieswindow.h"
#include "ui_propertieswindow.h"
#include <QMessageBox>


CPropertiesWindow::CPropertiesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CPropertiesWindow)
{
    ui->setupUi(this);


    //Werte der Trackbars setzen
    ui->slider_H_MAX->setValue(m_Stream.get_m_Properties()->get_m_HMax());
    ui->slider_H_MIN->setValue(m_Stream.get_m_Properties()->get_m_HMin());
    ui->slider_S_MAX->setValue(m_Stream.get_m_Properties()->get_m_SMax());
    ui->slider_S_MIN->setValue(m_Stream.get_m_Properties()->get_m_SMin());
    ui->slider_V_MAX->setValue(m_Stream.get_m_Properties()->get_m_VMax());
    ui->slider_V_MIN->setValue(m_Stream.get_m_Properties()->get_m_VMin());

    ui->dial_Dilate->setValue(m_Stream.get_m_Properties()->get_m_Dilate());
    ui->dial_Erode->setValue(m_Stream.get_m_Properties()->get_m_Erode());

    ui->slider_BLUB_MIN->setValue(m_Stream.get_m_Properties()->get_m_BlubMin());
    ui->slider_BLUB_MAX->setValue(m_Stream.get_m_Properties()->get_m_BlubMax());
    //Werte der Trackbars setzen


    //Kamerastream öffnen
    if(m_Stream.openWebcam() == true)
    {

        m_Timer = new QTimer(this); //Timer erstellen


        connect(m_Timer, SIGNAL(timeout()), this, SLOT(updateGUI()));      //Timer mit Funktion verbinden


        m_Timer->start(20); //Timer starten
    }
    else
    {
        //Fehlermelder ausgeben
        QMessageBox warning;
        warning.setText("Achtung!!\n Kamera konnte nicht geöffnet werden!");
        warning.exec();
        //Fehlermelder ausgeben

        exit(1);
    }
}

CPropertiesWindow::~CPropertiesWindow()
{
    delete ui;

}

void CPropertiesWindow::updateGUI()
{
    //analysiert einen Frame
    m_Stream.convertFrame();
    QString coordinats;

    coordinats.clear();

    if(m_Stream.tracking())
    {
        //Koordinaten in Image zeichnen
        m_Stream.drawcoordinates();

        //Koordinaten ausgeben
        coordinats.sprintf("X : %02d , Y : %02d",(int)m_Stream.get_m_CoordinateMoment(0).x,(int)m_Stream.get_m_CoordinateMoment(0).y);
        ui->textEdit->append(coordinats);

    }

    //Originalbild
    //Bild von cv::MAT in QImage
    QImage tempCam((uchar*)m_Stream.get_m_webcamFrame().data, m_Stream.get_m_webcamFrame().cols, m_Stream.get_m_webcamFrame().rows, QImage::Format_RGB888 );
    //Bild skalieren für Fenster
    tempCam = tempCam.scaled(320,240,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //Bild in UI ausgeben
    ui->image_cam->setPixmap(QPixmap::fromImage(tempCam));

    //Bild nach inRange Filter
    //Bild von cv::MAT in QImage
    QImage tempInRange((uchar*)m_Stream.get_m_webcamFrameInRange().data, m_Stream.get_m_webcamFrameInRange().cols, m_Stream.get_m_webcamFrameInRange().rows, QImage::Format_Indexed8 );
    //Bild skalieren für Fenster
    tempInRange = tempInRange.scaled(320,240,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //Bild in UI ausgeben
    ui->image_inRange->setPixmap(QPixmap::fromImage(tempInRange));

    //Bild nach dem Dilate Filter
    //Bild von cv::MAT in QImage
    QImage tempDilate((uchar*)m_Stream.get_m_webcamFrameDilate().data, m_Stream.get_m_webcamFrameDilate().cols, m_Stream.get_m_webcamFrameDilate().rows, QImage::Format_Indexed8 );
    //Bild skalieren für Fenster
    tempDilate = tempDilate.scaled(320,240,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //Bild in UI ausgeben
    ui->image_Dilate->setPixmap(QPixmap::fromImage(tempDilate));

    //Bild nach dem Erode Filter
    //Bild von cv::MAT in QImage
    QImage tempErode((uchar*)m_Stream.get_m_webcamFrameErode().data, m_Stream.get_m_webcamFrameErode().cols, m_Stream.get_m_webcamFrameErode().rows, QImage::Format_Indexed8 );
    //Bild skalieren für Fenster
    tempErode = tempErode.scaled(320,240,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //Bild in UI ausgeben
    ui->image_Erode->setPixmap(QPixmap::fromImage(tempErode));
}

void CPropertiesWindow::on_button_OK_clicked()
{
    //Einstellungen speichern
    m_Stream.get_m_Properties()->saveData();

    //Timer deaktivieren
    if(m_Timer->isActive() == true)
    {
        m_Timer->stop();
        delete m_Timer;
    }

    if(!m_Stream.closeWebcam())
    {
        //Fehlermeldung ausgeben
        QMessageBox warning;
        warning.setText("Achtung!!\n Kamera konnte nicht geschlossen werden!");
        warning.exec();
        //Fehlermeldung ausgeben

        exit(1);
    }

    close();
}

void CPropertiesWindow::on_button_cancel_clicked()
{
    //Timer deaktivieren
    if(m_Timer->isActive() == true)
    {
        m_Timer->stop();    //Timer anhalten
        delete m_Timer;     //Timer löschen
    }

    if(!m_Stream.closeWebcam())
    {
        //Fehlermeldung ausgeben
        QMessageBox warning;
        warning.setText("Achtung!!\n Kamera konnte nicht geschlossen werden!");
        warning.exec();
        //Fehlermeldung ausgeben

        exit(1);
    }
    close();
}

void CPropertiesWindow::on_button_reset_clicked()
{
    ui->slider_H_MAX->setValue(256);
    ui->slider_H_MIN->setValue(0);
    ui->slider_S_MAX->setValue(256);
    ui->slider_S_MIN->setValue(0);
    ui->slider_V_MAX->setValue(256);
    ui->slider_V_MIN->setValue(0);

    ui->dial_Dilate->setValue(0);
    ui->dial_Erode->setValue(0);

    ui->slider_BLUB_MIN->setValue(0);
    ui->slider_BLUB_MAX->setValue(100);

}


///Slider change////
void CPropertiesWindow::on_slider_H_MIN_valueChanged(int value)
{
    m_Stream.get_m_Properties()->set_m_HMin(value);
}

void CPropertiesWindow::on_slider_H_MAX_valueChanged(int value)
{
    m_Stream.get_m_Properties()->set_m_HMax(value);
}

void CPropertiesWindow::on_slider_S_MIN_valueChanged(int value)
{
    m_Stream.get_m_Properties()->set_m_SMin(value);
}

void CPropertiesWindow::on_slider_S_MAX_valueChanged(int value)
{
    m_Stream.get_m_Properties()->set_m_SMax(value);
}

void CPropertiesWindow::on_slider_V_MIN_valueChanged(int value)
{
    m_Stream.get_m_Properties()->set_m_VMin(value);
}

void CPropertiesWindow::on_slider_V_MAX_valueChanged(int value)
{
    m_Stream.get_m_Properties()->set_m_VMax(value);
}
///Slider change////


///Dial change////
void CPropertiesWindow::on_dial_Erode_valueChanged(int value)
{
    m_Stream.get_m_Properties()->set_m_Erode(value);
}

void CPropertiesWindow::on_dial_Dilate_valueChanged(int value)
{
    m_Stream.get_m_Properties()->set_m_Dilate(value);
}
///Dial change////

void CPropertiesWindow::on_slider_BLUB_MAX_valueChanged(int value)
{
    m_Stream.get_m_Properties()->set_m_BlubMax(value);
}

void CPropertiesWindow::on_slider_BLUB_MIN_valueChanged(int value)
{
    m_Stream.get_m_Properties()->set_m_BlubMin(value);
}

