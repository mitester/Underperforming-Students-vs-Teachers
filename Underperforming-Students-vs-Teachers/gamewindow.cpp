#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "sleepdeprivedstudent.h"

#include "game.h"
#include <QString>
#include <QDebug>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setWindowTitle(Game::GAME_NAME);

    this->game = Game::getInstance(this);
    game->currentSize = size();

    SleepDeprivedStudent* s = new SleepDeprivedStudent(new QLabel(this), nullptr);
}

void GameWindow::resizeEvent(QResizeEvent *ev) {
    this->game->currentSize = ev->size();
}

GameWindow::~GameWindow()
{
    delete ui;
}
