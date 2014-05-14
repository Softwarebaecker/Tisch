#include "pongwindow.h"
#include "ui_pongwindow.h"

CPongWindow::CPongWindow(CTracking* stream,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CPongWindow)
{
    ui->setupUi(this);
    m_Stream = stream;

    m_TimerTracking = new QTimer(this);
    connect(m_TimerTracking,SIGNAL(timeout()),this,SLOT(UpdateTracking()));



    m_LeftPannel = new Pannel(ui->Panel_Left);
    m_RightPannel = new Pannel(ui->Panel_Right);
    m_Ball = new Ball(ui->Ball, m_LeftPannel, m_RightPannel);

    connect(m_Ball, &Ball::finished, this, &CPongWindow::Update);

    StartMenue();

    this->setWindowState(Qt::WindowFullScreen);

}

CPongWindow::~CPongWindow()
{
    delete m_LeftPannel;
    delete m_RightPannel;
    delete m_Ball;
    delete ui;
}

void CPongWindow::Update()
{
    StartMenue();
}

void CPongWindow::UpdateTracking()
{

    if(m_Stream->get_m_CoordinateMoment_number()!=0)
    {
        int anzahl = m_Stream->get_m_CoordinateMoment_number();

        //Berührungen bearbeiten
        for(int i = 0; i < anzahl; i++)
        {
            if(m_Stream->get_m_CoordinateMoment(i).x - this->pos().x() < this->width()/2)
            {
                m_LeftPannel->SetPosition(m_Stream->get_m_CoordinateMoment(i).y-this->pos().y());
                continue;
            }
            else
            {
                m_RightPannel->SetPosition(m_Stream->get_m_CoordinateMoment(i).y-this->pos().y());
                continue;
            }
        }

    }
}

void CPongWindow::on_button_starte_clicked()
{
    //spiel soll gestartet werden
    ui->button_starte->setVisible(false);
    ui->button_benden->setVisible(false);
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);

    ui->Ball->setVisible(true);
    ui->Panel_Left->setVisible(true);
    ui->Panel_Right->setVisible(true);
    m_Ball->SetStart();
    m_TimerTracking->start(100);
    m_Ball->start();
}


void CPongWindow::StartMenue()
{
    m_TimerTracking->stop();

    //menue soll wieder angezeigt werden
    ui->button_starte->setVisible(true);
    ui->button_benden->setVisible(true);
    ui->label->setVisible(true);
    ui->label_2->setVisible(true);
    ui->label_3->setVisible(true);

    ui->Ball->setVisible(false);
    ui->Panel_Left->setVisible(false);
    ui->Panel_Right->setVisible(false);
}

void CPongWindow::on_button_benden_clicked()
{
    close();
}
