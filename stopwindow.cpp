#include "stopwindow.h"
#include "config.h"
#include "mypushbutton.h"
#include "QMessageBox"
#include "QLabel"
#include "QPainter"
#include "QPalette"

StopWindow::StopWindow(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(WIDTH,HEIGHT);
    setWindowTitle("暂停");
    //setWindowIcon(QIcon(":/res/pic/icon.png"));
    MyPushButton *continuebtn=new MyPushButton(this,"继续游戏",85,50,12);
    MyPushButton *menubtn=new MyPushButton(this,"返回主菜单",85,50,12);
    MyPushButton *exitbtn=new MyPushButton(this,"退出游戏",85,50,12);
    continuebtn->move(250,150);
    menubtn->move(250,250);
    exitbtn->move(250,350);
    QLabel *title=new QLabel(this);
    QFont font;
    QPalette palette1,palette2;
    palette1.setColor(QPalette::WindowText,Qt::blue);
    title->setPalette(palette1);
    font.setFamily("微软雅黑");
    font.setPointSize(25);
    font.setBold(true);
    title->setFont(font);
    title->setText("STOP");
    title->setGeometry(260,0,250,50);
    connect(continuebtn,&MyPushButton::clicked,[=](){
        this->close();
        emit continuegame();
    });
    connect(exitbtn,&MyPushButton::clicked,[=](){
        QMessageBox box(QMessageBox::Question, "退出游戏", "退出游戏后进度将无法保存\n\n你确定要退出游戏吗？");
        box.setWindowIcon(QIcon(":/res/pic/icon.png"));
        box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        box.setButtonText(QMessageBox::Cancel, QString("取消"));
        box.setButtonText(QMessageBox::Ok, QString("退出游戏"));
        int ret=box.exec();
        if(ret==QMessageBox::Ok)
        {
            this->close();
            emit exitgame();
        }
    });
    connect(menubtn,&MyPushButton::clicked,[=](){
        this->close();
        emit returnmenu();
    });
}

void StopWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawRect(rect());
}
