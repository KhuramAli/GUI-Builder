#include <QApplication>

#include "MainWindow.h"

int main (int argc, char * argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.setFixedSize(800, 600);
    window.show();
    //window.showMaximized();
    return app.exec();
}
