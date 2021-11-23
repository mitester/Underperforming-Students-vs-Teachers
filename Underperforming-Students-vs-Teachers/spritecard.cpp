#include "spritecard.h"
#include "timevariant.h"
#include "clickablelabel.h"
#include "game.h"
#include "human.h"
#include "sleepdeprivedstudent.h"
#include "student.h"

SpriteCard::SpriteCard(TimeVariant::Type type, QWidget* parent, Qt::WindowFlags f):ClickableLabel(parent, f), type(type)
{
    this->setGeometry(0,0,Student::SPRITE_HEIGHT,Student::SPRITE_WIDTH);
    switch (type) {
        case TimeVariant::Type::SLEEP_DEPRIVED_STUDENT:
            setPixmap(*SleepDeprivedStudent::PIC_0);
    }
    this->setStyleSheet("color: white;");
}

void SpriteCard::mousePressEvent(QMouseEvent *event) {
    if(selected) {
        selected = false;
        Game::selectedSprite = TimeVariant::Type::REDBULL;
        this->setStyleSheet("color: white;");
    } else {
        selected = true;
        Game::selectedSprite = type;
        this->setStyleSheet("color: white; border: 3px solid yellow;");
    }
}
