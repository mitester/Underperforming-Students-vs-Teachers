#ifndef SUPPORTSTUDENT_H
#define SUPPORTSTUDENT_H

#include "student.h"

class SupportStudent : public Student
{
protected:
    SupportStudent(QWidget* widget, QString name, int maxHp, double skillSpeed, int cost);
};

#endif // SUPPORTSTUDENT_H
