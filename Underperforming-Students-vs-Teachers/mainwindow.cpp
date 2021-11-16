#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Underperforming Students VS Teachers");
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

