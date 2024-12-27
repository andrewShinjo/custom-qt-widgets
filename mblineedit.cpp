#include <QPainter>
#include "mblineedit.h"

const int DEFAULT_MARGIN = 10;

MbLineEdit::MbLineEdit(QWidget *parent) : QWidget{parent}
{
    isSelected = false;
}

QSize MbLineEdit::minimumSizeHint() const
{
    int height = 12 + 5 + 5;
    int width = rect().width();
    return QSize(width, height);
}

void MbLineEdit::mousePressEvent(QMouseEvent *event)
{
    isSelected = true;
    update();
}

void MbLineEdit::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Draw border.
    {
        if(isSelected)
        {
            painter.setPen(QPen(Qt::blue, 4));
        }
        else if(!isSelected)
        {
            painter.setPen(QPen(Qt::black, 2));
        }
        painter.drawRect(rect());
    }

}

QSize MbLineEdit::sizeHint() const
{
    int height = 12 + 5 + 5;
    int width = rect().width();
    return QSize(width, height);
}
