#ifndef TEACHERSPET_H
#define TEACHERSPET_H

#include "supportstudent.h"

class TeachersPet : public SupportStudent
{
    Q_OBJECT

public:
    static const QString DEFAULT_NAME;
    static const int DEFAULT_MAX_HP{15};
    static const int DEFAULT_SKILL_SPEED{1000};
    static const int DEFAULT_COST{10};

    static QPixmap* PIC_0;

    TeachersPet(QLabel* widget, Row* row,
                     QString name = DEFAULT_NAME,
                     int maxHp = DEFAULT_MAX_HP,
                     int skillSpeed = DEFAULT_SKILL_SPEED,
                     int cost = DEFAULT_COST);

    TimeVariant::Type getType() const;

    //the implementation of the pure virtual update()
    void update();
};

#endif // TEACHERSPET_H
