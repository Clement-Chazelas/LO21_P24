#include "plateauJeu.h"
#include <stdio.h>
#include "utils.h"

using namespace std;

PlateauDeJeu::PlateauDeJeu(size_t c, size_t pio, size_t pla)
    : nb_cartes(c), nb_jeton_pioche(pio), nb_jeton_plateau(pla), nb_defausse(0), nb_max_defausse(10),
    defausse(new Batiment*[10]), tab(new Batiment[c]),
    piocheJeton(new JetonProgres[pio]), plateauJeton(new JetonProgres[pla]),
    selectionMerveille(new Merveille[8]), emplacementPionMilitaire(0), nb_merveille_plateau(0) {}  //Rajouter l'initialisation avec un fichier csv



void PlateauDeJeu::prendreCarte(size_t i) {
    if(i >= nb_cartes){
        throw "Erreur : cette carte n'est pas sur le plateau";
    }
    else{
        for(i; i < nb_cartes-1; i++){
            tab[i] = tab[i + 1];
        }
        nb_cartes--;
    }
}

void PlateauDeJeu::prendreJetonPioche(size_t i) {
    if(i >= nb_jeton_pioche){
        throw "Erreur : ce jeton n'est pas dans la pioche";
    }
    else{
        for(i; i < nb_jeton_pioche; i++){
            piocheJeton[i] = piocheJeton[i + 1];
        }
        nb_jeton_pioche--;
    }
}

void PlateauDeJeu::prendreJetonPlateau(size_t i) {
    if(i >= nb_jeton_plateau){
        throw "Erreur : ce jeton n'est pas sur le plateau";
    }
    else{
        for(i; i < nb_jeton_plateau; i++){
            plateauJeton[i] = plateauJeton[i + 1];
        }
        nb_jeton_plateau--;
    }
}


void PlateauDeJeu::ajouterMerveillePlateau(Merveille& mer) {
    selectionMerveille[nb_merveille_plateau++]=mer;
}


Merveille PlateauDeJeu::prendreMerveillePlateau(size_t i) {
    if(i >= nb_merveille_plateau || i>4){
        throw "Erreur : cette merveille n'est pas sur le plateau";
    }
    else{
        Merveille merveilleChoisie(selectionMerveille[i]);
        for(i; i < 4; i++){
            selectionMerveille[i] = selectionMerveille[i+1];
        }
        nb_merveille_plateau--;
        return merveilleChoisie;
    }
}


Merveille& PlateauDeJeu::choisirMerveille() {
    string merveilleChoisie;
    cin >> merveilleChoisie;
    viderBuffer();
    for (unsigned int i=0; i<min(4, nb_merveille_plateau); i++) {
        if (merveilleChoisie==selectionMerveille[i].getNom()) return selectionMerveille[i];
    }
    throw "La merveille choisie n'existe pas sur le plateau de jeu";
}

void PlateauDeJeu::setDefausse(Batiment& bat) {
    if( nb_defausse >= nb_max_defausse){
        Batiment** newdefausse = new Batiment*[nb_max_defausse*2];
        for(int i = 0; i < nb_defausse; i++){
            newdefausse[i] = defausse[i];
        }
        Batiment **old = defausse;
        defausse = newdefausse;
        nb_max_defausse*=2;
        delete[] old;
    }
    defausse[nb_defausse++] = &bat;
}


Batiment * PlateauDeJeu::piocher(int i) {
    if(i >= nb_defausse){
        throw "Erreur : cette carte n'est pas dans la pioche";
    }
    else{
        Batiment *bat = defausse[i];
        for(int j; j < nb_defausse; j++){
            defausse[j] = defausse[j + 1];
        }
        return bat;
    }
}


std::ostream& operator<<(std::ostream& f, const PlateauDeJeu& pla) { //affichage a completer avec les autres elements du plateau de jeu
    f << "Merveilles a selectionner : " << std::endl;
    for (unsigned int i=0; i<pla.getNb_merveille_plateau(); i++) f << pla.getSelectionMerveille()[i] << std::endl;
    return f;
}
