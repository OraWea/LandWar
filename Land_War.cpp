#include "Land_War.h"
#include "ui_Land_War.h"

Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Exit_Button,&QPushButton::clicked,&QApplication::closeAllWindows);
    this->setWindowTitle(QString("LandWar"));
    this->setFixedSize(1566,1111);
    setButtonColor();//主界面的信号与槽
}
Ui::MainWindow* Menu::getUi(){  return ui;}
void Menu::setButtonColor(){
    ui->Exit_Button->setStyleSheet("QPushButton { color: #00aaff; }"
                                   "QPushButton:hover { color: #ffff00; }"
                                   "QPushButton:pressed { color: #ff557f; }");
    ui->Start_Button->setStyleSheet("QPushButton { color: #00aaff; }"
                                   "QPushButton:hover { color: #ffff00; }"
                                   "QPushButton:pressed { color: #ff557f; }");
    ui->Settings_Button->setStyleSheet("QPushButton { color: #00aaff; }"
                                   "QPushButton:hover { color: #ffff00; }"
                                   "QPushButton:pressed { color: #ff557f; }");
    ui->Load_Button->setStyleSheet("QPushButton { color: #00aaff; }"
                                   "QPushButton:hover { color: #ffff00; }"
                                   "QPushButton:pressed { color: #ff557f; }");
    //主界面上按键没有触发,鼠标悬浮,鼠标点击三种时的不同状态
}
Menu::~Menu()
{
    delete ui;
}
