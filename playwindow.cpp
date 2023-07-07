#include "playwindow.h"
#include "mypushbutton.h"
#include "stopwindow.h"
#include "QMessageBox"
#include "endwindow.h"
#include "QPainter"
#include <QDebug>
#include <QSoundEffect>
#include <QDir>

PlayWindow::PlayWindow(int start_gate,QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(WIDTH,HEIGHT);
    setWindowTitle("坦克大战");
    //setWindowIcon(QIcon(":/res/pic/icon.png"));
    headRect.setRect(12*BaseSize,24*BaseSize,SIZE,SIZE);

    //加载声音
    startSound.setSource(QUrl::fromLocalFile(":/res/sound/start.wav"));
    shotSound.setSource(QUrl::fromLocalFile(":/res/sound/shoot.wav"));
    enemyBombSound.setSource(QUrl::fromLocalFile(":/res/sound/enemy-bomb.wav"));
    playerBombSound.setSource(QUrl::fromLocalFile(":/res/sound/player_bomb.wav"));
    moveSound.setSource(QUrl::fromLocalFile(":/res/sound/move.wav"));
    campSound.setSource(QUrl::fromLocalFile(":/res/sound/camp_bomb.wav"));
    failSound.setSource(QUrl::fromLocalFile(":/res/sound/fail.wav"));
    winSound.setSource(QUrl::fromLocalFile(":/res/sound/win.wav"));

    //下面加载图像
    bg_gray.load(":/res/pic/bg_gray.gif");
    grass.load(":/res/pic/grass.gif");
    stone.load(":/res/pic/stone.gif");
    iron.load(":/res/pic/iron.gif");
    river.load(":/res/pic/river-0.gif");
    head.load(":/res/pic/camp0.gif");
    broken_head.load(":/res/pic/camp1.gif");
    life.load(":/res/pic/hp.jpg");
    superbullet.load(":/res/pic/superbullet.png");
    nuclearbomb.load(":/res/pic/nuclearbomb.png");

    bg_gray=resizePic(bg_gray,SIZE,SIZE);
    grass=resizePic(grass,BaseSize,BaseSize);
    stone=resizePic(stone,BaseSize,BaseSize);
    iron=resizePic(iron,BaseSize,BaseSize);
    river=resizePic(river,BaseSize,BaseSize);
    head=resizePic(head,BaseSize*2,BaseSize*2);
    broken_head=resizePic(broken_head, BaseSize*2, BaseSize*2);
    life=resizePic(life,BaseSize,BaseSize);
    superbullet=resizePic(superbullet,BaseSize,BaseSize);
    nuclearbomb=resizePic(nuclearbomb,BaseSize,BaseSize);

    //设置定时器不停更新界面
    timer = new QTimer;

    //连接处理函数
    timer1=new QTimer(this);
    timer2=new QTimer(this);
    timer3=new QTimer(this);
    timer4=new QTimer(this);
    timer5=new QTimer(this);
    timer6=new QTimer(this);
    connect(timer1,&QTimer::timeout,this,&PlayWindow::play);
    connect(timer2,&QTimer::timeout,this,&PlayWindow::enemyMove);
    connect(timer3,&QTimer::timeout,this,&PlayWindow::enemyShot);
    connect(timer4,&QTimer::timeout,this,&PlayWindow::bulletMove);
    connect(timer5,&QTimer::timeout,this,&PlayWindow::refresh);
    connect(timer6,&QTimer::timeout,this,&PlayWindow::createTool);
    gate=start_gate;
    init();
    MyPushButton *exitbtn=new MyPushButton(this,"退出游戏",60,40,10);
    MyPushButton *stopbtn=new MyPushButton(this,"暂停游戏",60,40,10);
    exitbtn->move(0,0);
    stopbtn->move(60,0);
    connect(exitbtn,&MyPushButton::clicked,[=](){
        timer1->stop();
        timer2->stop();
        timer3->stop();
        timer4->stop();
        timer5->stop();
        timer6->stop();
        QMessageBox box(QMessageBox::Information, "提示", "退出游戏后进度将无法保存\n\n你确定要退出游戏吗？");
        //box.setWindowIcon(QIcon(":/res/pic/icon.png"));
        box.setStandardButtons(QMessageBox::Close|QMessageBox::Ok | QMessageBox::Cancel);
        box.setButtonText(QMessageBox::Cancel, QString("取消"));
        box.setButtonText(QMessageBox::Close, QString("返回主菜单"));
        box.setButtonText(QMessageBox::Ok, QString("退出游戏"));
        int ret=box.exec();
        if(ret==QMessageBox::Close)
        {
            this->close();
            emit returnmenu();
        }
        if(ret==QMessageBox::Ok)
        {
            this->close();
        }
        if(ret==QMessageBox::Cancel)
        {
            timer1->start(playRACE);
            timer2->start(enemyMoveRACE);
            timer3->start(enemyShotRACE);
            timer4->start(bulletMoveRACE);
            timer5->start(refreshRACE);
            timer6->start(toolRACE);
        }
    });
    connect(stopbtn,&MyPushButton::clicked,[=](){
        timer1->stop();
        timer2->stop();
        timer3->stop();
        timer4->stop();
        timer5->stop();
        timer6->stop();
        this->hide();
        StopWindow *stopwindow=new StopWindow;
        stopwindow->setGeometry(this->geometry());
        stopwindow->show();
        connect(stopwindow,&StopWindow::returnmenu,[=](){
            this->close();
            emit returnmenu();
        });
        connect(stopwindow,&StopWindow::continuegame,[=](){
            timer1->start(playRACE);
            timer2->start(enemyMoveRACE);
            timer3->start(enemyShotRACE);
            timer4->start(bulletMoveRACE);
            timer5->start(refreshRACE);
            timer6->start(toolRACE);
            this->show();
        });
        connect(stopwindow,&StopWindow::exitgame,[=](){
            this->close();
        });
    });
}

