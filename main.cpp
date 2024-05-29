#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // Establecer el fondo azul para la ventana principal
        w.setStyleSheet("background-color:blue;");
    w.show();
    return a.exec();

}
