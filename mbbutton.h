#ifndef MBBUTTON_H
#define MBBUTTON_H

#include <QWidget>

class MbButton : public QWidget
{
    Q_OBJECT
public:
    explicit MbButton(QWidget *parent = nullptr);
protected:
    void enterEvent(QEnterEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:
};

#endif // MBBUTTON_H
