#include "deadlinefighter.h"
#include "row.h"
#include <QDebug>

const QString DeadlineFighter::DEFAULT_NAME = "Deadline Fighter";

QPixmap* DeadlineFighter::PIC_0 = nullptr;
QPixmap* DeadlineFighter::PIC_1 = nullptr;
QPixmap* DeadlineFighter::PIC_2 = nullptr;
QPixmap* DeadlineFighter::PIC_3 = nullptr;
QPixmap* DeadlineFighter::PIC_4 = nullptr;
QPixmap* DeadlineFighter::PIC_5 = nullptr;


DeadlineFighter::DeadlineFighter(QLabel* widget, Row* row, QString name, int maxHp, int normalSkillSpeed, int triggeredSkillSpeed,
                                 int cost, int damage, int triggerSkillDistance)
    : AttackStudent(widget, row, name, maxHp, normalSkillSpeed, cost, damage),
      normalSkillSpeed(normalSkillSpeed), triggeredSkillSpeed(triggeredSkillSpeed), triggerSkillDistance(triggerSkillDistance)
{

}

TimeVariant::Type DeadlineFighter::getType() const {return TimeVariant::Type::DEADLINE_FIGHTER;}

void DeadlineFighter::update()
{
    Teacher* leftMostTeacher = row->getLeftMostTeacher();

    if(leftMostTeacher)
    {
        /***
        * since it would be triggered at any time
        * it is not guaranteed that timeConcept will be restored. However, it needs to be.
        * It is the reason for this code to exist
        */
        //previous state is different from the current state
        if(isTriggered ^ (leftMostTeacher->getDistanceFromLeft() - getDistanceFromLeft() <= triggerSkillDistance))
        {
            isTriggered = !isTriggered;
            timeConcept = 0;
        }

        if(isTriggered)
        {
            skillSpeed = triggeredSkillSpeed;
            //widget->setPixmap(QPixmap(":/images/students/stu_deadline_3.png"));

            if(timeConcept == skillSpeed / 2)
            {
                widget->setPixmap(*PIC_4);
            }
            else if(timeConcept == skillSpeed)
            {
                widget->setPixmap(*PIC_5);
                row->addAssignment(this, damage);
                timeConcept = 0;
            }
        }
        else
        {
            skillSpeed = normalSkillSpeed;
            if(timeConcept == skillSpeed / 2)
            {
                widget->setPixmap(*PIC_1);
            }
            else if(timeConcept == skillSpeed)
            {
                widget->setPixmap(*PIC_2);
                row->addAssignment(this, damage);
                timeConcept = 0;
            }
        }

        timeConcept += Game::BASIC_TIME_UNIT;
    }
    else
    {
        timeConcept = 0;
        widget->setPixmap(*PIC_0);
        isTriggered = false;
        skillSpeed = normalSkillSpeed;
    }
}
