#include "human.h"

Human::Human(QWidget *widget, QString name, int maxHp) : TimeVariant(widget), name(name), hp(maxHp), maxHp(maxHp)
{

}

//getter and setter for w
QWidget getWidget();
void setWidget(QWidget* widget);

//getter and setter for name
QString getName();
int setName(QString name);

//getter and setter for maxHp
int getMaxHp();
void setMaxHp(int maxHp);

//getter and setter for hp
int getHp();
void setHp(int hp);

