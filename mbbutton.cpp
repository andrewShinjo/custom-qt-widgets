#include <QPainter>
#include "mbbutton.h"

MbButton::MbButton(QWidget *parent)
    : QWidget{parent}
{}

void MbButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QRect rectangle(0, 0, 200, 100);
    painter.drawRect(rectangle);

    QFont font("Arial", 20, QFont::Bold);
    painter.setFont(font);

    QString text = "Button";
    painter.drawText(rectangle, Qt::AlignCenter, text);
}
