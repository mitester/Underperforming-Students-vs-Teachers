#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent, f) {

}

ClickableLabel::~ClickableLabel() {}

//emit click() if the label is clickable
void ClickableLabel::mousePressEvent(QMouseEvent* ) {
    if(clickable)
        emit clicked();
}

//set clickable property
void ClickableLabel::setClickable(bool x)
{
    clickable = x;
}

//get clickable property
bool ClickableLabel::isClickable() const
{
    return clickable;
}
