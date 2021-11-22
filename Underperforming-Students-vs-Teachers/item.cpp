#include "item.h"

Item::Item(QLabel* widget, Row* row) : TimeVariant(widget, row)
{

}

TimeVariant::Category Item::getCategory() const
{
    return TimeVariant::Category::ITEM;
}
