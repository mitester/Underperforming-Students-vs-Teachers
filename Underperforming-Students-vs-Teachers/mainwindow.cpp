#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewindow.h"
#include "game.h"

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


void MainWindow::on_btn_start_clicked()
{
    this->hide();
    gameWindow = new GameWindow(this);
    gameWindow->show();
}

