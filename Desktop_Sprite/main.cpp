#include <DesktopSprite.h>
#include <QApplication>
#include <QFrame>
#include <QGraphicsEffect>
#include <QObject>
#include <QPushButton>
#include <QWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DesktopSprite game;
    game.show();
    return a.exec();
}

