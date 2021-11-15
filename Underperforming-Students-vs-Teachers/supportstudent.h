#ifndef SUPPORTSTUDENT_H
#define SUPPORTSTUDENT_H

#include "student.h"

class SupportStudent : public Student
{
    Q_OBJECT

public:
    TimeVariant::Category getCategory() const;

protected:
    SupportStudent(QLabel* widget, QString name, int maxHp, double skillSpeed, int cost);
};

#endif // SUPPORTSTUDENT_H
