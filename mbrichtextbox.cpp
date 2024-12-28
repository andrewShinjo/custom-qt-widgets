#include <QPainter>
#include "mbrichtextbox.h"

/* public */

MbRichTextBox::MbRichTextBox(QWidget *parent)
    : QWidget{parent}
{

    textDocument = new QTextDocument;

    marginBottom = DEFAULT_MARGIN;
    marginLeft = DEFAULT_MARGIN;
    marginRight = DEFAULT_MARGIN;
    marginTop = DEFAULT_MARGIN;

    paddingBottom = DEFAULT_PADDING;
    paddingLeft = DEFAULT_PADDING;
    paddingRight = DEFAULT_PADDING;
    paddingTop = DEFAULT_PADDING;
}

/* protected */

void MbRichTextBox::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Draw background color.
    {
        painter.setBrush(QBrush(Qt::white));
        painter.setPen(Qt::NoPen);
        painter.drawRect(rect());
    }

    QRect marginBorder(
        marginLeft,
        marginTop,
        width() - marginLeft - marginRight,
        height() - marginTop - marginBottom
    );

    // Draw margin border.
    {
        painter.setPen(QPen(Qt::black, 0.25));
        painter.drawRect(marginBorder);
    }

    QRect paddingBorder = marginBorder.adjusted(
        paddingLeft,
        paddingTop,
        - paddingRight,
        - paddingBottom
    );

    // Draw padding border.
    {
        painter.setPen(QPen(Qt::blue, 0.25));
        painter.drawRect(paddingBorder);
    }
}
