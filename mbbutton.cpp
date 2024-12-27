#include <QPainter>
#include "mbbutton.h"

/* public */

MbButton::MbButton(QWidget *parent): MbButton("Button", parent)
{

}

MbButton::MbButton(const QString &text, QWidget *parent): QWidget{parent}
{
    isHovering = false;
    isPressed = false;
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_text = text;
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

QSize MbButton::minimumSizeHint() const
{
    // Minimum width is width of text + margin
    QFont font("Arial", 12, QFont::Normal);
    QFontMetrics metrics(font);
    int textWidth = metrics.horizontalAdvance(m_text);
    return QSize(textWidth + 10, 22);
}

void MbButton::mousePressEvent(QMouseEvent *event)
{
    isPressed = true;
    emit clicked();
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
    QFont font("Arial", 12, QFont::Normal);
    painter.setPen(Qt::black);
    painter.setFont(font);
    painter.drawText(rect(), Qt::AlignCenter, m_text);
}

QSize MbButton::sizeHint() const
{
    QFont font("Arial", 12, QFont::Normal);
    QFontMetrics metrics(font);
    int textWidth = metrics.horizontalAdvance(m_text);
    return QSize(textWidth + 10, 22);
}
