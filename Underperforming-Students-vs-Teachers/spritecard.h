#ifndef SPRITECARD_H
#define SPRITECARD_H

#include "clickablelabel.h"
#include <QWidget>
#include "timevariant.h"
#include <QMediaPlayer>

/***    ---- Description ----
 *
 *  SpriteCards are the student cards shown in the sprite selection board (on the left of the game scene)
 *  It is a subclass of ClickableLabel.
 *
 *  When being clicked, it checks whether it was clicked before, and do corresponding behaviour. (stylesheet change)
 *
 *
 * */

class SpriteCard : public ClickableLabel
{
public:
    const static int WIDTH = 100;
    const static int HEIGHT = 125;
    const static int COST_X = 35;
    const static int COST_Y = 97;
    SpriteCard(TimeVariant::Type type, QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    void on_clicked(); //the slot function for being clicked.
    QLabel* costLabel = nullptr;    //the label storing the redbull cost

protected:
    TimeVariant::Type type;     //the type of the spriteCard.


private:
    bool selected = false;  // if yourself is selected, default is false
    QMediaPlayer* player;
};

#endif // SPRITECARD_H
