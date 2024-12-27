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
    QSize minimumSizeHint() const override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    QSize sizeHint() const override;
signals:
    void clicked();
    void textChanged(const QString &text);
private:
    QString m_text;
    bool isHovering;
    bool isPressed;
};

#endif // MBBUTTON_H
