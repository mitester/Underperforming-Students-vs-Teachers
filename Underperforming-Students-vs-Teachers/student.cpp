#include "student.h"
#include "row.h"

Student::Student(QLabel* widget, Row* row, QString name, int maxHp, int skillSpeed, int cost) : Human(widget, row, name, maxHp)
  ,skillSpeed(skillSpeed), cost(cost)
{
}

//getter and setter for skillSpeed
int Student::getSkillSpeed() const {return skillSpeed;}
void Student::setSkillSpeed(int skillSpeed) {this->skillSpeed = skillSpeed;}

//getter and setter for skillSpeed
int Student::getCost() const {return cost;}
void Student::setCost(int cost) {this->cost = cost;}
