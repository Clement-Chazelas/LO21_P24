#include <iostream>
#include "joueur.h"

using namespace std;

ostream& operator<<(ostream& f, const Joueur& j) {
    f << "Joueur : " << j.getPrenom() << " " << j.getNom() << " avec " << j.getnbPieces() << " Pieces" << endl;
    return f;
}
