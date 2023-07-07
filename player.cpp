#include "player.h"
#include <QDebug>
#include <QDir>
#include "player.h"
player::player(){
    speed = BaseSize;
    dir=Up;
    ismove=false;
    state = 0;
    hp = 3;
    up_pic[0].load(":/res/pic/0Player/m0-1-1.gif");
    up_pic[1].load(":/res/pic/0Player/m0-1-2.gif");
    left_pic[0].load(":/res/pic/0Player/m0-0-1.gif");
    left_pic[1].load(":/res/pic/0Player/m0-0-2.gif");
    right_pic[0].load(":/res/pic/0Player/m0-2-1.gif");
    right_pic[1].load(":/res/pic/0Player/m0-2-2.gif");
    down_pic[0].load(":/res/pic/0Player/m0-3-1.gif");
    down_pic[1].load(":/res/pic/0Player/m0-3-2.gif");

    up_pic[0]=resizePic(up_pic[0],SIZE,SIZE);
    up_pic[1]=resizePic(up_pic[1],SIZE,SIZE);
    left_pic[0]=resizePic(left_pic[0],SIZE,SIZE);
    left_pic[1]=resizePic(left_pic[1],SIZE,SIZE);
    right_pic[0]=resizePic(right_pic[0],SIZE,SIZE);
    right_pic[1]=resizePic(right_pic[1],SIZE,SIZE);
    down_pic[0]=resizePic(down_pic[0],SIZE,SIZE);
    down_pic[1]=resizePic(down_pic[1],SIZE,SIZE);

}
void player::setDir(direct dir){
    this->dir=dir;
    ismove=true;
}
