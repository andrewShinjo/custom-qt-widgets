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

    MbButton *button1 = new MbButton();
    QPushButton *button2 = new QPushButton("Button Button Button");

    layout->addWidget(button1);
    // layout->addWidget(button2);

    QObject::connect(button1, &MbButton::clicked, showMessage);

    window.setLayout(layout);
    window.show();

    return a.exec();
}
