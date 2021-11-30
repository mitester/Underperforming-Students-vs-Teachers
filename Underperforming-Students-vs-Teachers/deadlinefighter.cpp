#include "deadlinefighter.h"
#include "row.h"
#include <QDebug>

//initialization of name and pics
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

//return if its rage mode is triggered
bool DeadlineFighter::isTriggered() const
{
    return triggered;
}

//react to the timeout() signal per BASIC_TIME_UNIT
void DeadlineFighter::update()
{

    //if there is at least teacher approaching
    if(row->getLeftMostTeacher())
    {
        /***
        * since it would be triggered at any time
        * it is not guaranteed that timeConcept will be restored. However, it needs to be.
        * It is the reason for this code to exist
        */
        //if previous state is different from the current state
        if(triggered ^ (row->getLeftMostTeacher()->getDistanceFromLeft() - getDistanceFromLeft() <= triggerSkillDistance))
        {
            triggered = !triggered; //triggered needs to be changed

            if(triggered)
            {
                widget->setPixmap(*PIC_3); //set to triggered pics
            }
            else
            {
                widget->setPixmap(*PIC_0); //set to the normal pics

            }

            timeConcept = 0; //reset timeConcept since
        }
        if(triggered) //if it is in rage mode
        {
            skillSpeed = triggeredSkillSpeed; //change the skillspeed to the triggered skill speed

            if(timeConcept == skillSpeed / 2)
            {
                widget->setPixmap(*PIC_4); //set to rage prepare pics
            }
            else if(timeConcept == skillSpeed)
            {
                widget->setPixmap(*PIC_5); //set to rage attack pics
                row->addAssignment(this, damage, *Assignment::PIC_1); //create assignment
                player->play(); //play shoot.mp3
                timeConcept = 0; //reset it to 0
            }
        }
        else
        {
            //same as the above but just different assignment pics
            skillSpeed = normalSkillSpeed;
            if(timeConcept == skillSpeed / 2)
            {
                widget->setPixmap(*PIC_1);
            }
            else if(timeConcept == skillSpeed)
            {
                widget->setPixmap(*PIC_2);
                row->addAssignment(this, damage);
                player->play();
                timeConcept = 0;
            }
        }

        timeConcept += Game::BASIC_TIME_UNIT; //count the time
    }
    else
    {
        //restore everything to default when idle
        timeConcept = 0;
        widget->setPixmap(*PIC_0);
        triggered = false;
        skillSpeed = normalSkillSpeed;
    }
}
