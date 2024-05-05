#include <iostream>
#include "partie.h"
#include <string>
#include "utils.h"

using namespace std;

int main() {

    Partie p("Ducasse", "Agathe", "Chazelas", "Clement");
    cout << p << endl;

    p.genererHuitMerveilles(); //generation random parmis un csv

    cout << p.getPlateau(); //on affiche les merveilles qu'il y a dans le plateau de jeu
    // il faudra bien sur completer l'affichage du plateau au fur et a mesure

    return 0;
}

}

