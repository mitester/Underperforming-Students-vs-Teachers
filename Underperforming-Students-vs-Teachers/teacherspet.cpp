#include "teacherspet.h"

const QString TeachersPet::DEFAULT_NAME = "Teachers' Pet";

TeachersPet::TeachersPet(QWidget* widget, QString name, int maxHp, double skillSpeed, int cost)
    : SupportStudent(widget, name, maxHp, skillSpeed, cost)
{

}

//the implementation of the pure virtual skill()
void TeachersPet::skill() {}

//the implementation of the pure virtual update()
void TeachersPet::update() {}
