#include <QPainter>
#include "mbbutton.h"

MbButton::MbButton(QWidget *parent)
    : QWidget{parent}
{}

void MbButton::enterEvent(QEnterEvent *event)
{
    qDebug() << "enterEvent";
}

void MbButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QFont font("Arial", 20, QFont::Bold);
    painter.setFont(font);

    QString text = "Button";
    painter.drawText(rect(), Qt::AlignCenter, text);
}
