#ifndef LAND_WAR_H
#define LAND_WAR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr);
    Ui::MainWindow* getUi();
    void setButtonColor();
    ~Menu();

private:
    Ui::MainWindow *ui;
};
#endif // LAND_WAR_H
