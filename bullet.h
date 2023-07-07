#ifndef BULLET_H
#define BULLET_H

#include "config.h"
#include <QPixmap>
#include <QPainter>
//#include <QMediaPlayer>

class Bullet{
private:
    int speed;
    bool active;    //记录是否发射
public:
    int bumbx, bumby; // 爆炸位置
    bool bumb;  //记录是否爆炸
    bool super=false;
    int w;
    int h; //bullet像素大小（宽与高）
    direct dir; //移动方向
    QPixmap up_pic,up_pic2;
    QPixmap down_pic,down_pic2;
    QPixmap left_pic,left_pic2;
    QPixmap right_pic,right_pic2;
    QPixmap bumb_pic; //爆炸图片
    QRect rect;       //记录位置 ， rect.x():left, rect.y():top
    Bullet();
    Bullet(const Bullet& b);
    Bullet& operator=(const Bullet& b);
    ~Bullet();
    bool getActive(); //
    void setActive(bool active_);
    void move();    //移动函数
    void displayBullet(QPainter & paint);            //显示子弹
    void displayExplosion(QPainter & paint);        //显示爆炸
    bool moveAvailable(int x, int y, direct dir);  //像素坐标x, y(rect),  dir:目前移动方向;
    void resetSpeed(int speed_);                    //重设速度
    void setDir(direct dir_);                      //设置方向
};

#endif // BULLET_H
