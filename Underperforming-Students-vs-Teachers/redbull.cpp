#include "redbull.h"
#include <QDebug>
#include <QRandomGenerator>
#include "game.h"
#include <QVector2D>

QPixmap* Redbull::PIC_0 = nullptr;

//constructor
Redbull::Redbull(ClickableLabel* widget, int energy, int vx, int vy, int ay) : Item(widget, nullptr),
    energy(energy), vx_initial(vx), vx(vx), vy_initial(vy), vy(vy), ay(ay), widget(widget)
{
    //connect pressed() to the clicked() signal of ClickableLabel
    connect(widget, &ClickableLabel::clicked, this, &Redbull::pressed);
    player.setParent(widget);
    player.setMedia(QUrl("qrc:/sounds/redbull.mp3"));
}

//getter of energy
int Redbull::getEnergy() const
{
    return energy;
}

//setter of energy
void Redbull::setEnergy(int energy)
{
    this->energy = energy;
}

TimeVariant::Type Redbull::getType() const
{
    return TimeVariant::Type::REDBULL;
}

void Redbull::update()
{
    if(isPressed) //if the redbull is pressed
    {
        widget->setClickable(false); //it is unable to be clicked twice
        if(widget->pos().x() >= Game::REDBULL_POS.x()) //if it reaches the destination
        {
            deleteLater(); //it will be deleted
            return; //return the function
        }

        //compute the velocity vector v
        QVector2D v(Game::REDBULL_POS - widget->pos());
        v.normalize();
        v*=20;

        //move the redbull by the velocity vector v
        widget->move(widget->pos() + v.toPoint());
    }
    else //if not pressed
    {
        //if current time left is greater than 0, means the game continues
        //then redbull has to be raised to the top so that users can click it
        if(Game::getInstance()->getCurrentMsLeft() > 0)
            widget->raise();
        else
        {
            widget->setClickable(false); //if the game ends, redbull is no longer clickable
        }

        //making the trajectory of redbull going with a parabola
        if(vy == -vy_initial) return; //parabola completed
        widget->show();
        widget->move(widget->x() + vx, widget->y() + vy);
        vy += ay;
    }

}

//will be called when redbull is clicked
void Redbull::pressed()
{
    isPressed = true;
    Game::getInstance()->addRedbull();
    player.play();
}