PlayWindow::~PlayWindow()
{
//    delete timer;
    delete timer1;
    delete timer2;
    delete timer3;
    delete timer4;
    delete timer5;
    delete timer6;
}

void PlayWindow::init(){
    flag = false;
    loadMap();//加载地图
    head.load(":/res/pic/camp0.gif");

    //Qt6.5.1 使用QSoundEffect播放
//    QSoundEffect * startSound = new QSoundEffect(this);
//    startSound->setSource(QUrl::fromLocalFile(":/res/sound/start.wav"));
    startSound.play();

//    QSoundEffect::play(":/res/sound/start.wav");  Qt5

    head=resizePic(head,SIZE,SIZE);
    cursor=0;
    toolnum=0;
    enemynum=10+gate;
    enemycnt=10+gate;
    for(int i=0;i<4;i++){createEnemy();}//创建敌人
    player1.hp = 3;
    player1.superbullet=0;
    player1.nuclearbomb=0;
    createPlayer(); //创建player
    start=30;
    timer1->start(playRACE);
    timer2->start(enemyMoveRACE);
    timer3->start(enemyShotRACE);
    timer4->start(bulletMoveRACE);
    timer5->start(refreshRACE);
    timer6->start(toolRACE);
}

void PlayWindow::createPlayer(){
    player1.bullet.setActive(false);
    player1.setDir(direct::Up);
    player1.ismove=false;
    player1.rect.setRect(9*BaseSize,24*BaseSize,SIZE,SIZE);
}

void PlayWindow::createEnemy(){
    if(enemycnt<=0)return;
    Enemy enemy;
    enemy.rect.setRect(cursor*SIZE,0,SIZE,SIZE);
    enemies.push_back(enemy);
    cursor+=6;
    cursor%=18;
    enemycnt--;
}

void PlayWindow::createTool()
{
    if(toolnum>=3) return;
    toolnum++;
    int x,y,kind;
    do
    {
        x=rand()%26;
        y=rand()%26;
    }while(map[x][y]!=EMPTY);
    kind=rand()%3;
    switch(kind)
    {
    case 0:
        map[x][y]=LIFE;
        break;
    case 1:
        map[x][y]=SUPERBULLET;
        break;
    case 2:
        map[x][y]=NUCLEARBOMB;
        break;
    default:
        map[x][y]=EMPTY;
        break;
    }
}

void PlayWindow::loadMap(){//加载地图
    QFile file(":/res/data/map.dat");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
    }
    else
    {
        file.seek(sizeof(map)*(gate-1));
        file.read(*map,sizeof(map));
        file.close();
    }
}

void PlayWindow::drawMap(){
    for(int i=0;i<26;i++){
        for(int j=0;j<26;j++){
            if(map[i][j] == EMPTY) continue;
            if(map[i][j]==GRASS){paint.drawPixmap(j*BaseSize,i*BaseSize,grass);}
            else if(map[i][j]==STONE){paint.drawPixmap(j*BaseSize,i*BaseSize,stone);}
            else if(map[i][j]==IRON){paint.drawPixmap(j*BaseSize,i*BaseSize,iron);}
            else if(map[i][j]==RIVER){paint.drawPixmap(j*BaseSize,i*BaseSize,river);}
            else if(map[i][j]==LIFE) {paint.drawPixmap(j*BaseSize,i*BaseSize,life);}
            else if(map[i][j]==SUPERBULLET) {paint.drawPixmap(j*BaseSize,i*BaseSize,superbullet);}
            else if(map[i][j]==NUCLEARBOMB) {paint.drawPixmap(j*BaseSize,i*BaseSize,nuclearbomb);}
//            else if(map[i][j]==HEAD){paint.drawPixmap(headRect.x(),headRect.y(),head); qDebug() << i << " " << j << Qt::endl; }
//            else if(map[i][j]==BROKEN_HEAD){paint.drawPixmap(headRect.x(),headRect.y(),broken_head);}

        }
    }
    paint.drawPixmap(headRect.x(),headRect.y(),head);
}

