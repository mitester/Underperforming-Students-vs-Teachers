#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewindow.h"
#include "game.h"
#include "spritecard.h"
#include "timevariant.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(Game::GAME_NAME);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//it paints the background whenever this windows opened
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), QPixmap(":/images/scene/game_scene_mainwindow.png"));
}

//detect the mouse press and check if it clicks the start button
void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    QPointF p = ev->pos();
    float x = p.x() / width();
    float y = p.y() / height();

    //this range is the start button location
    if(x >= 360/800.0 && x<=455/800.0 && y >=435/600.0 && y<=495/600.0)
    {
        hide();
        gameWindow = new GameWindow(this);
        gameWindow->show();
    }
    else //if not clicking the start button, pass it back to father's mousePressEvent
    {
        QMainWindow::mousePressEvent(ev);
    }
}

