#include <QMouseEvent>
#include <QPainter>
#include <QtGlobal>
#include "mblineedit.h"

MbLineEdit::MbLineEdit(QWidget *parent)
    : QWidget{parent},
    m_cursorPosition(0),
    m_text("")
{
    // Initialize timer.
    {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MbLineEdit::blinkCursor);
        timer->start(500);
    }

    // Initialize appearance variables.
    {
        font = new QFont("Arial", 12);
        bottomPadding = DEFAULT_PADDING;
        leftPadding = DEFAULT_PADDING;
        rightPadding = DEFAULT_PADDING;
        topPadding = DEFAULT_PADDING;
        offset = 0;
    }

    // Initialize text selection variables.
    {
        selecting = false;
        selectionStart = 0;
        selectionEnd = 0;
    }

    isSelected = false;
    setFocusPolicy(Qt::StrongFocus);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
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
    updateOffset();
}

void MbLineEdit::setText(const QString &text)
{
    m_text = text;
}

/* protected */

void MbLineEdit::keyPressEvent(QKeyEvent *event)
{
    bool highlightTextSelection = selectionStart != selectionEnd;

    switch(event->key())
    {
        case Qt::Key_Left:
        {
            if(m_cursorPosition > 0)
            {
                m_cursorPosition--;
                updateOffset();
            }
            break;
        }
        case Qt::Key_Right:
        {
            if(m_cursorPosition < m_text.length())
            {
                m_cursorPosition++;
                updateOffset();
            }
            break;
        }
        case Qt::Key_Backspace:
        {
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
                    updateOffset();
                }
            }
        }
        default:
        {
            bool isKeyPrintable = !event->text().isEmpty() && event->text().at(0).isPrint();
            if(isKeyPrintable && !highlightTextSelection)
            {
                m_text.insert(m_cursorPosition++, event->text());
            }
            else if(isKeyPrintable && highlightTextSelection)
            {
                m_text.clear();
                m_cursorPosition = 0;
                m_text.insert(m_cursorPosition++, event->text());
                selectionStart = 0;
                selectionEnd = 0;
            }

            updateOffset();
        }
    }

    bool controlAPressed = event->modifiers() & Qt::ControlModifier && event->key() == Qt::Key_A;

    if(controlAPressed)
    {
        selectionStart = 0;
        selectionEnd = m_text.length();
    }

    update();
}

QSize MbLineEdit::minimumSizeHint() const
{
    int height = font->pointSize() + bottomPadding + topPadding;
    return QSize(0, height);
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

    painter.setFont(*font);
    QFontMetrics metrics(*font);
    int maxWidth = width() - leftPadding - rightPadding;
    QRect paddedRectagle = rect().adjusted(leftPadding, 0, -1 * rightPadding, 0);
    bool highlightTextSelection = selectionStart != selectionEnd;

    // Draw text selection.
    {
        if(highlightTextSelection)
        {
            int startX = metrics.horizontalAdvance(m_text.left(selectionStart)) + leftPadding;
            int startY = topPadding;
            int endX = qMin(metrics.horizontalAdvance(m_text.right(selectionEnd)) + leftPadding, width() - rightPadding);
            QRect highlightRect = QRect(QPoint(startX, startY), QSize(endX - startX, metrics.height() - bottomPadding));
            painter.setBrush(Qt::yellow);
            painter.setPen(Qt::NoPen);
            painter.drawRect(highlightRect);
        }
    }

    // Draw text.
    {
        QRect adjustedRect = paddedRectagle.adjusted(-1 * offset, 0, 0, 0);
        painter.setPen(QPen(Qt::black, 2));
        painter.drawText(adjustedRect, Qt::AlignLeft | Qt::AlignVCenter, m_text);
    }

    // Draw text cursor.
    {
        if(isSelected && isCursorVisible && !highlightTextSelection)
        {
            int cursorX = metrics.horizontalAdvance(m_text.left(m_cursorPosition)) + leftPadding - offset;
            int cursorY = (height() - metrics.height()) / 2;
            int cursorHeight = metrics.height();
            painter.drawLine(cursorX, cursorY, cursorX, cursorY + cursorHeight);
        }
    }
}

QSize MbLineEdit::sizeHint() const
{
    int height = font->pointSize() + bottomPadding + topPadding;
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

void MbLineEdit::updateOffset()
{
    QFontMetrics metrics(*font);
    int cursorX = metrics.horizontalAdvance(m_text, m_cursorPosition);

    // Get the current start and end.
    int currentStart = offset;
    int currentEnd = currentStart + (width() - leftPadding - rightPadding);

    if(cursorX < currentStart)
    {
        offset -= (currentStart - cursorX);
    }
    else if(cursorX > currentEnd)
    {
        offset += (cursorX - currentEnd);
    }
}
