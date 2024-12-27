#ifndef MBLINEEDIT_H
#define MBLINEEDIT_H

#include <QWidget>

class MbLineEdit : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int cursorPosition READ getCursorPosition WRITE setCursorPosition NOTIFY cursorPositionChanged)
    Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged)

public:
    explicit MbLineEdit(QWidget *parent = nullptr);

    /* Property - get */
    int getCursorPosition() const;
    QString getText() const;

    /* Property - set */
    void setCursorPosition(int cursorPosition);
    void setText(const QString &text);

protected:
    QSize minimumSizeHint() const override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    QSize sizeHint() const override;

signals:
    void cursorPositionChanged(const int &cursorPosition);
    void textChanged(const QString &text);

private:
    int m_cursorPosition;
    QString m_text;
    bool isSelected;

    int charIndexAt(int x);
};

#endif // MBLINEEDIT_H
