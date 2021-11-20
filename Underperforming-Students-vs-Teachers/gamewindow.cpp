#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "sleepdeprivedstudent.h"

#include "game.h"
#include <QString>
#include <QDebug>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QPainter>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setWindowTitle(Game::GAME_NAME);

    setFixedSize(windowWidth, windowHeight);

    this->game = Game::getInstance(this); //get the Singleton Game object

}

void GameWindow::resizeEvent(QResizeEvent *ev) {
    QMainWindow::resizeEvent(ev);
    this->game->currentSize = ev->size();

    int w = ev->size().width();
    int h = ev->size().height();

    game->getProgressBar()->move(w * 0.5, h * 0.5);

}

void GameWindow::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    p.drawPixmap(this->rect(), QPixmap(":/images/scene/game_scene.jpg"));
}

GameWindow::~GameWindow()
{
    delete ui;
}
