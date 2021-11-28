#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewindow.h"
#include "game.h"
#include "spritecard.h"
#include "timevariant.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(Game::GAME_NAME);
    SpriteCard* card = new SpriteCard(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, this);
    card->move(0, 0);
    card->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
}

void MainWindow::on_btn_start_clicked()
{
    this->hide();
    gameWindow = new GameWindow(this);
    gameWindow->show();
}

