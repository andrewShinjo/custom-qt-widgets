#include <QtWidgets>
#include "customtextobject.h"

void showMessage()
{
    qDebug() << "Connected to click";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextEdit *textEdit = new QTextEdit;

    // Add table.
    {
        QTextCursor cursor = textEdit->textCursor();
        QTextTableFormat tableFormat;
        tableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));
        QTextTable *table = cursor.insertTable(3, 2, tableFormat);

        QTextTableCellFormat cellFormat;
        cellFormat.setBorder(1);
        cellFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
        cellFormat.setBorderBrush(Qt::black);

        for(int row = 0; row < 3; row++)
        {
            for(int col = 0; col < 2; col++)
            {
                QTextTableCell cell = table->cellAt(row, col);
                cell.setFormat(cellFormat);
                QTextCursor cellCursor = cell.firstCursorPosition();
                cellCursor.insertText(QString("Row %1, Column %2").arg(row + 1).arg(col + 1));
            }
        }
    }

    // Add custom widget.
    {
        CustomTextObject *object = new CustomTextObject;
        textEdit->document()->documentLayout()->registerHandler(
            CustomTextObject::CustomTextObjectFormat, object
        );

        QTextCursor cursor = textEdit->textCursor();
        QTextCharFormat format;
        format.setObjectType(CustomTextObject::CustomTextObjectFormat);
        cursor.insertText(QString(QChar::ObjectReplacementCharacter), format);
    }


    textEdit->show();
    return a.exec();
}
