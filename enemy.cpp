#include "enemy.h"
#include <QDir>
Enemy::Enemy(){
    speed = BaseSize;
    dir = direct::Down;
    state = 0;
//    ismove = false;
    rect.setRect(0*BaseSize,0*BaseSize,SIZE,SIZE);
    up_pic[0].load(":/res/pic/gray-tank/1-2-1.gif");
    up_pic[1].load(":/res/pic/gray-tank/1-2-2.gif");
    left_pic[0].load(":/res/pic/gray-tank/1-1-1.gif");
    left_pic[1].load(":/res/pic/gray-tank/1-1-2.gif");
    right_pic[0].load(":/res/pic/gray-tank/1-3-1.gif");
    right_pic[1].load(":/res/pic/gray-tank/1-3-2.gif");
    down_pic[0].load(":/res/pic/gray-tank/1-4-1.gif");
    down_pic[1].load(":/res/pic/gray-tank/1-4-2.gif");

    up_pic[0]=resizePic(up_pic[0],SIZE,SIZE);
    up_pic[1]=resizePic(up_pic[1],SIZE,SIZE);
    left_pic[0]=resizePic(left_pic[0],SIZE,SIZE);
    left_pic[1]=resizePic(left_pic[1],SIZE,SIZE);
    right_pic[0]=resizePic(right_pic[0],SIZE,SIZE);
    right_pic[1]=resizePic(right_pic[1],SIZE,SIZE);
    down_pic[0]=resizePic(down_pic[0],SIZE,SIZE);
    down_pic[1]=resizePic(down_pic[1],SIZE,SIZE);

}

bool Enemy::operator ==(const Enemy&a){
    if(this->rect==a.rect)return true;
    return false;
}
Enemy::~Enemy(){}
