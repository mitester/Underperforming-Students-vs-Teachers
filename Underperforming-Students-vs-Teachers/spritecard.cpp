#include "spritecard.h"
#include "timevariant.h"
#include "clickablelabel.h"
#include "game.h"
#include "human.h"
#include "sleepdeprivedstudent.h"
#include "student.h"
#include <QDebug>

SpriteCard::SpriteCard(TimeVariant::Type type, QWidget* parent, Qt::WindowFlags f):ClickableLabel(parent, f), type(type)
{
    this->setFixedSize(WIDTH, HEIGHT);
    this->setScaledContents(true);
    switch (type) {
    case TimeVariant::Type::SLEEP_DEPRIVED_STUDENT:
        setPixmap(QPixmap(":/images/cards/card_sleep_0.png"));
        break;
    case TimeVariant::Type::SHAMELESS_STUDENT:
        setPixmap(QPixmap(":/images/cards/card_shameless_0.png"));
        break;
    case TimeVariant::Type::CGA_GOD:
        setPixmap(QPixmap(":/images/cards/card_cga_0.png"));
        break;
    case TimeVariant::Type::GBUS_STUDENT:
        setPixmap(QPixmap(":/images/cards/card_gbus_0.png"));
        break;
    case TimeVariant::Type::DEADLINE_FIGHTER:
        setPixmap(QPixmap(":/images/cards/card_deadline_0.png"));
        break;
    case TimeVariant::Type::TEACHERS_PET:
        setPixmap(QPixmap(":/images/cards/card_pet_0.png"));
        break;
    case TimeVariant::Type::EMPTY:
        setPixmap(QPixmap(":/images/cards/card_remove_0.png"));
        break;
    default:
        qDebug() << "wrong type passed to SpriteCard";
    }
    this->setStyleSheet("color: white;");
    this->show();
}

void SpriteCard::mousePressEvent(QMouseEvent *event) {
    Game* game = Game::getInstance();
        if(selected) {
            selected = false;
            Game::selectedSprite = TimeVariant::Type::EMPTY;
            this->setStyleSheet("color: white;");
        } else if(game->selectedSprite == TimeVariant::Type::EMPTY) {
            selected = true;
            Game::selectedSprite = type;
            this->setStyleSheet("color: white; border: 3px solid yellow;");
        }

}
