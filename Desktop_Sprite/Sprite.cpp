#include "Sprite.h"
#include<qdebug.h>
Sprite::Sprite(QWidget* parent):QPushButton(parent)
{
    widget=parent;
    setFixedSize(32,32);
    setFocusPolicy(Qt::NoFocus);
    pixmap=new QPixmap(":/new/picture/hero");
    this->setIcon(QIcon(pixmap->copy(0,0,32,32)));
    this->setFlat(true);
    setIconSize(this->size());

}
void Sprite::left_move(){
    ++state%=3;
    this->setIcon(QIcon(pixmap->copy(state*32,32,32,32)));
    if(this->x()>0){
        move(x()-(speed+100)/20,y());
        if(speed<10000)speed++;
    }
}
void Sprite::right_move(){
    ++state%=3;
    this->setIcon(QIcon(pixmap->copy(state*32,64,32,32)));
    if(this->x()<widget->width()-32){
        move(x()+(speed+100)/20,y());

        if(speed<10000)speed++;
    }
}
void Sprite::up_move(){
    ++state%=3;
    this->setIcon(QIcon(pixmap->copy(state*32,96,32,32)));
    if(this->y()>0){
        move(x(),y()-(speed+100)/20);
        if(speed<10000)speed++;
    }
}
void Sprite::down_move(){
    ++state%=3;
    this->setIcon(QIcon(pixmap->copy(state*32,0,32,32)));
    if(this->y()<widget->height()-32){
        move(x(),y()+(speed+100)/20);
        if(speed<10000)speed++;
    }
}
