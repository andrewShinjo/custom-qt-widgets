#include <QPainter>
#include "mbbutton.h"

/* public */

MbButton::MbButton(QWidget *parent): QWidget{parent}, m_text("Button")
{
    isHovering = false;
    isPressed = false;
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

void MbButton::mousePressEvent(QMouseEvent *event)
{
    isPressed = true;
    update();
}

void MbButton::mouseReleaseEvent(QMouseEvent *event)
{
    isPressed = false;
    update();
}

void MbButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if(isPressed)
    {
        painter.setBrush(QColor(70, 120, 170));
        painter.setPen(Qt::NoPen);
        painter.drawRect(rect());
    }
    else if(isHovering)
    {
        painter.setBrush(QColor(100, 150, 200));
        painter.setPen(Qt::NoPen);
        painter.drawRect(rect());
    }

    // Draw border.
    {
        painter.setPen(QPen(Qt::black, 2));
        painter.drawRect(rect());
    }

    // Draw text.
    QFont font("Arial", 12, QFont::Bold);
    painter.setPen(Qt::black);
    painter.setFont(font);
    painter.drawText(rect(), Qt::AlignCenter, m_text);
}

QSize MbButton::sizeHint() const
{
    return QSize(300, 22);
}
