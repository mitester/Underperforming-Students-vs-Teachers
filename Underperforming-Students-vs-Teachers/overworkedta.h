#ifndef OVERWORKEDTA_H
#define OVERWORKEDTA_H

#include "teacher.h"

/***
    Author: Tse Wai Chung
    Date: 11/13/2021
*/

class OverworkedTA : public Teacher
{
public:
    static const QString DEFAULT_NAME;
    static const int DEFAULT_MAX_HP{10};
    constexpr static const double defaultSpeed{10.0};
    static const int DEFAULT_DAMAGE{10};

    explicit OverworkedTA(QWidget *widget,
                          QString name = DEFAULT_NAME, int maxHp = DEFAULT_MAX_HP,
                          double speed = defaultSpeed, int damage = DEFAULT_DAMAGE);

    void update(); // implementation of the virtual function update()
protected:
private:
};

#endif // OVERWORKEDTA_H
