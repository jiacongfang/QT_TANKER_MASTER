#ifndef STOPWINDOW_H
#define STOPWINDOW_H

#include <QMainWindow>

class StopWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit StopWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);

signals:
    void exitgame();
    void returnmenu();
    void continuegame();

public slots:
};

#endif // STOPWINDOW_H
