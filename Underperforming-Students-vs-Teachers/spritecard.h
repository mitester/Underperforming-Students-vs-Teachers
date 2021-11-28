#ifndef SPRITECARD_H
#define SPRITECARD_H

#include "clickablelabel.h"
#include <QWidget>
#include "timevariant.h"

class SpriteCard : public ClickableLabel
{
public:
    const static int WIDTH = 100;
    const static int HEIGHT = 125;
    const static int COST_X = 35;
    const static int COST_Y = 97;
    SpriteCard(TimeVariant::Type type, QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    void on_clicked(); //the slot function for being clicked.

protected:
    TimeVariant::Type type;


private:
    bool selected = false;
};

#endif // SPRITECARD_H
