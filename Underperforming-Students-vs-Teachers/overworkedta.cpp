#include "overworkedta.h"

OverworkedTA::OverworkedTA(QLabel *widget, QString name, int maxHp, double speed, int damage) :
    Teacher(widget, name, maxHp, speed, damage)
{

}

TimeVariant::Type OverworkedTA::getType() const {return TimeVariant::Type::OVERWORKED_TA;}

void OverworkedTA::update() {

}


