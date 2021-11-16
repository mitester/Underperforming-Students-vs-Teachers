#include "overworkedta.h"

const QString OverworkedTA::DEFAULT_NAME = "Overworked TA";

OverworkedTA::OverworkedTA(QLabel *widget, QString name, int maxHp, double speed, int damage) :
    Teacher(widget, name, maxHp, speed, damage)
{

}

TimeVariant::Type OverworkedTA::getType() const {return TimeVariant::Type::OVERWORKED_TA;}

void OverworkedTA::update() {

}


