#include "gamewindow.h"
#include "ui_gamewindow.h"

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
}

void GameWindow::resizeEvent(QResizeEvent *ev) {
    this->game->currentSize = ev->size();
    qDebug() << QString::number(this->game->currentSize.width()) << " " << QString::number(this->game->currentSize.height());
}

GameWindow::~GameWindow()
{
    delete ui;
}
