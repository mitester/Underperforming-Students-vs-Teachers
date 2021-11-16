#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "game.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setWindowTitle(Game::GAME_NAME);
}

GameWindow::~GameWindow()
{
    delete ui;
}
