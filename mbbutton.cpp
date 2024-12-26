#include <QPainter>
#include "mbbutton.h"

/* public */

MbButton::MbButton(QWidget *parent): QWidget{parent}, m_text("Button")
{
    isHovering = false;
}

QString MbButton::getText() const
{
    return m_text;
}

void MbButton::setText(const QString &text)
{
    if(this->m_text == text)
    {
        return;
    }

    m_text = text;
    emit textChanged(m_text);
    update();
}

void MbButton::enterEvent(QEnterEvent *event)
{
    isHovering = true;
    update();
}

void MbButton::leaveEvent(QEvent *event)
{
    isHovering = false;
    update();
}

void MbButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if(isHovering)
    {
        painter.setBrush(QColor(100, 150, 200));
        painter.setPen(Qt::NoPen);
        painter.drawRect(rect());
    }

    QFont font("Arial", 20, QFont::Bold);
    painter.setPen(Qt::black);
    painter.setFont(font);
    painter.drawText(rect(), Qt::AlignCenter, m_text);
}
