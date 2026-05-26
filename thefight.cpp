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

// ============================================================
// 敌方 AI 状态机
// 状态: APPROACH(靠近) → ATTACK(攻击) ↔ EVADE(逃离)
// ============================================================
struct EnemyAI {
    enum State { APPROACH, ATTACK, EVADE } state = APPROACH;
    int  tick = 0;
    float fireCooldowns[5] = {}; // 每个武器棽的开火冷却(tick数)
    int  initialBlocks = 0;      // 初始方块数量(用于估算HP)
    bool initialized = false;

    static constexpr float ATTACK_RANGE = 700.0f; // 切换至ATTACK状态的距离阈値(像素)

    // 初始化 AI
    void init(Player_Land* e) {
        initialBlocks = (int)e->blocks.size();
        for(int i = 0; i < 5; i++) fireCooldowns[i] = 0;
        initialized = true;
    }

    // 估算敌方岛屿剩余HP百分比（以剩余方块数量占初始的比例计）
    int hpPercent(const Player_Land* e) const {
        if(initialBlocks == 0) return 100;
        return (int)(e->blocks.size() * 100 / (size_t)initialBlocks);
    }

    // 根据目标高度返回建议的纵向速度分量
    // 返回-1.0表示需要上升，+0.8表示下落，0保持当前
    float altitudeVelY(const Player_Land* e, float targetY) const {
        float curY = e->getCenter().y();
        if(curY > targetY + 40.0f) return -1.0f;   // 岛屿偏低 → 上升
        if(curY < targetY - 40.0f) return  0.8f;   // 岛屿偏高 → 下落
        return 0.0f;                                 // 高度合适
    }

    // 尝试对所有武器棽开火（带独立冷却时间）
    void tryFire(Player_Land* e) {
        for(int i = 0; i < 5; i++) {
            if(fireCooldowns[i] > 0) { fireCooldowns[i]--; continue; }
            auto& wp = e->player_weapons[i];
            if(!wp.first.isNull() && wp.second != nullptr) {
                e->m->add_fire(wp.second, wp.first);
                // cold_time 单位为秒，乘以100fps得到tick冷却时间
                fireCooldowns[i] = wp.second->getCold() * 100.0f;
            }
        }
    }

    // 每帧调用：更新状态机并执行对应行为
    void update(Player_Land* playerL, Player_Land* enemyL) {
        if(!initialized) init(enemyL);
        tick++;

        QVector2D eCenter = enemyL->getCenter();
        QVector2D pCenter = playerL->getCenter();
        float dx  = eCenter.x() - pCenter.x(); // 正値: 敌在玩家右侧
        int   hp  = hpPercent(enemyL);

        // ── 状态转移 ────────────────────────────────────
        switch(state) {
        case APPROACH:
            if(qAbs(dx) < ATTACK_RANGE)             state = ATTACK;
            break;
        case ATTACK:
            if(hp < 30)                             state = EVADE;
            else if(qAbs(dx) > ATTACK_RANGE + 150)  state = APPROACH;
            break;
        case EVADE:
            if(hp >= 45)                            state = ATTACK; // 回血后重新进攻
            break;
        }

        // ── 执行当前状态行为 ───────────────────────────
        float velX = 0.0f;
        float velY = altitudeVelY(enemyL, pCenter.y()); // 默认: 跟踪玩家高度

        switch(state) {
        case APPROACH:
            // 横向向玩家靠近
            velX = (dx > 0) ? -0.6f : 0.6f;
            break;

        case ATTACK:
            // 轻微左右挥动，让敌方看起来有机动性
            velX = ((tick / 50) % 2 == 0) ? -0.12f : 0.12f;
            // 持续开火（带冷却）
            tryFire(enemyL);
            break;

        case EVADE:
            // 向右逃离 + 拉升高度
            velX =  1.2f;
            velY = -1.0f;
            // 逃跑时偏尔回射
            if(tick % 80 == 0) tryFire(enemyL);
            break;
        }

        enemyL->setVelocity(QVector2D(velX, velY));
    }
};
static EnemyAI enemyAI; // 全局敌方AI实例

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
    // 重置并初始化敌方AI
    enemyAI = EnemyAI();
    enemyAI.init(enemy);
}
void TheFight::updateGame(){
    player->block_update();
    player->m->fire_update();
    enemy->block_update();
    enemy->m->fire_update();
    enemyAI.update(player, enemy); // 每帧更新敌方AI
}//更新游戏绘刽制

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
