#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QMainWindow>

class HelpWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit HelpWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);

signals:
    void returnmenu();

public slots:
};

#endif // HELPWINDOW_H
