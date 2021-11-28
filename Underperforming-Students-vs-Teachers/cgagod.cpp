#include "cgagod.h"
#include "row.h"

const QString CgaGod::DEFAULT_NAME = "CGA God";

QPixmap* CgaGod::PIC_0 = nullptr;
QPixmap* CgaGod::PIC_1 = nullptr;
QPixmap* CgaGod::PIC_2 = nullptr;


CgaGod::CgaGod(QLabel* widget, Row* row, QString name, int maxHp, int skillSpeed, int cost, int damage)
    : AttackStudent(widget, row, name, maxHp, skillSpeed, cost, damage)
{

}

TimeVariant::Type CgaGod::getType() const {return TimeVariant::Type::CGA_GOD;}

void CgaGod::update()
{
    if(row->getLeftMostTeacher())
    {
        if(timeConcept == skillSpeed / 2)
        {
            widget->setPixmap(*PIC_1);
        }
        else if(timeConcept == skillSpeed)
        {
            widget->setPixmap(*PIC_2);
            row->addAssignment(this, damage, *Assignment::PIC_2);
            timeConcept = 0;
        }
        timeConcept += Game::BASIC_TIME_UNIT;
    }
    else
    {
        timeConcept = 0;
        widget->setPixmap(*PIC_0);
    }

}
