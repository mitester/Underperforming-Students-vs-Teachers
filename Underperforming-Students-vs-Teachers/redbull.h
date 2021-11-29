#ifndef REDBULL_H
#define REDBULL_H

#include "item.h"
#include "clickablelabel.h"
#include <QMediaPlayer>

class Redbull : public Item
{
    Q_OBJECT
public:
    static const int DEFAULT_ENERGY = 10;
    static const int DEFAULT_INITIAL_VELOCITY_X{3};
    static const int DEFAULT_INITIAL_VELOCITY_Y{-14};
    static const int DEFAULT_INITIAL_ACCELERATION_Y{1};
    static const int SPRITE_WIDTH{50};
    static const int SPRITE_HEIGHT{42};

    static QPixmap* PIC_0;

    Redbull(ClickableLabel* widget, int energy = DEFAULT_ENERGY,
            int vx = DEFAULT_INITIAL_VELOCITY_X, int vy = DEFAULT_INITIAL_VELOCITY_Y,
            int ay = DEFAULT_INITIAL_ACCELERATION_Y);

    //getter & settter for energy
    int getEnergy() const;
    void setEnergy(int energy);

    //override
    TimeVariant::Type getType() const;

    //override
    void update();



private:
    int energy; //stores how many energy this redbull owns

    void pressed(); //private function handling redbull is pressed

    //stores the kinematic quanties for the redbull parabola
    int vx_initial, vx;
    int vy_initial, vy;
    int ay;

    //stores the isPressed state
    bool isPressed = false;

    ClickableLabel* widget;

    QMediaPlayer player;

};

#endif // REDBULL_H
