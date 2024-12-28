#include "customtextobject.h"
#include <qpainter.h>

/* public */

CustomTextObject::CustomTextObject(QObject *parent)
    : QObject{parent}
{}

void CustomTextObject::drawObject(
    QPainter *painter,
    const QRectF &rect,
    QTextDocument *doc,
    int posInDocument,
    const QTextFormat &format
)
{
    painter->setBrush(Qt::yellow);
    painter->drawRect(rect);
    painter->setPen(Qt::black);
    painter->drawText(rect, Qt::AlignCenter, "Custom widget");
}

QSizeF CustomTextObject::intrinsicSize(
    QTextDocument *doc,
    int posInDocument,
    const QTextFormat &format
)
{
    return QSizeF(500, 50);
}
