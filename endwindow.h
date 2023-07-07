#ifndef ENDWINDOW_H
#define ENDWINDOW_H

#include "playwindow.h"
#include <QMainWindow>

class EndWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit EndWindow(int status,int gate,QWidget *parent = nullptr);
     void paintEvent(QPaintEvent *e);

signals:
     void regame();
     void nextgame();
     void returnmenu();
     void exitgame();

public slots:
};

#endif // ENDWINDOW_H
