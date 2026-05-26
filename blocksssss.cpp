#include"blocksssss.h"
#include"weapons.h"
#include<map>
#include<QDebug>
#include"player_land.h"
using std::map;

map<int,Sprite> blocks_search;
map<int,weapons> weapons_search;
void initBlocks(){
    //TYPE:  land:0,core:1,basic_block:2~10,fly:11~15,weapons:16~24,bomb:25与27,others:25+;
    Sprite sand(0,0,":/block/images/block/sand.jpg",100,1,0,2);
    Sprite core(0,0,":/block/images/block/core.jpg",100,5,0,1);
    Sprite medium_fly(0,0,":/block/images/block/medium_fly.jpg",50,1,4,11);
    weapons medium_fire_right(0,0,":/block/images/block/medium_fire_right.jpg",75,2,0,3,1,30,1,1,18);
    weapons medium_fire_left(0,0,":/block/images/block/medium_fire_left.jpg",75,2,0,3,1,30,-1,1,16);
    Sprite bomb_left(0,0,":/block/images/block/bomb1_left.jpg",1,0,3,25);
    Sprite bomb_right(0,0,":/block/images/block/bomb1_right.jpg",1,0,3,27);
    blocks_search.insert({1,core});
    blocks_search.insert({2,sand});
    blocks_search.insert({11,medium_fly});
    weapons_search.insert({18,medium_fire_right});
    weapons_search.insert({16,medium_fire_left});
    blocks_search.insert({27,bomb_right});
    blocks_search.insert({25,bomb_left});
}//此处为各类的方块,载入后方便重复使用

Sprite getBlock(int num){
    auto it= blocks_search.find(num);
    return it->second;
}//获取方块

weapons getWeapon(int num){
    auto it =weapons_search.find(num);
    return it->second;
}//获取武器

void initLand(Player_Land* land){//基础岛屿的载入,目前作为战斗的测试用
    land->blocks.push_back({{300,480},getBlock(1)});
    land->blocks.push_back({{300,440},getBlock(2)});
    land->blocks.push_back({{340,480},getBlock(2)});
    land->blocks.push_back({{260,480},getBlock(2)});
    land->blocks.push_back({{300,520},getBlock(2)});
    land->blocks.push_back({{260,520},getBlock(2)});
    land->blocks.push_back({{340,520},getBlock(2)});
    land->blocks.push_back({{380,480},getBlock(2)});
    land->blocks.push_back({{220,480},getBlock(2)});
    land->blocks.push_back({{260,560},getBlock(11)});
    land->blocks.push_back({{340,560},getBlock(11)});
    weapons* w=new weapons(getWeapon(18));
    land->add_weapon({340,440},w,1);
    weapons* m=new weapons(getWeapon(16));
    land->add_weapon({260,440},m,2);
    land->setFlySpeed();
    land->setHoleGram();
    land->setHoleHp();
    land->setdown_dpeed();//设置并读取岛屿
}

void init_enemyLand(Player_Land* land){
    land->blocks.push_back({{1200,480},getBlock(1)});
    land->blocks.push_back({{1200,440},getBlock(2)});
    land->blocks.push_back({{1240,480},getBlock(2)});
    land->blocks.push_back({{1160,480},getBlock(2)});
    land->blocks.push_back({{1200,520},getBlock(2)});
    land->blocks.push_back({{1160,520},getBlock(2)});
    land->blocks.push_back({{1240,520},getBlock(2)});
    land->blocks.push_back({{1280,480},getBlock(2)});
    land->blocks.push_back({{1120,480},getBlock(2)});
    land->blocks.push_back({{1160,560},getBlock(11)});
    land->blocks.push_back({{1240,560},getBlock(11)});
    weapons* w=new weapons(getWeapon(18));
    land->add_weapon({1240,440},w,1);
    weapons* m=new weapons(getWeapon(16));
    land->add_weapon({1160,440},m,2);
    land->setFlySpeed();
    land->setHoleGram();
    land->setHoleHp();
    land->setdown_dpeed();//敌人的岛屿
}
