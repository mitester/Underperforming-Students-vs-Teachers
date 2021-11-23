#ifndef SUPPORTSTUDENT_H
#define SUPPORTSTUDENT_H

#include "student.h"

class SupportStudent : public Student
{
    Q_OBJECT

public:
    TimeVariant::Category getCategory() const;

protected:
    SupportStudent(QLabel* widget, Row* row, QString name, int maxHp, int skillSpeed, int cost);
};

#endif // SUPPORTSTUDENT_H
