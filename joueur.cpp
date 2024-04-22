#include <iostream>
#include "joueur.h"

using namespace std;

ostream& operator<<(ostream& f, const Joueur& j) {
    f << "Joueur : " << j.getPrenom() << " " << j.getNom();
    return f;
}

