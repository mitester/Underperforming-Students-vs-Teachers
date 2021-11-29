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
#include "vendingmachine.h"

#include "spritecard.h"
#include <QString>
#include <QDebug>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QThread>
#include <QWidget>
#include <QVBoxLayout>
#include <QTime>
#include <qmath.h>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setWindowTitle(Game::GAME_NAME);

    Game::REDBULL_POS = ui->lb_redbull_pic->mapToGlobal(QPoint(0,0));

    setFixedSize(windowWidth, windowHeight);

    // ======== All pictures are preloaded for efficiency improvement ========

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
    OverworkedTA::PIC_2 = new QPixmap(":/images/teachers/tea_overworked_ta_2.png");
    OverworkedTA::PIC_3 = new QPixmap(":/images/teachers/tea_overworked_ta_3.png");

    Pang::PIC_0 = new QPixmap(":/images/teachers/tea_pang_0.png");
    Pang::PIC_1 = new QPixmap(":/images/teachers/tea_pang_1.png");
    Pang::PIC_2 = new QPixmap(":/images/teachers/tea_pang_2.png");
    Pang::PIC_3 = new QPixmap(":/images/teachers/tea_pang_3.png");

    Kelvin::PIC_0 = new QPixmap(":/images/teachers/tea_kelvin_0.png");
    Kelvin::PIC_1 = new QPixmap(":/images/teachers/tea_kelvin_1.png");
    Kelvin::PIC_2 = new QPixmap(":/images/teachers/tea_kelvin_2.png");
    Kelvin::PIC_3 = new QPixmap(":/images/teachers/tea_kelvin_3.png");


    Desmond::PIC_0 = new QPixmap(":/images/teachers/tea_desmond_0.png");
    Desmond::PIC_1 = new QPixmap(":/images/teachers/tea_desmond_1.png");
    Desmond::PIC_2 = new QPixmap(":/images/teachers/tea_desmond_2.png");
    Desmond::PIC_3 = new QPixmap(":/images/teachers/tea_desmond_3.png");

    Item::EXPLOSION_0 = new QPixmap(":/images/items/item_explosion_0.png");
    Item::EXPLOSION_1 = new QPixmap(":/images/items/item_explosion_1.png");
    Item::EXPLOSION_2 = new QPixmap(":/images/items/item_explosion_2.png");


    Assignment::PIC_0 = new QPixmap(":/images/items/item_assignment_0.png");
    Assignment::PIC_1 = new QPixmap(":/images/items/item_assignment_1.png");
    Assignment::PIC_2 = new QPixmap(":/images/items/item_assignment_2.png");


    Redbull::PIC_0 = new QPixmap(":/images/items/item_redbull_0.png");

    VendingMachine::PIC_0 = new QPixmap(":/images/items/item_vending_0.png");

    Game::GAME_SCENE_FAIL = new QPixmap(":/images/scene/game_scene_fail.png");
    Game::GAME_SCENE_PASS = new QPixmap(":/images/scene/game_scene_pass.png");

    this->game = Game::getInstance(this); //get the Singleton Game object

    ui->lb_redbull_num->setText(QString::number(game->getRedbullNum()));
    ui->widget_right->raise();

    connect(game, &Game::notifyAddRedbull, this,
            [=]()
            {
                ui->lb_redbull_num->setText(QString::number(game->getRedbullNum()));
            });

    connect(game->getMainTimer(), &QTimer::timeout,
            this,
            [=]()
            {
                ui->lb_time_count->setText(game->getCurrentTimeLeft());
                ui->widget_right->raise();
            });

    connect(ui->lb_pause, &ClickableLabel::clicked, this,
            [=]()
            {
               if(!ui->lb_pause->text().compare("Pause", Qt::CaseInsensitive))
               {
                   game->pause();
                   ui->lb_pause->setText("Start");
               }
               else
               {
                   game->start();
                   ui->lb_pause->setText("Pause");
               }
            });

    connect(ui->lb_home, &ClickableLabel::clicked, this,
            [=]()
    {
        parentWidget()->show();
        deleteLater();
    });

//    game->getRowAt(0)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 0);
//    game->getRowAt(0)->addStudent(TimeVariant::Type::DEADLINE_FIGHTER, 1);
//    game->getRowAt(0)->addStudent(TimeVariant::Type::SHAMELESS_STUDENT, 2);
//    game->getRowAt(0)->addStudent(TimeVariant::Type::TEACHERS_PET, 3);

//    game->getRowAt(1)->addStudent(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, 0);
//    game->getRowAt(1)->addStudent(TimeVariant::Type::DEADLINE_FIGHTER, 1);
//    game->getRowAt(1)->addStudent(TimeVariant::Type::SHAMELESS_STUDENT, 2);
//    game->getRowAt(1)->addStudent(TimeVariant::Type::TEACHERS_PET, 3);

