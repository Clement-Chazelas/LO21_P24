#include <QApplication>
#include <QString>
#include <iostream>
#include <string>
#include "partie.h"
#include "utils.h"

using namespace std;

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    Partie p("Ducasse", "Agathe", "Chazelas", "Clement");
    cout << p << endl;

    //p.genererHuitMerveilles(); //generation random parmis un csv

    p.genererAgeUn(); //idem
    //Pour l'instant les batiments sont simplement dans une liste de pointeur de plateau de jeu

    //p.selectionDesMerveilles();

    cout << p.getPlateau(); //on affiche les merveilles et les batiments qu'il y a sur le plateau de jeu

    return 0;
}
