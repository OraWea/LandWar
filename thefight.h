#ifndef THEFIGHT_H
#define THEFIGHT_H
#include"player_land.h"
#include <QMainWindow>

namespace Ui {
class TheFight;
}

class TheFight : public QMainWindow
{
    Q_OBJECT

public:
    explicit TheFight(Player_Land* player,QWidget *parent = nullptr);
    void updateGame();
    void cleanGame();
    void drawGame(QPainter* painter);
    void initFight(Player_Land* player);
    ~TheFight();

protected:
    void paintEvent(QPaintEvent* ev)override;
    void closeEvent(QCloseEvent *ev)override;
    void keyPressEvent(QKeyEvent* ev)override;
    void keyReleaseEvent(QKeyEvent* ev)override;//战斗事件
protected:
    Ui::TheFight *ui;
};

#endif // THEFIGHT_H
