#include "DesktopSprite.h"
#include <time.h>
#include <QApplication>
#include <QScreen>
//#include<windows.h>
#include<QTimer>
#include<QDebug>
#include<time.h>
#include<QToolTip>

DesktopSprite::DesktopSprite(QWidget *parent)
    : QDialog(parent)
{
    QScreen *screen=QGuiApplication::primaryScreen ();
    QRect mm = screen->availableGeometry();
    this->setGeometry(mm);
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Dialog);
    setAttribute(Qt::WA_TranslucentBackground);
    sprite = new Sprite(this);
    sprite->move(mm.width() / 2, mm.height() / 2);
    srand(time(0));
    QTimer *timer = new QTimer(this);
    QString text = "你有ddl了！！！";
    connect(timer, &QTimer::timeout, [=]() {
        if(!is_delete)
        {
            auto key=Qt::Key_Down;
            count+=25;
            if (count >= end_time || sprite->x() >= this->width() - 32
                    || sprite->y() >= this->height() - 32 || sprite->x() <= 1 || sprite->y() <= 1) {
                for (int i = 0; i < 1e3; i++)
                    ;
                end_time=(6+rand()%7)*100;
                count=0;
                dir=rand()%5;
                sprite->speed = 0;
            }
            switch (dir) {
            case 0:
                return;
                break;
            case 1:
                key=Qt::Key_Down;
                break;
            case 2:
                key=Qt::Key_Up;
                break;
            case 3:
                key=Qt::Key_Left;
                break;
            case 4:
                key=Qt::Key_Right;
                break;
            default:
                break;
            }
            QKeyEvent tabKey(QEvent::KeyPress, key, Qt::NoModifier);
            QCoreApplication::sendEvent(this, &tabKey);
            QToolTip::showText(QPoint(sprite->x() + 32, sprite->y() - 32),
                               text,
                               this,
                               QRect(100, 100, 100, 100));
        }
    });
    connect(this,SIGNAL(stop()),timer,SLOT(stop()));
    timer->start(42);
    connect(sprite, &QPushButton::clicked, [=]() {
        is_close=true;
        is_delete=true;
        QToolTip::hideText();
        this->close();
    });
    QTimer *end=new QTimer(this);
    connect(end,&QTimer::timeout,[=](){
        is_delete=true;
        QToolTip::hideText();
        this->close();
    });
    end->start(30000);
}
void DesktopSprite::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        sprite->up_move();
        break;
    case Qt::Key_Down:
        sprite->down_move();
        break;
    case Qt::Key_Left:
        sprite->left_move();
        break;
    case Qt::Key_Right:
        sprite->right_move();
        break;
    default:
        break;
    }
}
void DesktopSprite::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
        event->ignore();
    else
        sprite->speed = 0;
}
