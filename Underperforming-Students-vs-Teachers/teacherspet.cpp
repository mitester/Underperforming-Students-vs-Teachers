#include "teacherspet.h"

const QString TeachersPet::DEFAULT_NAME = "Teachers' Pet";
QPixmap* TeachersPet::PIC_0 = nullptr;

TeachersPet::TeachersPet(QLabel* widget, Row* row, QString name, int maxHp, int skillSpeed, int cost)
    : SupportStudent(widget, row, name, maxHp, skillSpeed, cost)
{

}

TimeVariant::Type TeachersPet::getType() const {return TimeVariant::Type::TEACHERS_PET;}

//the implementation of the pure virtual update()
void TeachersPet::update() {}
