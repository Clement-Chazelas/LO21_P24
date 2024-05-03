#include "cartes.h"
#include <string>
#include <iostream>

using namespace std;

void Carte::ajouterCoutRessources(Ressources r) {
    if (nbCout >= nbCoutMax) {
        Ressources* newlist = new Ressources[nbCoutMax+5];
        for (unsigned int i = 0; i<nbCout; i++)
            newlist[i] = coutRessources[i];
        Ressources* old=coutRessources; coutRessources=newlist; delete [] old;
        nbCoutMax += 5;
    }
    coutRessources[nbCout++] = r;
}


void Merveille::ajouterProduitRessources(Ressources r){
    if (nbProd >= nbProdMax) {
        Ressources* newlist = new Ressources[nbProdMax+5];
        for (unsigned int i = 0; i<nbCout; i++)
            newlist[i] = produitRessources[i];
        Ressources* old = produitRessources; produitRessources = newlist; delete [] old;
        nbProdMax += 5;
    }
    produitRessources[nbProd++] = r;
}


string printRessource(const Ressources& r) {
    switch (r) {
    case Ressources::bois:
        return "bois";
        break;
    case Ressources::pierre:
        return "pierre";
        break;
    case Ressources::argile:
        return "brique";
        break;
    case Ressources::papyrus:
        return "papyrus";
        break;
    case Ressources::verre:
        return "verre";
        break;
    }
}

ostream& operator<<(ostream& f, const Merveille& m) {
    f << "Merveille : " << m.getNom() << std::endl;
    f << "cout : ";
    for (unsigned int i=0; i<m.getNbCout(); i++) {
        f << "# " << printRessource(m.getCoutRessources()[i]) << "    ";
    }
    if (m.getNbPointVictoire()!=0) {
        f << std::endl << "Cette merveille confere " << m.getNbPointVictoire() << " points de victoire";
    }
    if (m.getNbPointsCombat()!=0) {
        f << std::endl << "Cette merveille confere " << m.getNbPointsCombat() << " points de combat";
    }
    if (m.getNbPiecesRapportees()!=0) {
        f << std::endl << "Cette merveille confere " << m.getNbPiecesRapportees() << " pieces";
    }
    if (m.getNbPiecesSacagees()!=0) {
        f << std::endl << "Cette merveille sacage " << m.getNbPiecesSacagees() << " pieces a l'adversaire";
    }
    return f << std::endl;
}

