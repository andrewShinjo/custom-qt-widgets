#include <QtWidgets>

#include "./mbbutton.h"

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
    MbButton *button2 = new MbButton("Button 2");
    MbButton *button3 = new MbButton("Button 3");
    MbButton *button4 = new MbButton("Button 4");
    MbButton *button5 = new MbButton("Button 5");

    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);
    layout->addWidget(button4);
    layout->addWidget(button5);

    QObject::connect(button1, &MbButton::clicked, showMessage);

    window.setLayout(layout);
    window.show();

    return a.exec();
}
