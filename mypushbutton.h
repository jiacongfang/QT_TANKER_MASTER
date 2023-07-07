#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QSoundEffect>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    MyPushButton(QWidget* parent, QString text,int width=85,int height=50,int size=12);
    void mousePressEvent(QMouseEvent *e);
    QSoundEffect sound;
signals:

};
#endif // MYPUSHBUTTON_H
