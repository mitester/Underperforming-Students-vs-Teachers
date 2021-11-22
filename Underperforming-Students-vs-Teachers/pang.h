#ifndef PANG_H
#define PANG_H

#include "teacher.h"

/***
    Author: Tse Wai Chung
    Date: 11/13/2021
*/

class Pang : public Teacher
{
    Q_OBJECT

public:
    static const QString DEFAULT_NAME;
    static const int DEFAULT_MAX_HP{100};
    static const int DEFAULT_SPEED{2};
    static const int DEFAULT_DAMAGE{1};

    static QPixmap* PIC_0;
    static QPixmap* PIC_1;

    Pang(QLabel *widget, Row* row,
           QString name = DEFAULT_NAME, int maxHp = DEFAULT_MAX_HP,
           int speed = DEFAULT_SPEED, int damage = DEFAULT_DAMAGE);

    TimeVariant::Type getType() const;

};

#endif // PANG_H
