#include <QtWidgets>

#include "./mbbutton.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget window;
    QVBoxLayout *layout = new QVBoxLayout;

    MbButton *myButton = new MbButton();
    QPushButton *qtButton = new QPushButton("Button");

    layout->addWidget(myButton);
    layout->addWidget(qtButton);

    window.setLayout(layout);
    window.show();

    return a.exec();
}
