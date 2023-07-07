#ifndef CONFIG_H
#define CONFIG_H
//这是一些基本的环境参数配置
#include<QString>

extern char map[26][27];   //存储地图, extern 关键字用来外部变量，防止重复定义
extern const QString rootdir;  //存储根目录
enum direct{Up, Right, Down, Left}; //方向
//direct::up;
//定义宏resizePic（p, w, h) p:picture, w:width, h:height
#define resizePic(p, w, h) p.scaled(w, h, Qt::AspectRatioMode::IgnoreAspectRatio, Qt::TransformationMode::SmoothTransformation)

#define BaseSize 20     //一个BaseSize算map里的一格
#define SIZE 40         //tank大小----建议把界面做出来调一调看是要 20/40？
#define WIDTH 600
#define HEIGHT 600

// 刷新率 ms
#define playRACE 120
#define enemyMoveRACE 120
#define enemyShotRACE 1000
#define bulletMoveRACE 60
#define refreshRACE 33
#define toolRACE 5000
#define RACE 100    //DIY刷新率

//地图障碍--宏
#define EMPTY '0'
#define GRASS '1'
#define STONE '3'
#define IRON '5'
#define RIVER '4'
#define HEAD '2'
#define BROKEN_HEAD '6'
#define LIFE '7'
#define SUPERBULLET '8'
#define NUCLEARBOMB '9'

#define NUM 5  //开放的关卡数

#endif // CONFIG_H
