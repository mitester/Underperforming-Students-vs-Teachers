#include "item.h"

QPixmap* Item::EXPLOSION_0 = nullptr;
QPixmap* Item::EXPLOSION_1 = nullptr;
QPixmap* Item::EXPLOSION_2 = nullptr;

Item::Item(QLabel* widget, Row* row) : TimeVariant(widget, row)
{

}

TimeVariant::Category Item::getCategory() const
{
    return TimeVariant::Category::ITEM;
}
