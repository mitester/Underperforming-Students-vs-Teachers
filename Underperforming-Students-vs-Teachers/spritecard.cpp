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

    connect(this, &ClickableLabel::clicked, this, &SpriteCard::on_clicked);
}

void SpriteCard::on_clicked() {
    Game* game = Game::getInstance();
    if(Game::selectedCard == nullptr) {   //if no card is currently selected
        Game::selectedSprite = type;
        Game::selectedCard = this;
        this->setStyleSheet("color: white; border: 3px solid yellow;");
    } else {
        if(Game::selectedCard == this) {   //if yourself is the card selected
            Game::selectedCard = nullptr;
            Game::selectedSprite = TimeVariant::Type::EMPTY;
            this->setStyleSheet("color: white;");
        } else {                     // if another card was previously selected
            emit Game::selectedCard->clicked();
            Game::selectedCard = this;
            Game::selectedSprite = type;
            this->setStyleSheet("color: white; border: 3px solid yellow;");
        }
    }
}
