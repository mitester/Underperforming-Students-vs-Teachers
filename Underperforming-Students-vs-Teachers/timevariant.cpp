#include "timevariant.h"

TimeVariant::TimeVariant(QWidget* widget) : QObject(widget), widget(widget)
{
}

QWidget* TimeVariant::getWidget() {return widget;}

void TimeVariant::setWidget(QWidget* widget) {this->widget = widget;}
