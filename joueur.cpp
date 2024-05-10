#include "joueur.h"
#include "plateauJeu.h"

using namespace std;


void Joueur::ajouterMerveille(const Merveille& mer) {
    merveilles[nbMerveilles++]=mer; //Pas necessaire pour l'instant de gerer le nombre de merveilles du joueur (tjs = 4)
}


void Joueur::ajouterBatiment(Batiment* bat) {
    std::cout << "youhou" << std::endl;
    cite[nbBatiments++]=bat; //Pas necessaire pour l'instant de gerer le nombre de merveilles du joueur (tjs = 4)
}


ostream& operator<<(ostream& f, const Joueur& j) {
    f << "===Joueur : " << j.getPrenom() << " " << j.getNom() << "===" << endl;
    f << "Merveilles dans sa cite : " << endl;
    for (unsigned int i=0; i<j.getNbMerveilles(); i++) f << j.getMerveilles()[i];
    f << "Batiments dans sa cite : " << endl;
    for (unsigned int i=0; i<j.getNbBatiments(); i++) f << *(j.getCite()[i]);
    return f;
}
