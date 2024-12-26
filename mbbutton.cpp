#include <QPainter>
#include "mbbutton.h"

MbButton::MbButton(QWidget *parent)
    : QWidget{parent}
{}

void MbButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawRect(0, 0, 200, 50);
}
