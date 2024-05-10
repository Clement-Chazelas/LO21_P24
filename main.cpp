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

    //p.genererAgeUn(); //idem pour les batiments de l'age I
    //p.genererAgeDeux(); // Age I et Age II ne peuvent pas etre genere en meme temps pour le moment

    //p.selectionDesMerveilles(); //Choix successifs des merveilles
    //Il faut mettre le nom exact pour choisir la carte !

    //p.getPlateau().genererStructureAge1(); Permet de generer la tableau statique (dim 2) pour la structure des cartes

    //p.selectionDesBatiments(); Uniquement si la gen de l'age I a ete effectue

    //cout << p.getPlateau(); //afficher les merveilles et les batiments qu'il y a sur le plateau de jeu

    return 0;
}

