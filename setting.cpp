#include "setting.h"
#include "ui_setting.h"

Setting::Setting(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Setting)
{
    ui->setupUi(this);
    connect(ui->close_button,&QPushButton::clicked,this,&QWidget::close);
    this->setFixedSize(QSize(800, 720));
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->Music_slider->setMaximum(100);
    ui->SFX_slider->setMaximum(100);//设置界面相关,目前暂无音乐
}

Setting::~Setting()
{
    delete ui;
}
