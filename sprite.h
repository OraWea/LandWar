#ifndef SPRITE_H
#define SPRITE_H
#include<QString>
#include<QVector2D>
#include<QPixmap>
#include"entity.h"

class Sprite : public Entity{//精灵
public:
    Sprite();
    Sprite(int x,int y,const QString& filename);
    Sprite(int x,int y,const QString& filename,int hp,float gram,float speed,int m_type);
    virtual void update() override;
    void draw(QPainter* painter)override;
    void setVelocity(QVector2D vel){velocity=vel;}
    void setSpeed(int sp){speed=sp;}
    void sethp(int hp){this->hp=hp;}
public:
    QPixmap getPix(){return pixmap;}
    QVector2D getVel(){return velocity;}
    float getsp(){return speed;}
    int gethp(){return hp;}
    void setGram(float gram){this->gram=gram;}
    float getGram(){return gram;}
public:
    QRect collider;//碰撞箱
    QVector2D position;  //坐标
protected:
    QPixmap pixmap;   //对应的图片
    QVector2D velocity;//方向
    float speed = 0;//速度
    int hp;
    float gram;//重量
};

#endif // SPRITE_H
