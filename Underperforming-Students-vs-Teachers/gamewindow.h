#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "game.h"
#include <QResizeEvent>

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

private:
    Ui::GameWindow *ui;
    Game* game;
};

#endif // GAMEWINDOW_H
