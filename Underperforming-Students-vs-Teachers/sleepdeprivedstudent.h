/***
* This is a class of Attack Student
* It can be instantiated
*/
#ifndef SLEEPDEPRIVEDSTUDENT_H
#define SLEEPDEPRIVEDSTUDENT_H

#include "attackstudent.h"
#include <QPixmap>

class SleepDeprivedStudent : public AttackStudent
{
    Q_OBJECT

public:
    static const QString DEFAULT_NAME;
    static const int DEFAULT_MAX_HP{500};
    static const int DEFAULT_SKILL_SPEED{2000};
    static const int DEFAULT_COST{10};
    static const int DEFAULT_DAMAGE{10};
    static QPixmap* PIC_0;
    static QPixmap* PIC_1;
    static QPixmap* PIC_2;

    SleepDeprivedStudent(QLabel* widget, Row* row,
                         QString name = DEFAULT_NAME,
                         int maxHp = DEFAULT_MAX_HP,
                         int skillSpeed = DEFAULT_SKILL_SPEED,
                         int cost = DEFAULT_COST,
                         int damage = DEFAULT_DAMAGE);

    TimeVariant::Type getType() const;

    //the implementation of the pure virtual update()
    void update();

};

#endif // SLEEPDEPRIVEDSTUDENT_H
