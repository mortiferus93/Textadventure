#include "textadventure.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Textadventure w;
    w.show();

    return a.exec();
}
