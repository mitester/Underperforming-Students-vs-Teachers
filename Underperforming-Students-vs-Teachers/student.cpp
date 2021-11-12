#include "student.h"

Student::Student(QWidget* widget, QString name, int maxHp, double skillSpeed, int cost) : Human(widget, name, maxHp)
  ,skillSpeed(skillSpeed), cost(cost)
{

}

//getter and setter for skillSpeed
double Student::getSkillSpeed() {return skillSpeed;}
void Student::setSkillSpeed(double skillSpeed) {this->skillSpeed = skillSpeed;}

//getter and setter for skillSpeed
int Student::getCost() {return cost;}
void Student::setCost(int cost) {this->cost = cost;}
