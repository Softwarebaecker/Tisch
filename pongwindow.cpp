#include "pongwindow.h"
#include "ui_pongwindow.h"

CPongWindow::CPongWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CPongWindow)
{
    ui->setupUi(this);

    m_Timer = new QTimer(this);
    connect(m_Timer,SIGNAL(timeout()),this,SLOT(Update()));

    ui->Panel_Left->setStyleSheet("background-color:black;");
    ui->Panel_Right->setStyleSheet("background-color:black;");
    ui->Ball->setStyleSheet("background-color:black;");

    m_LeftPannel = new Pannel(ui->Panel_Left);
    m_RightPannel = new Pannel(ui->Panel_Right);
    m_Ball = new Ball(ui->Ball);

    StartMenue();

    this->setWindowState(Qt::WindowFullScreen);

}

CPongWindow::~CPongWindow()
{
    delete m_LeftPannel;
    delete m_RightPannel;
    m_Timer->stop();
    delete ui;
}

void CPongWindow::Update()
{
    //maus events verarbeiten und kollision berechnen
    if(QCursor::pos().x()-this->pos().x()<this->width()/2)
    {
        m_LeftPannel->SetPosition(QCursor::pos().y()-this->pos().y());
    }
    else
    {
        m_RightPannel->SetPosition(QCursor::pos().y()-this->pos().y());
    }

    m_Ball->CheckCollision(m_LeftPannel);
    m_Ball->CheckCollision(m_RightPannel);

    if(m_Ball->Update()==false)
    {//ein spieler hat gefailt
        StartMenue();
    }
}

void CPongWindow::on_button_starte_clicked()
{
    //spiel soll gestartet werden
    ui->button_starte->setVisible(false);
    ui->button_benden->setVisible(false);
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);

    ui->Ball->setVisible(true);
    ui->Panel_Left->setVisible(true);
    ui->Panel_Right->setVisible(true);
    m_Ball->SetStart();
    m_Timer->start(10);
}


void CPongWindow::StartMenue()
{
    //menue soll wieder angezeigt werden
    ui->button_starte->setVisible(true);
    ui->button_benden->setVisible(true);
    ui->label->setVisible(true);
    ui->label_2->setVisible(true);

    ui->Ball->setVisible(false);
    ui->Panel_Left->setVisible(false);
    ui->Panel_Right->setVisible(false);
    m_Timer->stop();
}
