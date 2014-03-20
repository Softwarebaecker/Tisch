#include "calibrationwindow.h"
#include "ui_calibrationwindow.h"
#include "QMessageBox"

CCalibrationwindow::CCalibrationwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CCalibrationwindow)
{
    ui->setupUi(this);

    showFullScreen();   //das Fenster im Vollbild anzeigen

    if(m_Stream.openWebcam() == true)   //Webcam öffnen
    {

    }
    else
    {
        QMessageBox warning;
        warning.setText("Achtung!!\n Kamera konnte nicht geöffnet werden!");
        warning.exec();

        exit(1);
    }

}

CCalibrationwindow::~CCalibrationwindow()
{
    delete ui;
}

void CCalibrationwindow::updateGUI()
{
    QPixmap img;
    cv::Point2f srcQaud[4], dstQuad[4];

    //setzen der Koordinaten der Bildschirmecken
    dstQuad[0].x = 0;
    dstQuad[0].y = 0;
    dstQuad[1].x = 1280;
    dstQuad[1].y = 0;
    dstQuad[2].x = 0;
    dstQuad[2].y = 720;
    dstQuad[3].x = 1280;
    dstQuad[3].y = 720;
    //setzen der Koordinaten der Bildschirmecken

    for(int i = 0; i < 4; i++)
    {   

        do  //wartet solange, bis es keine Berührung der Scheibe gibt
        {
            cv::waitKey(20);    //wartet 20 ms
            m_Stream.convertFrame();
        }while(m_Stream.tracking());      

        //Bild einfügen
        switch (i) {
        case 0:
            img.load("./Kalibrationsbilder/Kalibrierungsbild_Links_Oben.png");
            ui->label->setPixmap(img);
            break;
        case 1:
            img.load("./Kalibrationsbilder/Kalibrierungsbild_Rechts_Oben.png");
            ui->label->setPixmap(img);
            break;
        case 2:
            img.load("./Kalibrationsbilder/Kalibrierungsbild_Links_Unten.png");
            ui->label->setPixmap(img);
            break;
        case 3:
            img.load("./Kalibrationsbilder/Kalibrierungsbild_Rechts_Unten.png");
            ui->label->setPixmap(img);
            break;
        default:
            break;
        }
        //Bild einfügen
        cv::waitKey(20);    //wartet 20ms

        while(true) //Endlosschleife, bricht ab, sobald eine Berührung der Platte aufhört
        {
            m_Stream.convertFrame();
            if(m_Stream.tracking() == true)
            {
                switch (i)  //überprüft, um welche Bildschirmecke es sich handelt
                {
                    case 0:
                        srcQaud[0]= m_Stream.get_m_CoordinateMoment(0); //ruft die letzten Kamerakoordinaten ab
                        m_Stream.get_m_Properties()->set_m_DisplaycornerLeftTop(srcQaud[0]); //schreibt die Kamerakoordinaten in die Propertie-Klasse
                        break;
                    case 1:

                        srcQaud[1] = m_Stream.get_m_CoordinateMoment(0);//ruft die letzten Kamerakoordinaten ab
                        m_Stream.get_m_Properties()->set_m_DisplaycornerRightTop(srcQaud[1]);//schreibt die Kamerakoordinaten in die Propertie-Klasse
                        break;
                    case 2:

                        srcQaud[2] = m_Stream.get_m_CoordinateMoment(0);//ruft die letzten Kamerakoordinaten ab
                        m_Stream.get_m_Properties()->set_m_DisplaycornerLeftBottom(srcQaud[2]);//schreibt die Kamerakoordinaten in die Propertie-Klasse
                        break;
                    case 3:

                        srcQaud[3] = m_Stream.get_m_CoordinateMoment(0);//ruft die letzten Kamerakoordinaten ab
                        m_Stream.get_m_Properties()->set_m_DisplaycornerRightBottom(srcQaud[3]);//schreibt die Kamerakoordinaten in die Propertie-Klasse
                        break;
                    default:
                        break;
                }

                while(m_Stream.tracking())  //wartet solange, bis es keine Berührung der Scheibe gibt
                {
                    m_Stream.convertFrame();
                }

                break;
            }


        }

    }
    m_Stream.get_m_Properties()->set_m_TransformMatrix(cv::getPerspectiveTransform(srcQaud,dstQuad));   //erstellt eine Matrix für die Perspektive Transformation und speichet diese in der Propertie-Klasse ab
    m_Stream.get_m_Properties()->saveData();    //speichert die Propertie-Klasse in eine Datei
    close();    //schließt das Fenster
}
