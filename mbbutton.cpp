#include <QPainter>
#include "mbbutton.h"

/* public */

MbButton::MbButton(QWidget *parent): QWidget{parent}, m_text("Button")
{

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
    qDebug() << "enterEvent";
}

void MbButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QFont font("Arial", 20, QFont::Bold);
    painter.setFont(font);

    painter.drawText(rect(), Qt::AlignCenter, m_text);
}
