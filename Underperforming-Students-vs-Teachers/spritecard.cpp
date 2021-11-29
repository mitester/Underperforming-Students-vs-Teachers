#include "spritecard.h"
#include "timevariant.h"
#include "clickablelabel.h"
#include "game.h"
#include "gamewindow.h"
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

    costLabel = new QLabel(this);
    costLabel->setText(QString::number(Game::getCost(type)));
    costLabel->setStyleSheet("color: black; font-size: 19px; font: bold;");
    costLabel->move(COST_X, COST_Y);

    setObjectName("SpriteCard");

    connect(this, &ClickableLabel::clicked, this, &SpriteCard::on_clicked);
}

QPixmap getTransPicPath(TimeVariant::Type type) {
    switch (type) {
    case TimeVariant::Type::CGA_GOD:
        return QPixmap(":/images/students/stu_cga_trans.png");
    case TimeVariant::Type::DEADLINE_FIGHTER:
        return QPixmap(":/images/students/stu_deadline_trans.png");
    case TimeVariant::Type::GBUS_STUDENT:
        return QPixmap(":/images/students/stu_gbus_trans.png");
    case TimeVariant::Type::SHAMELESS_STUDENT:
        return QPixmap(":/images/students/stu_shameless_trans.png");
    case TimeVariant::Type::SLEEP_DEPRIVED_STUDENT:
        return QPixmap(":/images/students/stu_sleep_trans.png");
    case TimeVariant::Type::TEACHERS_PET:
        return QPixmap(":/images/students/stu_pet_trans.png");
    case TimeVariant::Type::EMPTY:
        return QPixmap();
    default:
        qDebug() << "invalid type passed in getTransPicPath()" << endl;
        return QPixmap();
    }
}

void SpriteCard::on_clicked() {
    Game* game = Game::getInstance();

    if(game->selectedCard == nullptr) {   //if no card is currently selected
        game->selectedSprite = type;
        game->selectedCard = this;

        this->setStyleSheet("#" + objectName() +"{ color: white; border: 3px solid yellow;}");
    } else {
        if(game->selectedCard == this) {   //if yourself is the card selected
            game->selectedCard = nullptr;
            game->selectedSprite = TimeVariant::Type::EMPTY;
            this->setStyleSheet("color: white;");

        } else {                     // if another card was previously selected
            emit game->selectedCard->clicked();
            game->selectedCard = this;
            game->selectedSprite = type;
            this->setStyleSheet("#" + objectName() +"{ color: white; border: 3px solid yellow;}");
        }
    }
    game->transLabel->setPixmap(getTransPicPath(game->selectedSprite));
}
