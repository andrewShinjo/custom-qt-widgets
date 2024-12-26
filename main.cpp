#include <QtWidgets>

#include "./mbbutton.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MbButton* button = new MbButton();
    button->show();
    return a.exec();
}
