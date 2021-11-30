/***
 * Class of ShamelessStudent
 * inherits from SupportStudent
 */
#ifndef SHAMELESSSTUDENT_H
#define SHAMELESSSTUDENT_H

#include "supportstudent.h"

class ShamelessStudent : public SupportStudent
{
    Q_OBJECT

public:
    //some constants defined the ShamelessStudent
    static const QString DEFAULT_NAME;
    static const int DEFAULT_MAX_HP{6000};
    static const int DEFAULT_SKILL_SPEED{1000};
    static const int DEFAULT_COST{20};

    static QPixmap* PIC_0;

    ShamelessStudent(QLabel* widget, Row* row,
                     QString name = DEFAULT_NAME,
                     int maxHp = DEFAULT_MAX_HP,
                     int skillSpeed = DEFAULT_SKILL_SPEED,
                     int cost = DEFAULT_COST);

    TimeVariant::Type getType() const;

    //the implementation of the pure virtual update()
    void update();
};

#endif // SHAMELESSSTUDENT_H
