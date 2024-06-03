#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
    return a.exec();
}


/*To do list

-Faire affichage selection des merveilles
-Faire affichage Age 1
-Faire affichage Age 2
-Faire affichage Age 3
-Faire des bons grids pour l'interface
-On reprend les images de Board Game Arena pour le fond


*/
