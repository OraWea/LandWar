#include "thefight.h"
#include "ui_thefight.h"
#include<QPainter>
#include<QDebug>
#include<QTimer>
#include<QKeyEvent>
#include"sprite.h"
//此处为战斗模块
Player_Land* player;
Player_Land* enemy;

static bool is_energyover=false;
QVector2D tempvelocity;
TheFight::TheFight(Player_Land* playerl,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TheFight)
{
    ui->setupUi(this);
    QTimer* timer =new QTimer(this);
    timer->callOnTimeout(this,[=](){
        updateGame();
        update();
    });
    timer->start(1000/100);//帧率为100
    initFight(playerl);
}//此处使用QTimer用以更新

void TheFight::initFight(Player_Land* playerl){
    player =new Player_Land(*playerl);
    player->m=new Manager;
    enemy =new Player_Land(0);
    enemy->m=new Manager;
}
void TheFight::updateGame(){
    player->block_update();
    player->m->fire_update();
    enemy->block_update();
    enemy->m->fire_update();
}//更新游戏绘制

void TheFight::drawGame(QPainter* painter){
   player->draw(painter);
    enemy->draw(painter);
}

void TheFight::cleanGame(){

}

void TheFight::paintEvent(QPaintEvent* ev){
    QPainter* painter=new QPainter(this);
    drawGame(painter);//绘制
}
void TheFight::closeEvent(QCloseEvent *ev){
    cleanGame();
}

void TheFight::keyPressEvent(QKeyEvent* ev){//此处为各类键盘感应事件
switch(ev->key()){
case Qt::Key_Space:
    if(player->getEnergy()>0){
        if(!is_energyover){
            player->is_energycost=true;
            player->is_energygain=false;
    tempvelocity.setY(-1);
    player->setVelocity(tempvelocity);
        }
    }
    else{
        is_energyover=true;
        player->is_energycost=false;
    }
    break;//空格控制岛屿的上升
case Qt::Key_1:
    if(!player->player_weapons[0].first.isNull())
    player->m->add_fire(player->player_weapons[0].second,player->player_weapons[0].first);
    qInfo()<<player->player_weapons[2].first.isNull();
    break;
case Qt::Key_2:
    if(!player->player_weapons[1].first.isNull())
    player->m->add_fire(player->player_weapons[1].second,player->player_weapons[1].first);
    break;
case Qt::Key_3:
    if(!player->player_weapons[2].first.isNull()){
    player->m->add_fire(player->player_weapons[2].second,player->player_weapons[2].first);
    }
    break;
case Qt::Key_4:
    if(!player->player_weapons[3].first.isNull())
    player->m->add_fire(player->player_weapons[3].second,player->player_weapons[3].first);
    break;
case Qt::Key_5:
    if(!player->player_weapons[4].first.isNull())
    player->m->add_fire(player->player_weapons[4].second,player->player_weapons[4].first);
    break;//数字1~5控制岛屿的武器系统
    }
}

void TheFight::keyReleaseEvent(QKeyEvent* ev){
    switch(ev->key()){
    case Qt::Key_Space:
        player->is_energygain=true;
        tempvelocity.setY(0.3);
        player->setVelocity(tempvelocity);
        QTimer::singleShot(800,[&](){
             tempvelocity.setY(1);
             player->setVelocity(tempvelocity);
         });

        if(player->getEnergy()>10)
            is_energyover=false;
        break;
    }
}//此处为释放空格键后岛屿的下落

TheFight::~TheFight()
{
    delete ui;
}
