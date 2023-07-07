#include "mainwindow.h"
#include "config.h"
#include <QDebug>
#include "QPainter"
#include <QSoundEffect>
#include "ui_mainwindow.h"
#include "mypushbutton.h"
#include "helpwindow.h"
#include "playwindow.h"
#include "selectionwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("坦克大战");
    //setWindowIcon(QIcon(":/res/pic/icon.png"));
    setFixedSize(WIDTH,HEIGHT);
    HelpWindow *helpwindow=new HelpWindow;
    SelectionWindow *selectwindow=new SelectionWindow;
    MyPushButton* exitbtn=new MyPushButton(this,"退出游戏");
    exitbtn->move(400,375);
    MyPushButton* helpbtn=new MyPushButton(this,"帮 助");
    helpbtn->move(250,375);
    MyPushButton* selectbtn=new MyPushButton(this,"选择关卡");
    selectbtn->move(100,375);
    MyPushButton* aboutbtn=new MyPushButton(this,"关于我们");
    aboutbtn->move(325,450);
    MyPushButton* diybtn=new MyPushButton(this,"关卡设计");
    diybtn->move(175,450);
    connect(exitbtn, &MyPushButton::clicked, [=](){
        QMessageBox box(QMessageBox::Question, "退出游戏", "你确定要退出游戏吗？");
        //box.setWindowIcon(QIcon(":/res/pic/icon.png"));
        box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        box.setButtonText(QMessageBox::Cancel, QString("取消"));
        box.setButtonText(QMessageBox::Ok, QString("退出游戏"));
        int ret=box.exec();
        if(ret==QMessageBox::Ok)
        {
            this->close();
        }
    });
    connect(helpbtn,&MyPushButton::clicked,[=](){
        helpwindow->setGeometry(this->geometry());
        helpwindow->show();
    });
    connect(selectbtn,&MyPushButton::clicked,[=](){
        selectwindow->setGeometry(this->geometry());
        this->close();
        selectwindow->show();
    });
    connect(selectwindow, &SelectionWindow::returnmenu, [=](){
       selectwindow->hide();
       this->show();
    });
    connect(helpwindow,&HelpWindow::returnmenu,[=](){
        helpwindow->hide();
        this->show();
    });
    connect(aboutbtn,&MyPushButton::clicked,[=](){
        QMessageBox::information(this, "关于坦克大战", "作者：QT_TEAM_068（方嘉聪 王渝樊 王千烨）\n\n本项目为QT_Team_068的程设课程QT大作业\n\n声明：游戏中的图片与声音素材来自网络，仅用于此次课程项目.\n\n如有任何疑问可以通过邮件联系jiacong_fang@stu.pku.edu.cn\n\n\t\t2023-07","确认");
    });

    connect(diybtn,&MyPushButton::clicked,[=](){
        QMessageBox::information(this, "关于坦克大战", "该功能未开放","确认");
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawRect(rect());
    QPixmap pix;
    pix.load(":/res/pic/background.png");
    pix=pix.scaled(580,580,Qt::KeepAspectRatio);
    painter.drawPixmap(0,0,pix);
}
