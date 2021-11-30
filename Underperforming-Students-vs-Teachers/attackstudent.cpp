#include "attackstudent.h"

// constructor of AttackStudent
// every attack student is preset to play the shoot.mp3
// this media is preset in the construction of this object
// subclasses are allowed to set it to another media
// but it will complain if the same media is repeatedly set
AttackStudent::AttackStudent(QLabel* widget, Row* row, QString name, int maxHp, int skillSpeed, int cost, int damage)
    : Student (widget, row, name, maxHp, skillSpeed, cost), damage(damage)
{
    player->setMedia(QUrl("qrc:/sounds/shoot.mp3"));
}

//getter of damage
int AttackStudent::getDamage() const {return damage;}

//setter of damage
void AttackStudent::setDamage(int damage) {this->damage = damage;}

//return the category of Attack Student
TimeVariant::Category AttackStudent::getCategory() const {return TimeVariant::Category::ATTACK_STUDENT;}
