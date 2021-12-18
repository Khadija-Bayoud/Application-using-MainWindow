#include "spreadsheet.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    spreadSheet w;
    w.show();
    return a.exec();
}
