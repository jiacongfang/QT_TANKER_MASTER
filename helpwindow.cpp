#include "helpwindow.h"
#include "config.h"
#include "mypushbutton.h"
#include "QPainter"
#include <QPalette>
#include <QLabel>

HelpWindow::HelpWindow(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(WIDTH,HEIGHT);
    setWindowTitle("游戏简介与帮助");
    //setWindowIcon(QIcon(":/res/pic/icon.png"));
    QLabel *title=new QLabel(this);
    QLabel *body=new QLabel(this);
    QFont font1,font2;
    QPalette palette1;
    palette1.setColor(QPalette::WindowText,Qt::white);
    title->setPalette(palette1);
    body->setPalette(palette1);
    font1.setFamily("微软雅黑");
    font1.setPointSize(20);
    font1.setBold(true);
    font2.setFamily("楷体");
    font2.setPointSize(12);
    font2.setBold(false);
    title->setFont(font1);
    body->setFont(font2);
    title->setText("HELP");
    body->setText("坦克控制：\nW：向上移动\nS：向下移动\nA：向左移动\nD：向右移动\nJ：发射子弹\nK：发射核弹\n\n地图：\n河流：坦克不可通过，子弹可通过\n砖块：坦克不可通过，可被子弹摧毁\n铁块：坦克不可通过，不可被子弹摧毁\n草丛：坦克可通过，且坦克在其中处于隐身状态\n\n道具：\n生命回复：玩家坦克生命值+1\n子弹升级：玩家坦克的五发子弹升级为超级子弹（效果可叠加）\n超级子弹在击中敌方坦克/铁块时将摧毁目标并爆炸，击中敌方坦克子弹/砖块时将\n摧毁目标并继续前进\n\n核弹：玩家坦克获得一枚核弹，按K健使用\n核弹可瞬间摧毁当前地图内所有敌方坦克\n\n胜利条件：\n在保护己方基地的前提下发射子弹击败当前关卡所有敌方坦克.\n\n注意:\n在本游戏设计中，敌方坦克可以相互碰撞，但若己方坦克与敌方坦克相撞，则双方皆会损毁.");
    title->resize(500,50);
    title->move(265,0);
    body->setGeometry(0,10,600,500);

    MyPushButton *returnbtn=new MyPushButton(this,"返回主菜单");
    returnbtn->move(245,500);
    returnbtn->show();
    connect(returnbtn, &MyPushButton::clicked, [=](){
        emit returnmenu();
    });
}

void HelpWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawRect(rect());
}
