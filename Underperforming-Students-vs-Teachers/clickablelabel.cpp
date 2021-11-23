#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent, f) {

}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent(QMouseEvent* ) {
    if(clickable)
        emit clicked();
}

void ClickableLabel::setClickable(bool x)
{
    clickable = x;
}

bool ClickableLabel::isClickable() const
{
    return clickable;
}
