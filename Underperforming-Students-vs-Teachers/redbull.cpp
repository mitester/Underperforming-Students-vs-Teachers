#include "redbull.h"
#include <QDebug>
#include <QRandomGenerator>
#include "game.h"
#include <QVector2D>

QPixmap* Redbull::PIC_0 = nullptr;

Redbull::Redbull(ClickableLabel* widget, int energy, int vx, int vy, int ay) : Item(widget, nullptr),
    energy(energy), vx_initial(vx), vx(vx), vy_initial(vy), vy(vy), ay(ay), widget(widget)
{
    connect(widget, &ClickableLabel::clicked, this, &Redbull::pressed);
    player.setParent(widget);
    player.setMedia(QUrl("qrc:/sounds/redbull.mp3"));
}

int Redbull::getEnergy() const
{
    return energy;
}

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
    if(isPressed)
    {
        Game::getInstance()->addRedbull();
        player.play();
        widget->setClickable(false);
        if(widget->pos().x() >= Game::REDBULL_POS.x())
        {
            deleteLater();
            return;
        }

        QVector2D v(Game::REDBULL_POS - widget->pos());
        v.normalize();
        v*=20;
        widget->move(widget->pos() + v.toPoint());
    }
    else
    {
        widget->raise();
        if(vy == -vy_initial) return; //parabola completed
        widget->show();
        widget->move(widget->x() + vx, widget->y() + vy);
        vy += ay;
    }

}

void Redbull::pressed()
{
    isPressed = true;
}
