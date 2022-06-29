#include "mainwindow.h"
//#include <QMotifStyle>
#include <QApplication>
#include <QFrame>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("macintosh");
    MainWindow w;
    w.show();
    return a.exec();
}
