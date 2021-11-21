#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "sleepdeprivedstudent.h"

#include "game.h"
#include <QString>
#include <QDebug>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QThread>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setWindowTitle(Game::GAME_NAME);

    setFixedSize(windowWidth, windowHeight);

    this->game = Game::getInstance(this); //get the Singleton Game object

    game->start();
    QLabel* label = new QLabel(this);
    label->setScaledContents(true);
    label->setFixedSize(Human::spriteWidth, Human::spriteHeight);
    label->setPixmap(QPixmap(":/images/students/stu_sleep_0.png"));

    SleepDeprivedStudent* s = new SleepDeprivedStudent(label, nullptr);
    game->registerTimeVariant(s);
}

void GameWindow::resizeEvent(QResizeEvent *ev) {
    QMainWindow::resizeEvent(ev);
    this->game->currentSize = ev->size();

}

void GameWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(this->rect(), QPixmap(":/images/scene/game_scene.jpg"));
}

GameWindow::~GameWindow()
{
    delete ui;
}
