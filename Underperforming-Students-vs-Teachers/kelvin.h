#ifndef KELVIN_H
#define KELVIN_H

#include "teacher.h"

/***
    Date: 11/13/2021
    The class of Teacher Kelvin.
    It is a subclass of Teacher, which represents the Kelvin.
    All its parameters & pictures are stored as static memeber of the class.
*/

class Kelvin : public Teacher
{
    Q_OBJECT

public:
    static const QString DEFAULT_NAME;
    static const int DEFAULT_MAX_HP{300};
    static const int DEFAULT_SPEED{2};
    static const int DEFAULT_DAMAGE{2};

    static QPixmap* PIC_0;
    static QPixmap* PIC_1;
    static QPixmap* PIC_2;
    static QPixmap* PIC_3;

    Kelvin(QLabel *widget, Row* row,
           QString name = DEFAULT_NAME, int maxHp = DEFAULT_MAX_HP,
           int speed = DEFAULT_SPEED, int damage = DEFAULT_DAMAGE);

    TimeVariant::Type getType() const;
    void update();

};

#endif // KELVIN_H
