#include "weapons.h"
#include<QTimer>
#include"blocksssss.h"
weapons::weapons() {}
weapons::weapons(int x,int y,const QString& filename,int hp,float gram,float speed,float cold_time,int nums_fire,float attacks_fire,int is_right,int mode_fire,int m_type)
{
    this->hp=hp;
    this->gram=gram;
    this->speed=speed;
    this->cold_time=cold_time;
    this->nums_fire=nums_fire;
    this->attacks_fire=attacks_fire;
    this->is_right=is_right;
    this->mode_fire=mode_fire;
    setType(m_type);
    pixmap.load(filename);
}//构造函数
void weapons::FIRE(){

}
