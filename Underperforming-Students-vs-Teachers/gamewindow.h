#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "game.h"
#include <QPoint>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    static QPoint getClosestGridPos(QPoint p);

protected:
    void resizeEvent(QResizeEvent* ev);
    void paintEvent(QPaintEvent* ev);
    void mousePressEvent(QMouseEvent* ev);
    void mouseMoveEvent(QMouseEvent* ev);

private:
    Ui::GameWindow *ui;
    Game* game;
    int windowWidth = 1280;
    int windowHeight = 720;

    QMainWindow* mainWindow;
};

#endif // GAMEWINDOW_H