void PlayWindow::drawFrame(){   //画边框---可以修改
    for(int i=0;i<15;i++){
        paint.drawPixmap(0,i*SIZE,bg_gray);
        paint.drawPixmap(14*SIZE,i*SIZE,bg_gray);
        paint.drawPixmap(i*SIZE,0,bg_gray);
        paint.drawPixmap(i*SIZE,14*SIZE,bg_gray);
    }
}

void PlayWindow::drawPanel(){   //画信息---可以修改
    paint.drawText(6*SIZE,BaseSize,"第"+QString::number(gate)+"关，敌人数量："+QString::number(enemynum));
    paint.drawText(5*SIZE,29*BaseSize,"生命"+QString::number(player1.hp));
    paint.drawText(7*SIZE,29*BaseSize,"超级子弹"+QString::number(player1.superbullet));
    paint.drawText(9*SIZE,29*BaseSize,"核弹"+QString::number(player1.nuclearbomb));
}

void PlayWindow::drawStart(){
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            paint.drawPixmap(i*SIZE,j*SIZE,bg_gray);
        }
    }
    paint.setFont(QFont("宋体",24));
    paint.drawText(12*BaseSize+10,13*BaseSize+10,"第"+QString::number(gate)+"关");

}

void PlayWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawRect(rect());
    paint.begin(this);
    if(0<start--){
        drawStart();
        paint.end();
        return;
    }
    paint.save();//保存当前状态
    paint.translate(SIZE,SIZE);//移动坐标
//    drawMap();
    player1.displayTank(paint);
    player1.bullet.displayBullet(paint);
    if(player1.bullet.bumb){player1.bullet.displayExplosion(paint);}
    for(auto& enemy:enemies){
        enemy.displayTank(paint);
        enemy.bullet.displayBullet(paint);
        if(enemy.bullet.bumb){enemy.bullet.displayExplosion(paint);}
    }
    drawMap();
    paint.restore();//恢复以上保存的状态
    drawFrame();
    drawPanel();
    paint.end();
}

void PlayWindow::keyPressEvent(QKeyEvent *event)        //键盘控制player1移动
{
    if(start>0){return;}
    if(event->key()==Qt::Key::Key_W){player1.setDir(direct::Up);}
    else if(event->key()==Qt::Key::Key_S){player1.setDir(direct::Down);}
    else if(event->key()==Qt::Key::Key_A){player1.setDir(direct::Left);}
    else if(event->key()==Qt::Key::Key_D){player1.setDir(direct::Right);}
    else if(event->key()==Qt::Key::Key_J){
        if(!player1.bullet.getActive()){
            player1.shot();

            //Qt6.5.1 使用QSoundEffect播放
//            QSoundEffect * shotSound = new QSoundEffect(this);
//            shotSound->setSource(QUrl::fromLocalFile(":/res/sound/shoot.wav"));
            shotSound.play();

//            QSoundEffect::play(":/res/sound/shoot.wav");
        }
    }
    else if(event->key()==Qt::Key::Key_K)
    {
        if(player1.nuclearbomb>0)
        {
                player1.nuclearbomb--;
                QSoundEffect *soundEffect = new QSoundEffect();
                soundEffect->setSource(QUrl::fromLocalFile(":/res/sound/nuclearbomb.wav"));
                soundEffect->setVolume(0.5);
                soundEffect->play();
                enemynum-=enemies.size();
                enemies.clear();
                QTimer::singleShot(1500, this, [=](){
                    if(enemynum<=0)return;
                    for(int i=0;i<4;++i) createEnemy();
                });
        }
    }
    else if(event->key()==Qt::Key::Key_V){enemynum=0;}
    else if(event->key()==Qt::Key::Key_L){player1.hp=0;}
}

void PlayWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key::Key_J){return;}
    else{player1.ismove=false;}
}

