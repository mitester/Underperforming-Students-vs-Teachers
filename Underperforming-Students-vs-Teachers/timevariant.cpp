#include "timevariant.h"

TimeVariant::TimeVariant(QLabel* widget) : QObject(widget), widget(widget)
{

}

QLabel* TimeVariant::getWidget() {return widget;}

void TimeVariant::setWidget(QLabel* widget) {this->widget = widget;}

double TimeVariant::getDistanceFromLeft() const {
    return this->widget->x();
}
