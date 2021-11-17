#ifndef OVERWORKEDTA_H
#define OVERWORKEDTA_H

#include "teacher.h"

/***
    Author: Tse Wai Chung
    Date: 11/13/2021
*/

class OverworkedTA : public Teacher
{
    Q_OBJECT

public:
    static const QString DEFAULT_NAME;
    static const int DEFAULT_MAX_HP{10};
    constexpr static const double DEFAULT_SPEED{10.0};
    static const int DEFAULT_DAMAGE{10};

    explicit OverworkedTA(QLabel *widget, Row* row,
                          QString name = DEFAULT_NAME, int maxHp = DEFAULT_MAX_HP,
                          double speed = DEFAULT_SPEED, int damage = DEFAULT_DAMAGE);

    TimeVariant::Type getType() const;

    void update(); // implementation of the virtual function update()
};

#endif // OVERWORKEDTA_H
