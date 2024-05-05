#include "joueur.h"
#include "plateauJeu.h"

using namespace std;


void Joueur::ajouterMerveille(Merveille& mer) {
    merveilles[nbMerveilles++] = mer;
}


ostream& operator<<(ostream& f, const Joueur& j) {
    f << "Joueur : " << j.getPrenom() << " " << j.getNom();
    return f;
}
