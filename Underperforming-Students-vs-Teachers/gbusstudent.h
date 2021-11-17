#ifndef GBUSSTUDENT_H
#define GBUSSTUDENT_H

#include "supportstudent.h"

class GbusStudent : public SupportStudent
{
    Q_OBJECT

public:
    static const QString DEFAULT_NAME;
    static const int DEFAULT_MAX_HP{10};
    static constexpr double DEFAULT_SKILL_SPEED{10.0}; //compiler said it should be constexpr for static double
    static const int DEFAULT_COST{10};

    GbusStudent(QLabel* widget, Row* row,
                     QString name = DEFAULT_NAME,
                     int maxHp = DEFAULT_MAX_HP,
                     double skillSpeed = DEFAULT_SKILL_SPEED,
                     int cost = DEFAULT_COST);

    TimeVariant::Type getType() const;

    //the implementation of the pure virtual update()
    void update();
};

#endif // GBUSSTUDENT_H
