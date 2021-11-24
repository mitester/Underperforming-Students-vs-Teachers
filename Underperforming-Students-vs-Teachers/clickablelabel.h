#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~ClickableLabel();

    //set the clickable property
    //if not clickable, no clicked() will be emitted
    void setClickable(bool x);
    bool isClickable() const;


signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);

private:
    bool clickable = true;

};

#endif // CLICKABLELABEL_H
