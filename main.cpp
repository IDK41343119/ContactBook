#include "contactbook.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ContactBook w;
    w.show();
    return a.exec();
}
