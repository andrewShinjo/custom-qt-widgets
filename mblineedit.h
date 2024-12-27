#ifndef MBLINEEDIT_H
#define MBLINEEDIT_H

#include <QWidget>

class MbLineEdit : public QWidget
{
    Q_OBJECT

public:
    explicit MbLineEdit(QWidget *parent = nullptr);
protected:
    QSize minimumSizeHint() const override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    QSize sizeHint() const override;
signals:
private:
    bool isSelected;
};

#endif // MBLINEEDIT_H
