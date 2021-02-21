#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QDebug>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void sendresultdata(int);
    void sendstasticdata(int,int);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString bg_name;
    int gridwith,gridhight,startX,startY;
    int chessmap[8][8];
    int change[8];
    int gridcolor;
    void init();
    int num_judge(int x,int y,int color,bool ischange=0);

private:
    Ui::MainWindow *ui;


protected:
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent*);
    void mousePressEvent(QMouseEvent*);

};
#endif // MAINWINDOW_H
