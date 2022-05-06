#include "mainstratego.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainStratego w;
    w.show();


    return a.exec();
}
