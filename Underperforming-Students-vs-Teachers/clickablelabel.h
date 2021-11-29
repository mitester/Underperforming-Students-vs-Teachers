/***
 * Since QLabel doesn't emit clicked() signal when it is clicked
 * ClickableLabel overrided QLabel's mousePressEvent() and emit clicked() signal when it's clicked and clickable
 */
#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    //constructor
    explicit ClickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~ClickableLabel();

    //set the clickable property
    //if not clickable, no clicked() will be emitted
    void setClickable(bool x);
    bool isClickable() const;


signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event); //inherits from QLabel

private:
    bool clickable = true; // the property indicates if it is clickable
                           // if not, no clicked() will be emitted

};

#endif // CLICKABLELABEL_H
