#ifndef WEAPONS_H
#define WEAPONS_H
#include"sprite.h"

class weapons :public Sprite
{
public:
    weapons();
    weapons(int x,int y,const QString& filename,int hp,float gram,float speed,float cold_time,int nums_fire,float attacks_fire,int is_right,int mode_fire,int m_type);
    void setCold(float cold_time){this->cold_time=cold_time;}
    float getCold(){return cold_time;}
    void setNums(int nums){nums_fire=nums;}
    int getNums(){return nums_fire;}
    void setAttack(float Attack){attacks_fire=Attack;}
    float getAttack(){return attacks_fire;}
    void setMode(int Mode){mode_fire=Mode;}
    int getMode(){return mode_fire;}
    void setRight(int is){is_right=is;}
    int getRight(){return is_right;}
    void FIRE();
private:
    float cold_time;
    int nums_fire = 1;
    float attacks_fire;
    int is_right;//1表示朝右,-1表示朝左
    int mode_fire;//1表示连续一线,2表示散射
};

#endif // WEAPONS_H
