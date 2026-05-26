#ifndef PLAYER_LAND_H
#define PLAYER_LAND_H
#include"sprite.h"
#include<vector>
#include<unordered_set>
#include"blocksssss.h"
#include"manager.h"
#include"weapons.h"
using std::vector;
using std::unordered_set;

class Player_Land : public Sprite
{
public:
    Player_Land();//岛屿,里面包含着方块的集合与飞行能量及武器等.
    Player_Land(int i);
    void draw(QPainter* painter) override;
    void block_update();
    void add_weapon(QVector2D position,Sprite* block,int weapon_site);
    void update() override;
    void setEnergy(int fly_energy){this->fly_energy=fly_energy;}
    int getEnergy(){return fly_energy;}
    void setcostspeed(float energy_costspeed){this->energy_costspeed=energy_costspeed;}
    float getcostspeed(){return energy_costspeed;}
    void setgainspeed(float energy_gainspeed){this->energy_gainspeed=energy_gainspeed;}
    float getgainspeed(){return energy_costspeed;}
    void setenemy_hard(float enemy_hard){this->enemy_hard=enemy_hard;}
    float getenemy_hard(){return enemy_hard;}
    void setdown_speed(float down_speed){this->down_speed=down_speed;}
    float getdown_speed(){return down_speed;}//各类setter和getter
    void setdown_dpeed();
    void setFlySpeed();
    void setHoleGram();
    void setHoleHp();

public:
    vector<QPair<QVector2D,Sprite>> blocks;
    bool is_energycost=false;
    bool is_energygain=true;
    Manager* m;
    QPair<QVector2D,weapons*> player_weapons[5];
private:
    float enemy_hard;
    float energy_costspeed=-10;
    float weaponscold[6];
    float down_speed=0;
    int fly_energy=100;
    float energy_gainspeed=20;
};

#endif // PLAYER_LAND_H
