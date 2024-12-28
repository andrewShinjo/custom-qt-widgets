#ifndef CUSTOMTEXTOBJECT_H
#define CUSTOMTEXTOBJECT_H

#include <QObject>
#include <QTextObjectInterface>

class CustomTextObject : public QObject, public QTextObjectInterface
{
    Q_OBJECT
    Q_INTERFACES(QTextObjectInterface)
public:

    enum
    {
        CustomTextObjectFormat = QTextFormat::UserObject + 1
    };

    explicit CustomTextObject(QObject *parent = nullptr);

    void drawObject(
        QPainter *painter,
        const QRectF &rect,
        QTextDocument *doc,
        int posInDocument,
        const QTextFormat &format
    ) override;

    QSizeF intrinsicSize(QTextDocument *doc, int posInDocument, const QTextFormat &format) override;

signals:
};

#endif // CUSTOMTEXTOBJECT_H
