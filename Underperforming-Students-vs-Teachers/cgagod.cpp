#include "cgagod.h"
#include "row.h"

//initialize the default name
const QString CgaGod::DEFAULT_NAME = "CGA God";

// initialize the default pics
// they will be initialized after QApplication is initialized
// i.e. in the constructor of GameWindow
QPixmap* CgaGod::PIC_0 = nullptr;
QPixmap* CgaGod::PIC_1 = nullptr;
QPixmap* CgaGod::PIC_2 = nullptr;

//constructor
CgaGod::CgaGod(QLabel* widget, Row* row, QString name, int maxHp, int skillSpeed, int cost, int damage)
    : AttackStudent(widget, row, name, maxHp, skillSpeed, cost, damage)
{

}

//return the type of CGA_GOD
TimeVariant::Type CgaGod::getType() const {return TimeVariant::Type::CGA_GOD;}

//it is called per BASIC_GAME_UNIT
void CgaGod::update()
{
    // if there is a teacher approaching
    if(row->getLeftMostTeacher())
    {
        //if time passes half of skillSpeed
        if(timeConcept == skillSpeed / 2)
        {
            widget->setPixmap(*PIC_1); //prepare to attack
        }
        else if(timeConcept == skillSpeed) //the time for attack
        {
            widget->setPixmap(*PIC_2); //set it to the attack pose
            row->addAssignment(this, damage, *Assignment::PIC_2); // create an assignment with addAssignment()
                                                                  // addAssignment() will instantiate assignment and prepare everything
            player->play(); //play shoot.mp3 that's preset in constructor of AttackStudent
            timeConcept = 0; //reset timeConcept to 0
        }
        timeConcept += Game::BASIC_TIME_UNIT; //it counts the time itself when listening to the clock
    }
    else //if no teacher is approaching
    {
        //all variables remain default
        timeConcept = 0;
        widget->setPixmap(*PIC_0);
    }

}
