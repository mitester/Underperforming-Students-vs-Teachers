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
    switch (type) {     //check the type passed in by user, and set the card to correspondign pixmap.
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

    costLabel = new QLabel(this);   //generate the costLabel, and put it in the spritecard to display the price
    int cost = Game::getCost(type);
    costLabel->setText(cost != 0 ? QString::number(cost) : "");
    costLabel->setStyleSheet("color: black; font-size: 19px; font: bold;");
    costLabel->move(COST_X, COST_Y);

    setObjectName("SpriteCard");    //this is for future style sheet control

    connect(this, &ClickableLabel::clicked, this, &SpriteCard::on_clicked); // link the clicked event to the slot function

    player = new QMediaPlayer(this);
    player->setMedia(QUrl("qrc:/sounds/electric_pop.wav")); // some sound effect
}

QPixmap getTransPicPixmap(TimeVariant::Type type) { // an utility function that returns the transparent pixmap for every student.
    switch (type) {     // match over different types
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

void SpriteCard::on_clicked() { //the slot function
    Game* game = Game::getInstance();

    if(game->selectedCard == nullptr && game->getRedbullNum() >= game->getCost(this->type)) {

        //if no card is currently selected
        //modify the fields in game controller and set your stylesheet
        game->selectedSprite = type;
        game->selectedCard = this;
        this->setStyleSheet("#" + objectName() +"{ color: white; border: 3px solid yellow;}");
        // used objectName as selector to avoid the style being passed to child widget (costLabel)

    } else {    // another card is selected

        if(game->selectedCard == this) {   //if yourself is the card selected

            //diselected yourself
            game->selectedCard = nullptr;
            game->selectedSprite = TimeVariant::Type::EMPTY;
            this->setStyleSheet("color: white;");

        } else if(game->getRedbullNum() < game->getCost(this->type)){ // if another card was previously selected, but no enough budget

            player->play(); // play the rejection sound effect

        } else {    //if another card was previously selected

            emit game->selectedCard->clicked(); //we want to cancel its selection => we "click" it.
            game->selectedCard = this;
            game->selectedSprite = type;
            this->setStyleSheet("#" + objectName() +"{ color: white; border: 3px solid yellow;}");

        }
    }

    game->transLabel->setPixmap(getTransPicPixmap(game->selectedSprite));   // we set the transparent widget to be the selected sprite
    //(for displaying the transparent sprite)
}
