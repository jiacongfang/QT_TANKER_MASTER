#ifndef SELECTIONWINDOW_H
#define SELECTIONWINDOW_H

#include <QMainWindow>
#include "QLabel"

class SelectionWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SelectionWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);
    int total_number; //目前开放的总关卡数
    QLabel *note;
signals:
    void returnmenu();

public slots:

};

#endif // SELECTIONWINDOW_H
