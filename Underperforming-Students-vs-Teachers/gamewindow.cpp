#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "redbull.h"
#include "clickablelabel.h"

#include "game.h"
#include "pang.h"
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
    game->getRowAt(0)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 0);
    game->getRowAt(0)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 1);
    game->getRowAt(0)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 2);
    game->getRowAt(0)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 3);
    game->getRowAt(0)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 4);
    game->getRowAt(0)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 5);

    game->getRowAt(1)->addStudent(TimeVariant::Type::DEADLINE_FIGHTER, 0);
    game->getRowAt(1)->addStudent(TimeVariant::Type::SHAMELESS_STUDENT, 1);


    game->getRowAt(2)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 0);
    game->getRowAt(2)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 1);
    game->getRowAt(2)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 2);
    game->getRowAt(2)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 3);
    game->getRowAt(2)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 4);
    game->getRowAt(2)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 5);

    game->getRowAt(3)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 0);
    game->getRowAt(3)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 1);
    game->getRowAt(3)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 2);
    game->getRowAt(3)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 3);
    game->getRowAt(3)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 4);
    game->getRowAt(3)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 5);

    game->getRowAt(4)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 0);
    game->getRowAt(4)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 1);
    game->getRowAt(4)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 2);
    game->getRowAt(4)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 3);
    game->getRowAt(4)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 4);
    game->getRowAt(4)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 5);

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