void PlayWindow::collisionCheck()//检验碰撞函数
{//玩家坦克子弹与敌方坦克子弹碰撞检测
    for(auto& enemy:enemies){
        if(player1.bullet.rect.intersects(enemy.bullet.rect)==true){
            if(!player1.bullet.super) player1.bullet.setActive(false);
            enemy.bullet.setActive(false);
            break;
        }
        else if(headRect.intersects(enemy.bullet.rect)==true||headRect.intersects(player1.bullet.rect)==true){
            head.load(":/res/pic/camp1.gif");
            head=resizePic(head,SIZE,SIZE);
            flag = true;
            campSound.play();
            update();
        }
    }

    //玩家坦克子弹与敌方坦克碰撞检测
    for(auto enemy=enemies.begin();enemy!=enemies.end();enemy++){
        if(player1.bullet.rect.intersects(enemy->rect)==true){

            //Qt6.5.1 使用QSoundEffect播放
//            QSoundEffect * enemyBombSound = new QSoundEffect(this);
//            enemyBombSound->setSource(QUrl::fromLocalFile(":/res/sound/enemy-bomb.wav"));
            enemyBombSound.play();

//            QSoundEffect::play(":/res/sound/enemy-bomb.wav");

            enemies.erase(enemy);
            enemynum--;
            if(enemynum<=0){return;}
            QTimer::singleShot(500, this, [=](){
                createEnemy();
            });
            player1.bullet.setActive(false);
            break;
        }
    }
    //玩家坦克与敌方坦克子弹碰撞检测
    for(auto &enemy:enemies){
        if(player1.rect.intersects(enemy.bullet.rect)){
            enemy.bullet.setActive(false);
            createPlayer();

            //Qt6.5.1 使用QSoundEffect播放
//            QSoundEffect * playerBombSound = new QSoundEffect(this);
//            playerBombSound->setSource(QUrl::fromLocalFile(":/res/sound/player-bomb.wav"));
            playerBombSound.play();

//            QSoundEffect::play(":/res/sound/player_bomb.wav");
            player1.hp--;
            break;
        }
    }

    //玩家坦克与敌方坦克碰撞检测
    for(auto enemy=enemies.begin();enemy!=enemies.end();enemy++){
        if(player1.rect.intersects(enemy->rect) == true){
            enemies.erase(enemy);
            enemynum--;
            createPlayer();

            //Qt6.5.1 使用QSoundEffect播放
            enemyBombSound.play();
            playerBombSound.play();

            player1.hp--;
            if(enemynum<=0){return;}
            createEnemy();
            break;
        }
    }
}

void PlayWindow::play(){
    if(player1.ismove){
        player1.move();
        toolnum-=player1.collectTool();

        //Qt6.5.1 使用QSoundEffect播放
//        QSoundEffect * moveSound = new QSoundEffect(this);
//        moveSound->setSource(QUrl::fromLocalFile(":/res/sound/move.wav"));
        moveSound.play();

//        QSoundEffect::play(":/res/sound/move.wav");
    }
}

void PlayWindow::enemyMove(){      //目前是随机策略
    static int d;
    srand((unsigned)time(NULL));
    for(auto& enemy:enemies){
        d = rand()%4;//随机方向
        if(d==0){enemy.setDir(direct::Left);}
        else if(d==1){enemy.setDir(direct::Up);}
        else if(d==2){enemy.setDir(direct::Right);}
        else if(d==3){enemy.setDir(direct::Down);}
        enemy.move();
    }
}

void PlayWindow::enemyShot(){
    for(auto&enemy:enemies){
        if(!enemy.bullet.getActive()){enemy.shot();}
    }
}

void PlayWindow::bulletMove(){
    if(player1.bullet.getActive()){player1.bullet.move();}
    for(auto& enemy:enemies){
        if(enemy.bullet.getActive()){enemy.bullet.move();}
    }
}

void PlayWindow::refresh(){
    collisionCheck();
    if(player1.hp<=0 || head_is_broken()) {
        failSound.play();
        gameover(0);
    }
    if(enemynum<=0) {
        winSound.play();
        gameover(1);
    }
    update();
}


void PlayWindow::gameover(int status){
    timer1->stop();
    timer2->stop();
    timer3->stop();
    timer4->stop();
    timer5->stop();
    timer6->stop();
    QTimer::singleShot(300, this, [=](){
        EndWindow *endwindow=new EndWindow(status,gate);
        this->hide();
        endwindow->setGeometry(this->geometry());
        endwindow->show();
        connect(endwindow,&EndWindow::returnmenu,[=](){
            this->close();
            emit returnmenu();
        });
        connect(endwindow,&EndWindow::exitgame,[=](){
            this->close();
        });
        connect(endwindow,&EndWindow::regame,[=](){
            while(!enemies.empty()) enemies.pop_front();
            this->show();
            this->init();
        });
        connect(endwindow,&EndWindow::nextgame,[=](){
            gate++;
            this->show();
            this->init();
        });
    });
}

bool PlayWindow::head_is_broken(){
    return flag;
}
