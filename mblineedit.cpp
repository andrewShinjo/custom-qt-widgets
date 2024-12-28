#include <QMouseEvent>
#include <QPainter>
#include <QtGlobal>
#include "mblineedit.h"

const int DEFAULT_MARGIN = 10;

MbLineEdit::MbLineEdit(QWidget *parent)
    : QWidget{parent},
    m_cursorPosition(0),
    m_text("")
{
    // Initialize timer
    {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MbLineEdit::blinkCursor);
        timer->start(500);
    }

    isSelected = false;
    setFocusPolicy(Qt::StrongFocus);
}

int MbLineEdit::getCursorPosition() const
{
    return m_cursorPosition;
}

QString MbLineEdit::getText() const
{
    return m_text;
}

void MbLineEdit::setCursorPosition(int cursorPosition)
{
    m_cursorPosition = cursorPosition;
}

void MbLineEdit::setText(const QString &text)
{
    m_text = text;
}

/* protected */

void MbLineEdit::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Left:
        {
            if(m_cursorPosition > 0)
            {
                m_cursorPosition--;
                update();
            }
            break;
        }
        case Qt::Key_Right:
        {
            if(m_cursorPosition < m_text.length())
            {
                m_cursorPosition++;
                update();
            }
            break;
        }
        case Qt::Key_Backspace:
        {
            bool highlightTextSelection = selectionStart != selectionEnd;

            if(highlightTextSelection)
            {
                int removeStart = qMin(selectionStart, selectionEnd);
                int removeEnd = qMax(selectionStart, selectionEnd);
                m_text.remove(removeStart, removeEnd - removeStart);
                m_cursorPosition = removeStart;
                selectionStart = 0;
                selectionEnd = 0;
            }
            else if(!highlightTextSelection)
            {
                if(m_cursorPosition > 0)
                {
                    m_text.remove(--m_cursorPosition, 1);
                }
            }
        }
        default:
        {
            bool isKeyPrintable = !event->text().isEmpty() && event->text().at(0).isPrint();
            if(isKeyPrintable)
            {
                m_text.insert(m_cursorPosition++, event->text());
            }
        }
    }

    bool controlAPressed = event->modifiers() & Qt::ControlModifier && event->key() == Qt::Key_A;

    if(controlAPressed)
    {
        selectionStart = 0;
        selectionEnd = m_text.length();
    }
}

QSize MbLineEdit::minimumSizeHint() const
{
    int height = 12 + 5 + 5;
    int width = rect().width();
    return QSize(width, height);
}

void MbLineEdit::mouseMoveEvent(QMouseEvent *event)
{
    // Handle text selection
    {
        if(selecting)
        {
            int x = event->pos().x();
            selectionEnd = charIndexAt(x);
        }
    }

    update();
}

void MbLineEdit::mousePressEvent(QMouseEvent *event)
{
    // Update cursor position depending on location of mouse press.
    {
        int x = event->pos().x();
        int index = charIndexAt(x);
        m_cursorPosition = index;
    }

    // Handle text selection.
    {
        int x = event->pos().x();
        selectionStart = charIndexAt(x);
        selectionEnd = charIndexAt(x);
        selecting = true;
    }

    isSelected = true;
    update();
}

void MbLineEdit::mouseReleaseEvent(QMouseEvent *event)
{
    // Handle text selection.
    {
        selecting = false;
    }
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

    QFont font("Arial", 12);
    painter.setFont(font);
    QFontMetrics metrics(font);
    int maxWidth = width();
    QString elidedText = metrics.elidedText(m_text, Qt::ElideRight, maxWidth);

    bool highlightTextSelection = selectionStart != selectionEnd;

    // Draw text selection.
    {
        if(highlightTextSelection)
        {
            int startX = metrics.horizontalAdvance(elidedText.left(selectionStart));
            int endX = metrics.horizontalAdvance(elidedText.left(selectionEnd));
            painter.setBrush(Qt::yellow);
            painter.setPen(Qt::NoPen);
            painter.drawRect(QRect(QPoint(startX, 5), QSize(endX - startX, metrics.height() - 5)));
        }
    }

    // Draw text.
    {
        painter.setPen(QPen(Qt::black, 2));
        painter.drawText(rect(), Qt::AlignLeft | Qt::AlignVCenter, elidedText);
    }

    // Draw text cursor.
    {
        if(isSelected && isCursorVisible && !highlightTextSelection)
        {
            int cursorX = metrics.horizontalAdvance(elidedText.left(m_cursorPosition));
            int cursorY = (height() - metrics.height()) / 2;
            int cursorHeight = metrics.height();
            painter.drawLine(cursorX, cursorY, cursorX, cursorY + cursorHeight);
        }
    }
}

QSize MbLineEdit::sizeHint() const
{
    int height = 12 + 5 + 5;
    int width = rect().width();
    return QSize(width, height);
}

/* private slots */

void MbLineEdit::blinkCursor()
{
    isCursorVisible = !isCursorVisible;
    update();
}

/* private */

int MbLineEdit::charIndexAt(int x)
{
    QFont font("Arial", 12);
    QFontMetrics metrics(font);
    int widthAccumulated = 0;

    for(int i = 0; i < m_text.length(); i++)
    {
        widthAccumulated += metrics.horizontalAdvance(m_text[i]);
        if(x < widthAccumulated)
        {
            return i;
        }
    }

    return m_text.length();
}
