#include "Land_War.h"
#include"setting.h"
#include"thefight.h"
#include "ui_Land_War.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Land_War_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    //语言

    initBlocks();//载入方块
    Menu w;
    Setting setting;
    w.show();
    w.connect(w.getUi()->Settings_Button, &QPushButton::clicked, [&setting,&w]() {
        int x = w.x() + w.width()/7+w.width()/21;
        int y = w.y() + w.height()/8;
        setting.move(x, y);
        setting.show();//设置界面的打开
    });
    w.move(200,50);
    Player_Land* player = new Player_Land(1);
    TheFight fight(player);
    fight.setFixedSize(w.size());
    w.connect(w.getUi()->Start_Button, &QPushButton::clicked, [&fight,&w]() {
        fight.move(w.x(),w.y());
        fight.show();
        w.close();//战斗界面
    });
    return a.exec();
}
