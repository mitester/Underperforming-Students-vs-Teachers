#include "deadlinefighter.h"
#include "row.h"
#include <QDebug>

const QString DeadlineFighter::DEFAULT_NAME = "Deadline Fighter";


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
        //distance close enough to trigger
        if(!isTriggered) //if not triggered before
        {
            //if triggered after the condition
            //implies isTriggered changed from false to true
            if((isTriggered = leftMostTeacher->getDistanceFromLeft() - getDistanceFromLeft() <= triggerSkillDistance))
            {
                timeConcept = 0;
            }
        }

        if(isTriggered)
        {
            skillSpeed = triggeredSkillSpeed;
            //widget->setPixmap(QPixmap(":/images/students/stu_deadline_3.png"));

            if(timeConcept == skillSpeed / 2)
            {
                widget->setPixmap(QPixmap(":/images/students/stu_deadline_4.png"));
            }
            else if(timeConcept == skillSpeed)
            {
                widget->setPixmap(QPixmap(":/images/students/stu_deadline_5.png"));
                row->addAssignment(this, damage);
                timeConcept = 0;
            }
        }
        else
        {
            skillSpeed = normalSkillSpeed;
            if(timeConcept == skillSpeed / 2)
            {
                widget->setPixmap(QPixmap(":/images/students/stu_deadline_1.png"));
            }
            else if(timeConcept == skillSpeed)
            {
                widget->setPixmap(QPixmap(":/images/students/stu_deadline_2.png"));
                row->addAssignment(this, damage);
                timeConcept = 0;
            }
        }

        timeConcept += Game::BASIC_TIME_UNIT;
    }
    else
    {
        timeConcept = 0;
        widget->setPixmap(QPixmap(":/images/students/stu_deadline_0.png"));
        isTriggered = false;
        skillSpeed = normalSkillSpeed;
    }
}
