#include "student.h"

Student::Student(QLabel* widget, QString name, int maxHp, double skillSpeed, int cost) : Human(widget, name, maxHp)
  ,skillSpeed(skillSpeed), cost(cost)
{

}

//getter and setter for skillSpeed
double Student::getSkillSpeed() const {return skillSpeed;}
void Student::setSkillSpeed(double skillSpeed) {this->skillSpeed = skillSpeed;}

//getter and setter for skillSpeed
int Student::getCost() const {return cost;}
void Student::setCost(int cost) {this->cost = cost;}
