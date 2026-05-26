#include "sprite.h"
#include<QDebug>

Sprite::Sprite() {

}

Sprite::Sprite(int x,int y,const QString &filename):position(x,y)
{
    pixmap.load(filename);
}
Sprite::Sprite(int x,int y,const QString& filename,int hp,float gram,float speed,int m_type):position(x,y),hp(hp),gram(gram),speed(speed)
{
    setType(m_type);
    pixmap.load(filename);//读取文件
}
void Sprite::update(){
    position+=speed*velocity;
    collider=QRect(position.toPoint(),pixmap.size());//更新位置和碰撞箱
    if(hp<=0)
        destroy();
}

void Sprite::draw(QPainter* painter){
    painter->drawPixmap(position.toPoint(),pixmap);
}
