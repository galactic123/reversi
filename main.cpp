
#include "gameui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gameUI game;
    game.show();
    return a.exec();
}
