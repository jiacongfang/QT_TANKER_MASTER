#include "endwindow.h"
#include "mypushbutton.h"
#include "playwindow.h"
#include "QLabel"
#include "config.h"
#include "QString"

EndWindow::EndWindow(int status,int gate,QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(WIDTH,HEIGHT);
    setWindowTitle("坦克大战");
    //setWindowIcon(QIcon(":/res/pic/icon.png"));
    MyPushButton *regamebtn=new MyPushButton(this,"重玩本关",85,50,12);
    MyPushButton *menubtn=new MyPushButton(this,"返回主菜单",85,50,12);
    MyPushButton *exitbtn=new MyPushButton(this,"退出游戏",85,50,12);
    MyPushButton *nextbtn=new MyPushButton(this,"下一关",85,50,12);
    if(status==0)
    {
        regamebtn->setText("再试一次");
        regamebtn->move(250,150);
        menubtn->move(250,250);
        exitbtn->move(250,350);
        nextbtn->hide();
    }
    else
    {
        if(gate==5)
        {
            nextbtn->hide();
            regamebtn->move(250,150);
            menubtn->move(250,250);
            exitbtn->move(250,350);
        }
        else
        {
            nextbtn->move(250,150);
            regamebtn->move(250,250);
            menubtn->move(250,350);
            exitbtn->move(250,450);
        }
    }
    QLabel *title=new QLabel(this);
    QFont font;
    QPalette palette1,palette2;
    palette1.setColor(QPalette::WindowText,Qt::yellow);
    palette2.setColor(QPalette::WindowText,Qt::red);
    font.setFamily("微软雅黑");
    font.setPointSize(25);
    font.setBold(true);
    title->setFont(font);
    if(status==1)
    {
        title->setText("胜 利");
        title->setPalette(palette1);
    }
    else
    {
        title->setText("失 败");
        title->setPalette(palette2);
    }
    title->setGeometry(260,0,250,50);
    if(gate==5 && status == 1)
    {
        QLabel *FinalTitle=new QLabel(this);
        FinalTitle->setFont(font);
        FinalTitle->setPalette(palette1);
        FinalTitle->setText("恭喜你已通过全部关卡！");
        FinalTitle->setGeometry(140,50,350,50);
    }
    connect(regamebtn,&MyPushButton::clicked,[=](){
        this->close();
        emit regame();
    });
    connect(exitbtn,&MyPushButton::clicked,[=](){
        this->close();
        emit exitgame();
    });
    connect(menubtn,&MyPushButton::clicked,[=](){
        this->close();
        emit returnmenu();
    });
    if(status==1)
    {
        connect(nextbtn,&MyPushButton::clicked,[=](){
            this->close();
            emit nextgame();
        });
    }
}

void EndWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawRect(rect());
}
