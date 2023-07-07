#include "tankbase.h"
#include <QDebug>


int TankBase::h = BaseSize;
int TankBase::w = BaseSize;

TankBase::TankBase(){

}

TankBase::~TankBase(){}

TankBase::TankBase(const TankBase &other){
    *this = other;
}

TankBase& TankBase::operator =(const TankBase& other){
    if(this == &other)  return *this;
    speed = other.speed;
    bullet = other.bullet;
    dir = other.dir;
    w = other.w;   h = other.h;
    up_pic[0] = other.up_pic[0];
    up_pic[1] = other.up_pic[1];
    down_pic[0] = other.down_pic[0];
    down_pic[1] = other.down_pic[1];
    left_pic[0] = other.left_pic[0];
    left_pic[1] = other.left_pic[1];
    right_pic[0] = other.right_pic[0];
    right_pic[1] = other.right_pic[1];
    rect = other.rect;
    state = other.state;
    hp = other.hp;
    level = other.level;
    return *this;
}

void TankBase::resetSpeed(int speed_){
    speed = BaseSize * speed_;
}
//升级时用到
void TankBase::setDir(direct dir_){
    dir = dir_;
}

void TankBase::shot(){
    if(bullet.getActive())  return ;//已经发射过
    bullet.setActive(true);
    if(superbullet>0)
    {
        superbullet--;
        bullet.super=true;
    }
    else bullet.super=false;
    bullet.setDir(dir);

    int bias = (SIZE - w) / 2; //弹道偏移量
    switch(dir){
    case direct::Up:
        bullet.rect.setRect(rect.x() + bias, rect.y(), bullet.w, bullet.h);
        break;
    case direct::Down:
        bullet.rect.setRect(rect.x() + bias, rect.bottom() - bullet.h, bullet.w, bullet.h);
        break;
    case direct::Left:
        bullet.rect.setRect(rect.left(), rect.y() + bias, bullet.h, bullet.w);
        break;
    case direct::Right:
        bullet.rect.setRect(rect.right() - bullet.h, rect.y() + bias, bullet.h, bullet.w);
        break;
    }

}

int TankBase::collectTool()
{
    int cnt=0;
    int x=rect.x()/BaseSize;
    int y=rect.y()/BaseSize;
    int tempx,tempy;
    switch(dir){
    case direct::Up:
        tempx = x + 1;
        tempy = y;
        break;
    case direct::Down:
        y += 1;
        tempx = x + 1;
        tempy = y;
        break;
    case direct::Left:

        tempx = x;
        tempy = y + 1;
        break;
    case direct::Right:
        x += 1;
        tempx = x;
        tempy = y + 1;
        break;
    }
    if(map[y][x]==LIFE)
    {
        cnt++;
        hp++;
        map[y][x]=EMPTY;
    }
    if(map[tempy][tempx]==LIFE)
    {
        cnt++;
        hp++;
        map[tempy][tempx]=EMPTY;
    }
    if(map[y][x]==SUPERBULLET)
    {
        cnt++;
        superbullet+=5;
        map[y][x]=EMPTY;
    }
    if(map[tempy][tempx]==SUPERBULLET)
    {
        cnt++;
        superbullet+=5;
        map[tempy][tempx]=EMPTY;
    }
    if(map[y][x]==NUCLEARBOMB)
    {
        cnt++;
        nuclearbomb+=1;
        map[y][x]=EMPTY;
    }
    if(map[tempy][tempx]==NUCLEARBOMB)
    {
        cnt++;
        nuclearbomb+=1;
        map[tempy][tempx]=EMPTY;
    }
    return cnt;
}

bool TankBase::moveAvailable(int x, int y, direct dir){
    x /= BaseSize;
    y /= BaseSize;
    int tempx, tempy;
    switch(dir){
    case direct::Up:
        tempx = x + 1;
        tempy = y;
        break;
    case direct::Down:
        y += 1;
        tempx = x + 1;
        tempy = y;
        break;
    case direct::Left:

        tempx = x;
        tempy = y + 1;
        break;
    case direct::Right:
        x += 1;
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
    if((map[y][x] == EMPTY || map[y][x] == GRASS||map[y][x]==LIFE||map[y][x]==SUPERBULLET||map[y][x]==NUCLEARBOMB) && (map[tempy][tempx] == EMPTY || map[tempy][tempx] == GRASS||map[tempy][tempx]==LIFE||map[tempy][tempx]==SUPERBULLET||map[tempy][tempx]==NUCLEARBOMB)){
        return true;
    }
//    else if(map[y][x] == STONE || map[y][x] == RIVER || map[y][x] == IRON){    //遇到砖头、铁和河流
//        return false;
//    }
//    else if(map[y][x] == HEAD){
//        return false;
//    }
//    else qDebug() << "map数值有错";
//    qDebug() << "MoveAvailable Error" ;
//    return false;
    else
        return false;
}

void TankBase::displayTank(QPainter &paint){
    switch(dir){
    case direct::Up:
        paint.drawPixmap(rect.x(), rect.y(), up_pic[state]);
        state = (state + 1) % 2;
        break;
    case direct::Down:
        paint.drawPixmap(rect.x(), rect.y(), down_pic[state]);
        state = (state + 1) % 2;
        break;
    case direct::Left:
        paint.drawPixmap(rect.x(), rect.y(), left_pic[state]);
        state = (state + 1) % 2;
        break;
    case direct::Right:
        paint.drawPixmap(rect.x(), rect.y(), right_pic[state]);
        state = (state + 1) % 2;
        break;
    }
}

void TankBase::move(){
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
    if(moveAvailable(x, y, this->dir)){
        rect.moveTo(x, y);
    }
}
