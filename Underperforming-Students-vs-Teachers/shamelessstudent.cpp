#include "shamelessstudent.h"

const QString ShamelessStudent::DEFAULT_NAME = "Shameless Student";

ShamelessStudent::ShamelessStudent(QWidget* widget, QString name, int maxHp, double skillSpeed, int cost)
    : SupportStudent(widget, name, maxHp, skillSpeed, cost)
{

}

//the implementation of the pure virtual skill()
void ShamelessStudent::skill() {}

//the implementation of the pure virtual update()
void ShamelessStudent::update() {}
