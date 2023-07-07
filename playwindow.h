#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>
#include <QIcon>
#include <QTimer>
#include <QList>
#include <QCoreApplication>
#include <QMessageBox>
#include <fstream>
#include <iostream>
#include "config.h"
#include "player.h"
#include "enemy.h"
#include <QSoundEffect>

class PlayWindow : public QMainWindow
{
    Q_OBJECT
private:
    bool flag;
    QPixmap grass;
    QPixmap stone;
    QPixmap iron;
    QPixmap river;
    QPixmap head;
    QPixmap bg_gray;
    QPixmap broken_head;
    QPixmap life;
    QPixmap superbullet;
    QPixmap nuclearbomb;
    void init();
    void createPlayer();
    void createEnemy();
    player player1;
    QRect headRect;
    QPainter paint;
    QTimer* timer1;
    QTimer* timer2;
    QTimer* timer3;
    QTimer* timer4;
    QTimer* timer5;
    QTimer* timer6;
    QTimer* timer;
    int cursor;//光标
    QList<Enemy>enemies;
    int enemynum;
    int enemycnt;
    int toolnum;
    int gate;//关卡
    int start;

    //Sound
    QSoundEffect startSound;
    QSoundEffect shotSound;
    QSoundEffect enemyBombSound;
    QSoundEffect playerBombSound;
    QSoundEffect moveSound;
    QSoundEffect campSound;
    QSoundEffect failSound;
    QSoundEffect winSound;

protected:
    void loadMap();
    void drawMap();
    void drawFrame();
    void drawPanel();
    void drawStart();
    void paintEvent(QPaintEvent*);
    void gameover(int status);
public:
    bool head_is_broken();
    PlayWindow(int start_gate,QWidget *parent = nullptr);
    ~PlayWindow();
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent *event);
    void collisionCheck();
    void nextGate();
    void createTool();
signals:
    void returnmenu();
public slots:
    void play();
    void enemyMove();
    void enemyShot();
    void bulletMove();
    void refresh();
};

#endif // PLAYWINDOW_H
