#include "merveilles.h""
#include <string>
#include <iostream>
using namespace std;

void Carte::ajouterCoutRessources(Ressources& r){
    if nbCout >= nbCoutMax {
        Ressources* newlist = new Ressources[nbCoutMax+5];
        for (unsigned int i = 0; i<nbCout; i++)
            newlist[i] = CoutRessources[i];
        Ressources* old = CoutRessources; CoutRessources = newlist; delete [] old;
        nbCoutMax += 5;
    }
    CoutRessources[nbCout++] = r;
}

void Merveille::ajouterProduitRessources(Ressources& r){
    if nbProd >= nbProdMax {
        Ressources* newlist = new Ressources[nbProdMax+5];
        for (unsigned int i = 0; i<nbCout; i++)
            newlist[i] = ProduitRessources[i];
        Ressources* old = ProduitRessources; ProduitRessources = newlist; delete [] old;
        nbProdMax += 5;
    }
    ProduitRessources[nbProd++] = r;
}
