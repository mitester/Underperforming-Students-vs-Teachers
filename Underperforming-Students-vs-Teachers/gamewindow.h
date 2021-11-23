#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "game.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

protected:
    void resizeEvent(QResizeEvent* ev);
    void paintEvent(QPaintEvent* ev);

private:
    Ui::GameWindow *ui;
    Game* game;
    int windowWidth = 1280;
    int windowHeight = 720;

    void changeRedbullNum(int n);
};

#endif // GAMEWINDOW_H
