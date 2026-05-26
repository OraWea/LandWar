#ifndef MANAGER_H
#define MANAGER_H
#include"weapons.h"
#include<vector>
#include<QSet>

class Manager
{
public:
    Manager();
    void add_fire(weapons* weapon,QVector2D position);
    void fire_update();
    void fire_draw(QPainter* painter);
    void destroy_fire();
    void setIsP(bool is){is_player=is;}
    bool getIsp(){return is_player;}
private:
    bool is_player;
public:
    std::vector<QPair<QVector2D,Sprite>> bombs;
};

#endif // MANAGER_H
