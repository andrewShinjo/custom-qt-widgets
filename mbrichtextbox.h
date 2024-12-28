#ifndef MBRICHTEXTBOX_H
#define MBRICHTEXTBOX_H

#include <QTextDocument>
#include <QWidget>

class MbRichTextBox : public QWidget
{
    Q_OBJECT
public:
    explicit MbRichTextBox(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

signals:

private:

    /* data structure -- start */

    QTextDocument *textDocument;

    /* data structure -- end */

    /* appearance variables -- start */

    static const int DEFAULT_MARGIN = 10;
    static const int DEFAULT_PADDING = 10;

    int marginBottom;
    int marginLeft;
    int marginRight;
    int marginTop;

    int paddingBottom;
    int paddingLeft;
    int paddingRight;
    int paddingTop;

    /* appearance variables -- end */
};

#endif // MBRICHTEXTBOX_H
