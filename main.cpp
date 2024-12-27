#include <QtWidgets>

#include "./mbbutton.h"
#include "./mblineedit.h"

void showMessage()
{
    qDebug() << "Connected to click";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget window;
    QVBoxLayout *layout = new QVBoxLayout;

    MbButton *button1 = new MbButton("Button 1");
    MbLineEdit *lineEdit = new MbLineEdit();

    lineEdit->setText("This is text");

    layout->addWidget(button1);
    layout->addWidget(lineEdit);

    QObject::connect(button1, &MbButton::clicked, showMessage);

    window.setLayout(layout);
    window.show();

    return a.exec();
}
