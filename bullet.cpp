#include "bullet.h"
#include <QDebug>
#include <QImage>
#include <QDir>
/* Bullet{
private:
int speed;
bool active;
public:
int bumbx, bumby;
bool bump;  //记录是否爆炸
int w;
int h; //bullet像素大小（宽与高）
direct dir; //移动方向
QPixmap up_pic;
QPixmap down_pic;
QPixmap left_pic;
QPixmap right_pic;
QPixmap bump_pic; //爆炸图片
QRect rect; //记录位置
*/
Bullet::Bullet(){  //图片像素：4*3
    w = 8;
    h = 12;
    speed = BaseSize * 2 / 3;   //可以调
    active = false;
    bumb = false;
    up_pic2.load(":/res/pic/super_up.png");
    down_pic2.load(":/res/pic/super_down.png");
    left_pic2.load(":/res/pic/super_left.png");
    right_pic2.load(":/res/pic/super_right.png");
    left_pic.load(":/res/pic/bullet-0.gif");
    up_pic.load(":/res/pic/bullet-1.gif");
    right_pic.load(":/res/pic/bullet-2.gif");
    down_pic.load(":/res/pic/bullet-3.gif");
    //resize: 4*3 -> 12*8
    up_pic2 = resizePic(up_pic2, w, h);
    down_pic2 = resizePic(down_pic2, w, h);
    left_pic2 = resizePic(left_pic2, h, w);
    right_pic2 = resizePic(right_pic2, h, w);
    left_pic = resizePic(left_pic, h, w);
    right_pic = resizePic(right_pic, h, w);
    up_pic = resizePic(up_pic, w, h);
    down_pic = resizePic(down_pic, w, h);
    bumb_pic.load(":/res/pic/bump1.gif");
    bumb_pic = resizePic(bumb_pic, BaseSize, BaseSize);   // 16*16 -> BaseSize * BaseSize
    rect.setRect(-1, -1, 0, 0); //位置矩形初始化

}

Bullet::Bullet(const Bullet& b){
    *this = b;
}

Bullet& Bullet::operator=(const Bullet& b){
    if(this == &b) return *this;
    w = b.w;
    h = b.h;
    speed = b.speed;
    active = b.active;
    bumb = b.bumb;
    bumbx = b.bumbx;
    bumby = b.bumby;
    left_pic = b.left_pic;
    right_pic = b.right_pic;
    up_pic = b.up_pic;
    down_pic = b.down_pic;
    bumb_pic = b.bumb_pic;
    dir = b.dir;
    rect = b.rect;
    return *this;
}
Bullet::~Bullet(){ }

void Bullet::setDir(direct dir_){
    dir = dir_;
}

void Bullet::setActive(bool active_){
    active = active_;
    if(active == false){    //bumb!
        bumb = true;
        //校准爆炸位置--计算爆炸中心位置
        int x = rect.x();
        int y = rect.y();
        if(dir == direct::Up || dir == direct::Down){
            x -= (BaseSize - w) / 2;
        }
        else{
            y -= (BaseSize - w) / 2;
        }
        bumbx = x;
        bumby = y;
        rect.setRect(-1, -1, 0, 0);
    }
}

void Bullet::move(){
    if(!active) return;
    int x = rect.x();
    int y = rect.y();
    switch(dir){
    case direct::Up:
        y -= speed;
        break;
    case direct::Down:
        y += speed;
        break;
    case direct::Left:
        x -= speed;
        break;
    case direct::Right:
        x += speed;
        break;
    }
    if(moveAvailable(x, y, dir)){
        rect.moveTo(x, y);
    }
    else{
        setActive(false);
    }
}

void Bullet::displayBullet(QPainter & paint){
    if(!active) return;
//    int bias = 5;
    switch(dir){
    case direct::Up:
        if(super) paint.drawPixmap(rect.x(), rect.y(), up_pic2);
        else paint.drawPixmap(rect.x(), rect.y(), up_pic);
        break;
    case direct::Down:
        if(super) paint.drawPixmap(rect.x(), rect.y(), down_pic2);
        else paint.drawPixmap(rect.x(), rect.y(), down_pic);
        break;
    case direct::Left:
        if(super) paint.drawPixmap(rect.x(), rect.y(), left_pic2);
        else paint.drawPixmap(rect.x(), rect.y(), left_pic);
        break;
    case direct::Right:
        if(super) paint.drawPixmap(rect.x(), rect.y(), right_pic2);
        else paint.drawPixmap(rect.x(), rect.y(), right_pic);
        break;
    }


}
void Bullet::displayExplosion(QPainter & paint){    //显示爆炸
    bumb = false;
    paint.drawPixmap(bumbx, bumby, bumb_pic);
}
bool Bullet::moveAvailable(int x, int y, direct dir){ //像素坐标x, y(rect),  dir:目前移动方向;
    x /= BaseSize;
    y /= BaseSize;
    int tempx, tempy;
    switch(dir){
    case direct::Up:
        tempx = x + 1;
        tempy = y;
        break;
    case direct::Down:
        tempx = x + 1;
        tempy = y;
        break;
    case direct::Left:
        tempx = x;
        tempy = y + 1;
        break;
    case direct::Right:
        tempx = x;
        tempy = y + 1;
        break;
    default:
        qDebug() << "Direct ERROR!";
        break;
    }
    //判断是否越界
    if( x < 0 || y < 0 || x > 25 || y > 25 || tempx < 0 || tempy < 0 || tempx > 25 || tempy > 25 ){
        return false;
    }
    if(map[y][x] == EMPTY || map[y][x] == GRASS || map[y][x] == RIVER ||map[y][x]==LIFE||map[y][x]==SUPERBULLET||map[y][x]==NUCLEARBOMB){
        return true;
    }
    else if(map[y][x] == STONE){//遇到砖头
        map[y][x] = EMPTY;
        if(super) return true;
        else return false;
    }
    else if(map[y][x] == IRON){     //遇到铁
        //是否需要在这里加上音效
        if(super)
        {
            map[y][x]=EMPTY;
            super=false;
        }
        return false;
    }
//    else if(map[y][x] == HEAD){     //大本营被毁灭
//        //############这里需要有游戏结束信号##############
//        map[y][x] = BROKEN_HEAD;
//        return true;
//    }
    else qDebug() << "map数值有错";
    qDebug() << "MoveAvailable Error" ;;
    return false;
}
/*
//地图障碍宏
#define EMPTY 0
#define GRASS 1
#define STONE 2
#define IRON 3
#define RIVER 4
#define HEAD 5
#define BROKEN_HEAD 6
  */
void Bullet::resetSpeed(int speed_){
    speed = BaseSize * speed_ / 3;
}

bool Bullet::getActive(){
    return active;
}
