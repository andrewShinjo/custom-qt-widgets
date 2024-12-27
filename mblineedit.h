#ifndef MBLINEEDIT_H
#define MBLINEEDIT_H

#include <QWidget>

class MbLineEdit : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged)

public:
    explicit MbLineEdit(QWidget *parent = nullptr);

    QString getText() const;
    void setText(const QString &text);

protected:
    QSize minimumSizeHint() const override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    QSize sizeHint() const override;

signals:
    void textChanged(const QString &text);

private:
    QString m_text;
    bool isSelected;
};

#endif // MBLINEEDIT_H
