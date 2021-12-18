#include "wordtext.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    wordText w;
    w.show();
    return a.exec();
}
