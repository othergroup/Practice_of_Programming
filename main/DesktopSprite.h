#ifndef DESKTOPSPRITE_H
#define DESKTOPSPRITE_H
#include <QDialog>
#include <Sprite.h>
#include <QKeyEvent>
class DesktopSprite : public QDialog
{
    Q_OBJECT
public:
    explicit DesktopSprite(QWidget *parent = 0);
    Sprite *sprite;
    bool is_close=false;
    bool is_delete=false;
    int count=0;
    int dir=0;
    int end_time=1000;
    void left_move();
    void right_move();
    void down_move();
    void up_move();
signals:
    void stop();
public slots:
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

};

#endif // DESKTOPSPRITE_H
