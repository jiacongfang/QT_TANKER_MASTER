#ifndef TANKBASE_H
#define TANKBASE_H
#include "config.h"
#include "bullet.h"
#include <QPixmap>
#include <QPainter>

class TankBase{
public:
    int speed;
    Bullet bullet;
    int superbullet=0;
    int nuclearbomb=0;
    static int w, h;
    direct dir;
    int state=0;  //由于图片有两种状态，借此来实现履带的转动感 0->1->0->1
    int level;  //记录等级
    int hp;     //记录生命
    QPixmap up_pic[2];
    QPixmap down_pic[2];
    QPixmap left_pic[2];
    QPixmap right_pic[2];
    QRect rect;
    TankBase();
    TankBase(const TankBase& other);
    TankBase & operator=(const TankBase& other);
    ~TankBase();

    void resetSpeed(int speed_);    //重设speed，未必要用，可以用来升级时调用
    void setDir(direct dir_);
    int collectTool();

    //写成多态，不确定要不要用～
    virtual void move();
    virtual void displayTank(QPainter & paint);     //这里会周期性修改state
    virtual bool moveAvailable(int x, int y, direct dir);
    virtual void shot(); //发射bullet
};


#endif // TANKBASE_H