//    game->getRowAt(2)->addStudent(TimeVariant::Type::CGA_GOD, 0);
//    game->getRowAt(2)->addStudent(TimeVariant::Type::CGA_GOD, 1);
//    game->getRowAt(2)->addStudent(TimeVariant::Type::SHAMELESS_STUDENT, 2);
//    game->getRowAt(2)->addStudent(TimeVariant::Type::TEACHERS_PET, 3);

//    game->getRowAt(3)->addStudent(TimeVariant::Type::DEADLINE_FIGHTER, 0);
//    game->getRowAt(3)->addStudent(TimeVariant::Type::DEADLINE_FIGHTER, 1);
//    game->getRowAt(3)->addStudent(TimeVariant::Type::SHAMELESS_STUDENT, 2);
//    game->getRowAt(3)->addStudent(TimeVariant::Type::TEACHERS_PET, 3);

//    game->getRowAt(4)->addStudent(TimeVariant::Type::GBUS_STUDENT, 0);
//    game->getRowAt(4)->addStudent(TimeVariant::Type::CGA_GOD, 1);
//    game->getRowAt(4)->addStudent(TimeVariant::Type::DEADLINE_FIGHTER, 2);
//    game->getRowAt(4)->addStudent(TimeVariant::Type::SHAMELESS_STUDENT, 3);
//    game->getRowAt(4)->addStudent(TimeVariant::Type::TEACHERS_PET, 4);


    QLabel* label = new QLabel(this);
    label->setPixmap(*VendingMachine::PIC_0);
    label->setFixedSize(VendingMachine::SPRITE_WIDTH, VendingMachine::SPRITE_HEIGHT);
    label->move(140, height() - label->height() - 40);
    VendingMachine* v = new VendingMachine(label);
    game->registerTimeVariant(v);

    //Creating the sprite selection board
    SpriteCard* card1 = new SpriteCard(TimeVariant::Type::SLEEP_DEPRIVED_STUDENT, this);
    SpriteCard* card2 = new SpriteCard(TimeVariant::Type::GBUS_STUDENT, this);
    SpriteCard* card3 = new SpriteCard(TimeVariant::Type::DEADLINE_FIGHTER, this);
    SpriteCard* card4 = new SpriteCard(TimeVariant::Type::SHAMELESS_STUDENT, this);
    SpriteCard* card5 = new SpriteCard(TimeVariant::Type::TEACHERS_PET, this);
    SpriteCard* card6 = new SpriteCard(TimeVariant::Type::CGA_GOD, this);
    SpriteCard* card7 = new SpriteCard(TimeVariant::Type::EMPTY, this);
    ui->gridLayout->addWidget(card1,0,0);
    ui->gridLayout->addWidget(card2,1,0);
    ui->gridLayout->addWidget(card3,2,0);
    ui->gridLayout->addWidget(card4,3,0);
    ui->gridLayout->addWidget(card5,0,1);
    ui->gridLayout->addWidget(card6,1,1);
    ui->gridLayout->addWidget(card7,2,1);


    //ATTENTION
    //starts the game after everything is ready
    //so it must be the last line
    game->start();

    QLabel* transparentSprite = new QLabel(this);
    transparentSprite->setFixedSize(Student::SPRITE_WIDTH,Student::SPRITE_HEIGHT);
    transparentSprite->setScaledContents(true);
    transparentSprite->hide();
    game->transLabel = transparentSprite;

    setMouseTracking(true);
    ui->centralwidget->setMouseTracking(true);
}

void GameWindow::resizeEvent(QResizeEvent *ev) {
    QMainWindow::resizeEvent(ev);
    this->game->currentSize = ev->size();

}

void GameWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(this->rect(), QPixmap(":/images/scene/game_scene.png"));
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
    delete OverworkedTA::PIC_2;
    delete OverworkedTA::PIC_3;

    delete Pang::PIC_0;
    delete Pang::PIC_1;
    delete Pang::PIC_2;
    delete Pang::PIC_3;

    delete Kelvin::PIC_0;
    delete Kelvin::PIC_1;
    delete Kelvin::PIC_2;
    delete Kelvin::PIC_3;

    delete Desmond::PIC_0;
    delete Desmond::PIC_1;
    delete Desmond::PIC_2;
    delete Desmond::PIC_3;

    delete Item::EXPLOSION_0;
    delete Item::EXPLOSION_1;
    delete Item::EXPLOSION_2;


    delete Assignment::PIC_0;
    delete Assignment::PIC_1;
    delete Assignment::PIC_2;


    delete Redbull::PIC_0;

    delete VendingMachine::PIC_0;

    delete Game::GAME_SCENE_FAIL;
    delete Game::GAME_SCENE_PASS;

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
    OverworkedTA::PIC_2 = nullptr;
    OverworkedTA::PIC_3 = nullptr;

    Pang::PIC_0 = nullptr;
    Pang::PIC_1 = nullptr;
    Pang::PIC_2 = nullptr;
    Pang::PIC_3 = nullptr;

    Kelvin::PIC_0 = nullptr;
    Kelvin::PIC_1 = nullptr;
    Kelvin::PIC_2 = nullptr;
    Kelvin::PIC_3 = nullptr;

    Desmond::PIC_0 = nullptr;
    Desmond::PIC_1 = nullptr;
    Desmond::PIC_2 = nullptr;
    Desmond::PIC_3 = nullptr;

    Item::EXPLOSION_0 = nullptr;
    Item::EXPLOSION_1 = nullptr;
    Item::EXPLOSION_2 = nullptr;


    Assignment::PIC_0 = nullptr;
    Assignment::PIC_1 = nullptr;
    Assignment::PIC_2 = nullptr;

    Redbull::PIC_0 = nullptr;

    VendingMachine::PIC_0 = nullptr;

    Game::GAME_SCENE_FAIL = nullptr;
    Game::GAME_SCENE_PASS = nullptr;

    delete ui;
}

