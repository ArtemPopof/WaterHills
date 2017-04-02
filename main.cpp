#include "editowindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EditoWindow w;
    w.show();

    return a.exec();
}
