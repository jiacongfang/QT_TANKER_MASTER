#include "mypushbutton.h"
#include "QDebug"
#include <QMouseEvent>

MyPushButton::MyPushButton(QWidget* parent,const QString text,int width,int height,int size):QPushButton(text,parent)
{
    resize(width,height);
    QFont font;
    font.setFamily("宋体");
    font.setPixelSize(1024);
    font.setPointSize(size);
    font.setBold(true);
    setFont(font);
    sound.setSource(QUrl::fromLocalFile(":/res/sound/ButtonSound.wav"));

}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
//    QSoundEffect *sound =new QSoundEffect(":/res/sound/ButtonSound.wav");
//    sound->play();

    //Qt6.5.1 使用QSoundEffect播放
    sound.play();

    QPushButton::mousePressEvent(e);
}


