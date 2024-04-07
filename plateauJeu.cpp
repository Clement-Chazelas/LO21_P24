#include <iostream>
#include "joueur.h"
#include "plateauJeu.h"
#include "batiment.h"
#include "jetonProgres.h"

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