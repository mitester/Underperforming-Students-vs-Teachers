#ifndef GBUSSTUDENT_H
#define GBUSSTUDENT_H

#include "supportstudent.h"

class GbusStudent : public SupportStudent
{
public:
    static const QString defaultName;
    static const int defaultMaxHp{10};
    static constexpr double defaultSkillSpeed{10.0}; //compiler said it should be constexpr for static double
    static const int defaultCost{10};

    GbusStudent(QWidget* widget,
                     QString name = defaultName,
                     int maxHp = defaultMaxHp,
                     double skillSpeed = defaultSkillSpeed,
                     int cost = defaultCost);

    //the implementation of the pure virtual skill()
    void skill();

    //the implementation of the pure virtual update()
    void update();
};

#endif // GBUSSTUDENT_H
