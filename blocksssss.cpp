#include"blocksssss.h"
#include"weapons.h"
#include<map>
#include<set>
#include<algorithm>
#include<QDebug>
#include<QRandomGenerator>
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
    QRandomGenerator* rng = QRandomGenerator::global();
    const int bs = 40;   // 每个方块的像素尺寸
    const int cx = 1200; // 岛屿中心 X
    const int cy = 480;  // 岛屿中心 Y
    float hard = land->getenemy_hard(); // 默认 1.0f

    // 记录已占用的网格坐标集合（检测重叠）
    std::set<std::pair<int,int>> occupied;

    // 辅助 lambda：在网格偏移(gx, gy)处放置指定类型的方块
    auto place = [&](int gx, int gy, int blockType){
        occupied.insert({gx, gy});
        land->blocks.push_back({
            {(float)(cx + gx * bs), (float)(cy + gy * bs)},
            getBlock(blockType)
        });
    };

    // 1) 核心方块（固定
    place(0, 0, 1);

    // 2) 随机堂土方块
    std::vector<std::pair<int,int>> sandSlots = {
        {0,-1},{0,1},{-1,0},{1,0},
        {-1,-1},{1,-1},{-1,1},{1,1},
        {0,-2},{-2,0},{2,0},{0,2},
        {-1,-2},{1,-2},{-2,-1},{2,-1}
    };
    for(int i = (int)sandSlots.size()-1; i > 0; --i){
        int j = (int)rng->bounded((quint32)(i + 1));
        std::swap(sandSlots[i], sandSlots[j]);
    }
    int sandCount = 5 + (int)hard + (int)rng->bounded(5u);
    sandCount = std::min(sandCount, (int)sandSlots.size());
    int sa = 0;
    for(auto& p : sandSlots){
        if(sa >= sandCount) break;
        if(!occupied.count(p)){ place(p.first, p.second, 2); sa++; }
    }

    // 3) 随机飞行引擎（岛屿下方）
    std::vector<std::pair<int,int>> engSlots = {{-1,1},{0,1},{1,1},{-1,2},{0,2},{1,2}};
    for(int i = (int)engSlots.size()-1; i > 0; --i){
        int j = (int)rng->bounded((quint32)(i + 1));
        std::swap(engSlots[i], engSlots[j]);
    }
    int engCount = 1 + (int)rng->bounded(2u) + (int)(hard * 0.5f);
    engCount = std::min(engCount, 3);
    int ea = 0;
    for(auto& p : engSlots){
        if(ea >= engCount) break;
        if(!occupied.count(p)){ place(p.first, p.second, 11); ea++; }
    }

    // 4) 随机武器（朝左朝向玩家）
    std::vector<std::pair<int,int>> wepSlots = {{-1,-1},{0,-1},{1,-1},{-2,0},{-2,-1}};
    for(int i = (int)wepSlots.size()-1; i > 0; --i){
        int j = (int)rng->bounded((quint32)(i + 1));
        std::swap(wepSlots[i], wepSlots[j]);
    }
    int wepCount = 1 + (int)(hard * 0.5f) + (int)rng->bounded(2u);
    wepCount = std::min(wepCount, 3);
    int slot = 1;
    for(auto& p : wepSlots){
        if(slot > wepCount) break;
        if(!occupied.count(p)){
            weapons* w = new weapons(getWeapon(16)); // is_right=-1, 朝左射击
            land->add_weapon(
                {(float)(cx + p.first * bs), (float)(cy + p.second * bs)},
                w, slot
            );
            occupied.insert(p);
            slot++;
        }
    }

    land->setFlySpeed();
    land->setHoleGram();
    land->setHoleHp();
    land->setdown_dpeed();//敌人的岛屿（随机生成）
}
