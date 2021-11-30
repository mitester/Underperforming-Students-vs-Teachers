/***
 * the class of GbusStudent
 * inherits from SupportStudent
 */
#ifndef GBUSSTUDENT_H
#define GBUSSTUDENT_H

#include "supportstudent.h"

class GbusStudent : public SupportStudent
{
    Q_OBJECT

public:
    //some constants defined the GbusStudent
    static const QString DEFAULT_NAME;
    static const int DEFAULT_MAX_HP{500};
    static const int DEFAULT_SKILL_SPEED{5000};
    static const int DEFAULT_COST{10};

    //pictures
    static QPixmap* PIC_0;
    static QPixmap* PIC_1;
    static QPixmap* PIC_2;

    //constructor
    GbusStudent(QLabel* widget, Row* row,
                     QString name = DEFAULT_NAME,
                     int maxHp = DEFAULT_MAX_HP,
                     int skillSpeed = DEFAULT_SKILL_SPEED,
                     int cost = DEFAULT_COST);

    TimeVariant::Type getType() const;

    //the implementation of the pure virtual update()
    void update();
};

#endif // GBUSSTUDENT_H
