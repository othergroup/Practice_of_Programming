#ifndef SPRITE_H
#define SPRITE_H
#include<QPushButton>

class Sprite : public QPushButton
{
public:
    Sprite(QWidget *parent = nullptr);
    QWidget* widget;
    int speed=0;
    int state=0;
    QPixmap *pixmap;
    void left_move();
    void right_move();
    void up_move();
    void down_move();
protected:

};

#endif // SPRITE_H
