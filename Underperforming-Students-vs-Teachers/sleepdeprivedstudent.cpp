#include "sleepdeprivedstudent.h"
#include "game.h"
#include <QDebug>
#include <QThread>

const QString SleepDeprivedStudent::DEFAULT_NAME = "Sleep Deprived Student";

SleepDeprivedStudent::SleepDeprivedStudent(QLabel* widget, Row* row, QString name, int maxHp, int skillSpeed, int cost, int damage)
    : AttackStudent(widget, row, name, maxHp, skillSpeed, cost, damage)
{
}

TimeVariant::Type SleepDeprivedStudent::getType() const {return TimeVariant::Type::SLEEP_DEPRIVED_STUDENT;}

void SleepDeprivedStudent::update()
{
    //there is at least one teacher approaching
    //if(row->getLeftMostTeacher())
    if(true)
    {
        if(timeConcept == skillSpeed / 2)
        {
            widget->setPixmap(QPixmap(":/images/students/stu_sleep_1.png"));
        }
        else if(timeConcept == skillSpeed)
        {
            widget->setPixmap(QPixmap(":/images/students/stu_sleep_2.png"));

            Game* game = Game::getInstance();

            QLabel* label = new QLabel(game->getParent());
            label->setScaledContents(true);
            label->setFixedSize(Assignment::spriteWidth, Assignment::spriteWidth);
            label->setPixmap(QPixmap(":/images/items/item_assignment_0.png"));
            label->setGeometry(widget->x() + widget->width(), widget->y() + 0.5*widget->height(),
                               spriteWidth,spriteHeight);
            label->setVisible(true);

            Assignment* s = new Assignment(label, nullptr, damage);
            game->registerTimeVariant(s);
            timeConcept = 0;
        }
        timeConcept += Game::BASIC_TIME_UNIT;
    }
    else
    {
        timeConcept = 0;
    }
}
