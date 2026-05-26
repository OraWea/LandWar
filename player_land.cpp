#include "player_land.h"
#include"blocksssss.h"
#include<QDebug>

Player_Land::Player_Land() {//玩家方块最左60,最右500,上320,下640
    initLand(this);
}

Player_Land::Player_Land(int i){
    if(i)
        initLand(this);
    else
        init_enemyLand(this);
}

void Player_Land::setdown_dpeed(){
    for(auto& block:blocks)
        down_speed+=block.second.getGram();
    down_speed/=10;
}
void Player_Land::setFlySpeed(){
    float temp_speed=0;
    for(auto& block:blocks){
        temp_speed+=block.second.getsp();
    }
    setSpeed(temp_speed);
}
void Player_Land::setHoleGram(){
    float temp_gram=0;
    for(auto& block:blocks){
        temp_gram+=block.second.getGram();
    }
    setGram(temp_gram);
}
void Player_Land::setHoleHp(){
    float temp_hp=0;
    for(auto& block:blocks){
        temp_hp+=block.second.gethp();
    }
    setGram(temp_hp);
}//计算整个岛屿的属性

void Player_Land::draw(QPainter* painter){
    for(auto& block:blocks){
        painter->drawPixmap(block.first.toPoint(),block.second.getPix());//岛屿上方块的绘制
    }
    m->fire_draw(painter);//炮弹的绘制
}

void Player_Land::block_update(){
    for(int i=0;i<blocks.size();i++){
        if(getVel().y()<0)
        blocks[i].first+=getVel()*getsp();
        else
            blocks[i].first+=getVel()*down_speed;
        blocks[i].second.collider=QRect(blocks[i].first.toPoint(),blocks[i].second.getPix().size());//方块的更新
    }
    for(auto& weapon:player_weapons){
        if(getVel().y()<0)
            weapon.first+=getVel()*getsp();
        else
            weapon.first+=getVel()*down_speed;//武器的更新
    }
    if(m->bombs.size()>0)
        m->fire_update();//炮弹的更新
}

void Player_Land::add_weapon(QVector2D position,Sprite* block,int weapon_site){
    blocks.push_back({position,*block});
    setSpeed(getsp()+block->getsp());//添加武器,也可以用于添加方块
    weapons* wee=dynamic_cast<weapons*>(block);
    if(wee){
        player_weapons[weapon_site-1].second=wee;
        player_weapons[weapon_site-1].first=position;
    }
}

void Player_Land::update(){
    if(is_energycost){
        if(fly_energy>0)
            fly_energy+=energy_costspeed;//更新能量,上升时减少
        else
            fly_energy=0;
    }
    else if(is_energygain){
        if(fly_energy<100)
            fly_energy+=energy_gainspeed;//下落时增加
        else
            fly_energy=100;
    }
}


