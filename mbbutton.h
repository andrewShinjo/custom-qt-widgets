#ifndef MBBUTTON_H
#define MBBUTTON_H

#include <QWidget>

class MbButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged)

public:
    explicit MbButton(QWidget *parent = nullptr);
    QString getText() const;
    void setText(const QString &text);
protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
signals:
    void textChanged(const QString &text);
private:
    QString m_text;
    bool isHovering;
};

#endif // MBBUTTON_H
