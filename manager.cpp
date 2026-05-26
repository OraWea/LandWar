#include "manager.h"
#include"blocksssss.h"
#include<QTimer>
#include<QDebug>
Manager::Manager() {}


void Manager::add_fire(weapons* weapon,QVector2D position){
//添加炮弹的函数
    int i=weapon->getNums();
    while(i>0){
        Sprite bomb=(getBlock(26+weapon->getRight()));
        bombs.push_back({position,bomb});
        i--;
    }
}
void Manager::fire_update(){//更新炮弹的函数
    int i=0;
    for(auto& bomb:bombs){
        bomb.second.update();
        bomb.first.setX(bomb.second.getsp()*(bomb.second.type()-26 )+bomb.first.x());
        if(bomb.first.x()>1640){
            bombs.erase(bombs.begin()+i);
        }
        if(bomb.first.x()<0)
            bomb.first.setX(1600);
        if(bomb.first.x()<750&&bomb.first.x()>600&&bomb.second.type()==25){
            bombs.erase(bombs.begin()+i);}//当炮弹位置超过范围时删除
        if(bomb.second.gethp()<=0){
                bombs.erase(bombs.begin()+i);
        }//当炮弹生命值降为0,即碰撞后删除.
        i++;
        bombs.shrink_to_fit();
    }
}

void Manager::fire_draw(QPainter* painter){
    for(auto& bomb:bombs)
        painter->drawPixmap(bomb.first.toPoint(),bomb.second.getPix());//炮弹绘制
}

void Manager::destroy_fire(){

}
