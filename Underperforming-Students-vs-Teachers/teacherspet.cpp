#include "teacherspet.h"

const QString TeachersPet::DEFAULT_NAME = "Teachers' Pet";

TeachersPet::TeachersPet(QLabel* widget, QString name, int maxHp, double skillSpeed, int cost)
    : SupportStudent(widget, name, maxHp, skillSpeed, cost)
{

}

TimeVariant::Type TeachersPet::getType() const {return TimeVariant::Type::TEACHERS_PET;}

//the implementation of the pure virtual skill()
void TeachersPet::skill() {}

//the implementation of the pure virtual update()
void TeachersPet::update() {}
