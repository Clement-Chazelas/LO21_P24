#include <iostream>
#include "joueur.h"
#include "plateauJeu.h"

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
