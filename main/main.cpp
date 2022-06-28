#include "mainwindow.h"
//#include <QMotifStyle>
#include <QApplication>
#include <QFrame>

MainWindow w;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("macintosh");
    // MainWindow w;
    w.show();
    return a.exec();
}
