#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "redbull.h"
#include "clickablelabel.h"

#include "game.h"
#include "cgagod.h"
#include "gbusstudent.h"
#include "shamelessstudent.h"
#include "sleepdeprivedstudent.h"
#include "deadlinefighter.h"
#include "teacherspet.h"

#include "overworkedta.h"
#include "kelvin.h"
#include "pang.h"
#include "desmond.h"

#include "spritecard.h"
#include <QString>
#include <QDebug>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QThread>
#include <QWidget>
#include <QVBoxLayout>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setWindowTitle(Game::GAME_NAME);

    setFixedSize(windowWidth, windowHeight);

    this->game = Game::getInstance(this); //get the Singleton Game object

    SleepDeprivedStudent::PIC_0 = new QPixmap(":/images/students/stu_sleep_0.png");
    SleepDeprivedStudent::PIC_1 = new QPixmap(":/images/students/stu_sleep_1.png");
    SleepDeprivedStudent::PIC_2 = new QPixmap(":/images/students/stu_sleep_2.png");

    CgaGod::PIC_0 = new QPixmap(":/images/students/stu_cga_0.png");
    CgaGod::PIC_1 = new QPixmap(":/images/students/stu_cga_1.png");
    CgaGod::PIC_2 = new QPixmap(":/images/students/stu_cga_2.png");

    GbusStudent::PIC_0 = new QPixmap(":/images/students/stu_gbus_0.png");
    GbusStudent::PIC_1 = new QPixmap(":/images/students/stu_gbus_1.png");
    GbusStudent::PIC_2 = new QPixmap(":/images/students/stu_gbus_2.png");

    ShamelessStudent::PIC_0 = new QPixmap(":/images/students/stu_shameless_0.png");

    TeachersPet::PIC_0 = new QPixmap(":/images/students/stu_pet_0.png");

    DeadlineFighter::PIC_0 = new QPixmap(":/images/students/stu_deadline_0.png");
    DeadlineFighter::PIC_1 = new QPixmap(":/images/students/stu_deadline_1.png");
    DeadlineFighter::PIC_2 = new QPixmap(":/images/students/stu_deadline_2.png");
    DeadlineFighter::PIC_3 = new QPixmap(":/images/students/stu_deadline_3.png");
    DeadlineFighter::PIC_4 = new QPixmap(":/images/students/stu_deadline_4.png");
    DeadlineFighter::PIC_5 = new QPixmap(":/images/students/stu_deadline_5.png");

    OverworkedTA::PIC_0 = new QPixmap(":/images/teachers/tea_overworked_ta_0.png");
    OverworkedTA::PIC_1 = new QPixmap(":/images/teachers/tea_overworked_ta_1.png");

    Pang::PIC_0 = new QPixmap(":/images/teachers/tea_pang_0.png");
    Pang::PIC_1 = new QPixmap(":/images/teachers/tea_pang_1.png");

    Kelvin::PIC_0 = new QPixmap(":/images/teachers/tea_kelvin_0.png");
    Kelvin::PIC_1 = new QPixmap(":/images/teachers/tea_kelvin_1.png");

    Desmond::PIC_0 = new QPixmap(":/images/teachers/tea_desmond_0.png");
    Desmond::PIC_1 = new QPixmap(":/images/teachers/tea_desmond_1.png");

    game->start();
    game->getRowAt(0)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 0);
    game->getRowAt(0)->addStudent(TimeVariant::Type::DEADLINE_FIGHTER, 1);
    game->getRowAt(0)->addStudent(TimeVariant::Type::SHAMELESS_STUDENT, 2);
    game->getRowAt(0)->addStudent(TimeVariant::Type::TEACHERS_PET, 3);

    game->getRowAt(1)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 0);
    game->getRowAt(1)->addStudent(TimeVariant::Type::DEADLINE_FIGHTER, 1);
    game->getRowAt(1)->addStudent(TimeVariant::Type::SHAMELESS_STUDENT, 2);
    game->getRowAt(1)->addStudent(TimeVariant::Type::TEACHERS_PET, 3);

    game->getRowAt(2)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 0);
    game->getRowAt(2)->addStudent(TimeVariant::Type::DEADLINE_FIGHTER, 1);
    game->getRowAt(2)->addStudent(TimeVariant::Type::SHAMELESS_STUDENT, 2);
    game->getRowAt(2)->addStudent(TimeVariant::Type::TEACHERS_PET, 3);

    game->getRowAt(3)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 0);
    game->getRowAt(3)->addStudent(TimeVariant::Type::DEADLINE_FIGHTER, 1);
    game->getRowAt(3)->addStudent(TimeVariant::Type::SHAMELESS_STUDENT, 2);
    game->getRowAt(3)->addStudent(TimeVariant::Type::TEACHERS_PET, 3);

    game->getRowAt(4)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 0);
    game->getRowAt(4)->addStudent(TimeVariant::Type::DEADLINE_FIGHTER, 1);
    game->getRowAt(4)->addStudent(TimeVariant::Type::SHAMELESS_STUDENT, 2);
    game->getRowAt(4)->addStudent(TimeVariant::Type::TEACHERS_PET, 3);

    QWidget* spriteWidget = new QWidget(this);
    spriteWidget->setGeometry(1120, 20, 150, 660);
    spriteWidget->setStyleSheet("color: rgb(161, 112, 56);");
    spriteWidget->setLayout(new QVBoxLayout(this));

    SpriteCard* card1 = new SpriteCard(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, this);
    SpriteCard* card2 = new SpriteCard(TimeVariant::Type::CGA_GOD, this);
    spriteWidget->layout()->addWidget(card1);
    spriteWidget->layout()->addWidget(card2);

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
    delete SleepDeprivedStudent::PIC_0;
    delete SleepDeprivedStudent::PIC_1;
    delete SleepDeprivedStudent::PIC_2;

    delete CgaGod::PIC_0;
    delete CgaGod::PIC_1;
    delete CgaGod::PIC_2;

    delete GbusStudent::PIC_0;
    delete GbusStudent::PIC_1;
    delete GbusStudent::PIC_2;

    delete ShamelessStudent::PIC_0;

    delete TeachersPet::PIC_0;

    delete DeadlineFighter::PIC_0;
    delete DeadlineFighter::PIC_1;
    delete DeadlineFighter::PIC_2;
    delete DeadlineFighter::PIC_3;
    delete DeadlineFighter::PIC_4;
    delete DeadlineFighter::PIC_5;

    delete OverworkedTA::PIC_0;
    delete OverworkedTA::PIC_1;

    delete Pang::PIC_0;
    delete Pang::PIC_1;

    delete Kelvin::PIC_0;
    delete Kelvin::PIC_1;

    delete Desmond::PIC_0;
    delete Desmond::PIC_1;

    //nullptr
    SleepDeprivedStudent::PIC_0 = nullptr;
    SleepDeprivedStudent::PIC_1 = nullptr;
    SleepDeprivedStudent::PIC_2 = nullptr;

    CgaGod::PIC_0 = nullptr;
    CgaGod::PIC_1 = nullptr;
    CgaGod::PIC_2 = nullptr;

    GbusStudent::PIC_0 = nullptr;
    GbusStudent::PIC_1 = nullptr;
    GbusStudent::PIC_2 = nullptr;

    ShamelessStudent::PIC_0 = nullptr;

    TeachersPet::PIC_0 = nullptr;

    DeadlineFighter::PIC_0 = nullptr;
    DeadlineFighter::PIC_1 = nullptr;
    DeadlineFighter::PIC_2 = nullptr;
    DeadlineFighter::PIC_3 = nullptr;
    DeadlineFighter::PIC_4 = nullptr;
    DeadlineFighter::PIC_5 = nullptr;

    OverworkedTA::PIC_0 = nullptr;
    OverworkedTA::PIC_1 = nullptr;

    Pang::PIC_0 = nullptr;
    Pang::PIC_1 = nullptr;

    Kelvin::PIC_0 = nullptr;
    Kelvin::PIC_1 = nullptr;

    Desmond::PIC_0 = nullptr;
    Desmond::PIC_1 = nullptr;

    delete ui;
}