QPoint GameWindow::getClosestGridPos(QPoint p) {
    Game* game = Game::getInstance();
    // Finding the closest row that matches the YPosition of the clicking
    int minYIdx = 0;
    for(int i = 0; i < Game::NUMBER_OF_ROW; i++)    //compare the y position to every row's yPos
        if(abs(game->getRowAt(i)->getYPos() + (Game::GRID_INTERVAL_VERTICAL) - p.y())
         < abs(game->getRowAt(minYIdx)->getYPos() + (Game::GRID_INTERVAL_VERTICAL) - p.y()))
            minYIdx = i;
    Row* row = game->getRowAt(minYIdx);

    // Finding the closest tile in the row that matches the XPosition of the clicking
    int minXPos = Game::GRID_LEFT;
    int minXIdx = 0;
    for(int i = 0; i < Game::NUMBER_OF_COLUMN; i++) {
        int xPos = Game::GRID_LEFT + (Game::GRID_INTERVAL_HORIZONTAL/2) + i * Game::GRID_INTERVAL_HORIZONTAL;
        if(abs(xPos - p.x()) < abs(minXPos - p.x())) {
            minXPos = xPos;
            minXIdx = i;
        }
    }

    return QPoint(minXIdx, minYIdx);
}

void GameWindow::mousePressEvent(QMouseEvent *ev) { // rewrite the mousePressEvent. Mostly for sprite card placement
    QPoint p = ev->pos();
    Game* game = Game::getInstance();

    if(p.x() > Game::GRID_LEFT && p.x() < Game::GRID_RIGHT &&
       p.y() > Game::GRID_UP && p.y() < Game::GRID_DOWN &&
       game->selectedCard != nullptr) { //only when the click is within the grid area, we do further judgement

        // Finding the closest row that matches the YPosition of the clicking

        QPoint gridPos = getClosestGridPos(p);
        int minYIdx = gridPos.y();
        int minXIdx = gridPos.x();
        Row* row = game->getRowAt(minYIdx);
        int minXPos = Game::GRID_LEFT + (Game::GRID_INTERVAL_HORIZONTAL/2) + minXIdx * Game::GRID_INTERVAL_HORIZONTAL;

        // If the selected type is Empty, but there is card selected (implies expel)
        if(game->selectedSprite == TimeVariant::Type::EMPTY) {
            if(row->hasStudentAt(minXIdx))
                row->removeStudent(minXIdx);
            return;
        }

        int cost = game->getCost(game->selectedSprite);

        if(game->getRedbullNum() >= cost && !row->hasStudentAt(minXIdx)) {  // check if cost is enough & hasStudent

            if(row->getLeftMostTeacher()) // not allowed to put student to the right of teachers
                if(row->getLeftMostTeacher()->getDistanceFromLeft() < minXPos)
                    return;

            game->addRedbull(-cost); // reduce redbull
            row->addStudent(game->selectedSprite, minXIdx); // add the student to corresponding row
        }

        if(game->getRedbullNum() < game->getCost(game->selectedSprite)) {
            emit game->selectedCard->clicked();
        }
    }
    else
    {
        QMainWindow::mousePressEvent(ev);
    }
}

void GameWindow::mouseMoveEvent(QMouseEvent *ev) {
    QPoint p = ev->pos();
    Game* game = Game::getInstance();
    if(p.x() > Game::GRID_LEFT && p.x() < Game::GRID_RIGHT &&
       p.y() > Game::GRID_UP && p.y() < Game::GRID_DOWN && game->selectedSprite != TimeVariant::Type::EMPTY) {
        QPoint pos = getClosestGridPos(p);
        int xPos = pos.x() * Game::GRID_INTERVAL_HORIZONTAL + Game::GRID_LEFT;
        int yPos = pos.y() * Game::GRID_INTERVAL_VERTICAL + Game::GRID_UP;
        game->transLabel->move(xPos, yPos);
        game->transLabel->show();
    } else {
        game->transLabel->hide();
        QMainWindow::mouseMoveEvent(ev);
    }
}
