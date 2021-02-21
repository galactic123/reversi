#ifndef GAMEUI_H
#define GAMEUI_H

#include <QWidget>
#include <mainwindow.h>
#include <QPushButton>
#include <QTextEdit>
namespace Ui {
class gameUI;
}

class gameUI : public QWidget
{
    Q_OBJECT

public:
    explicit gameUI(QWidget *parent = nullptr);
    ~gameUI();

private:
    Ui::gameUI *ui;
    MainWindow *chess;
    void init();
public slots:
    void restart_click();
    void reciveresultdata(int i);
    void recivestasticdata(int black,int white);
};

#endif // GAMEUI_H
