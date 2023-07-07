#include "selectionwindow.h"
#include "mypushbutton.h"
#include "QMessageBox"
#include "QPainter"
#include "config.h"
#include "playwindow.h"

SelectionWindow::SelectionWindow(QWidget *parent) : QMainWindow(parent)
{
    total_number = NUM;
    setFixedSize(WIDTH,HEIGHT);
    setWindowTitle("选择关卡");
    //setWindowIcon(QIcon(":/res/pic/icon.png"));

//    note = new QLabel("注意\n1-5关为固定关卡\n6-10关为DIY设计关卡", this);
//    note->resize(150, 150);
//    note->setAlignment(Qt::AlignHCenter);
//    note->move(275, 275);
//    QPalette pe;
//    pe.setColor(QPalette::WindowText, Qt::white);
//    note->setPalette(pe);
//    note->show();

    MyPushButton *infobtn=new MyPushButton(this,"关卡信息");
    infobtn->move(200, 400);
    infobtn->show();
    connect(infobtn, &MyPushButton::clicked, [=](){
        QMessageBox::information(this, "关卡信息", "目前只开放了5关\n\n1-5关的总敌人数量依此增加\n\n同时关卡地形也变得更丰富\n\n祝好运！","确认");
    });

    MyPushButton *returnbtn=new MyPushButton(this,"返回主菜单");
    returnbtn->move(300,400);
    returnbtn->show();
    connect(returnbtn, &MyPushButton::clicked, [=](){
        emit returnmenu();
    });
    MyPushButton *gamebtn[40];
    for(int i=0;i<2;++i)
    {
        for(int j=0;j<5;++j)
        {
            int id=i*5+j+1;
            gamebtn[id]=new MyPushButton(this,"第 "+QString::number(id)+" 关",80,40,12);
            gamebtn[id]->move(50+j*100,60+60*i);
            connect(gamebtn[id],&MyPushButton::clicked,[=](){
                if(id>10||id<1)
               {
                   QMessageBox::warning(this,tr("WARNNING: "),tr("关卡数据不存在，请检查游戏文件！"),tr("确认"));
               }
               else
               {
                   if(id>=1&&id<=total_number)
                   {
                       PlayWindow *playwindow=new PlayWindow(id);
                       playwindow->setGeometry(this->geometry());
                       this->close();
                       playwindow->show();
                       connect(playwindow,&PlayWindow::returnmenu,[=](){
                           emit returnmenu();
                       });
                   }
                   else
                   {
                       QMessageBox::warning(this,tr("提示: "),tr("关卡尚未开放，敬请期待！"),tr("确认"));
                   }
               }
            });
        }
    }
}

void SelectionWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawRect(rect());
}

