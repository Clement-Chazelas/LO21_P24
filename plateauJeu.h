#ifndef LO21_P24_PLATEAUJEU_H
#define LO21_P24_PLATEAUJEU_H
#include <iostream>
#include "joueur.h"
#include "batiment.h"
#include "jetonProgres.h"

class PlateauDeJeu {
private:
    Batiment* tab;
    Batiment** defausse;
    JetonProgres* piocheJeton;
    JetonProgres* plateauJeton;
    size_t nb_cartes;
    size_t nb_jeton_pioche;
    size_t nb_jeton_plateau;
    size_t nb_defausse;
    size_t nb_max_defausse;
public:
    PlateauDeJeu(size_t c, size_t pio, size_t pla) : nb_cartes(c), nb_jeton_pioche(pio), nb_jeton_plateau(pla), nb_defausse(0), nb_max_defausse(10), defausse(new Batiment*[nb_max_defausse]) {};     //Rajouter l'initialisation avec un fichier csv
    ~PlateauDeJeu() {delete[] defausse; nb_jeton_pioche = 0; nb_jeton_plateau = 0; nb_cartes =0;}
    void setDispositionCartes(size_t i);
    void setJetonProgresPioche(size_t i);
    void setJetonProgresPlateau(size_t i);
    Batiment* getDispositionCarte() {return tab;}
    JetonProgres* getJetonProgresPioche() {return piocheJeton;}
    JetonProgres* getJetonProgresPlateau() {return plateauJeton;}
    void prendreCarte(size_t i);
    void prendreJetonPioche(size_t i);
    void prendreJetonPlateau(size_t i);
    Batiment * piocher(int i);
    void setDefausse(Batiment& bat);      //Défausser
    Batiment* getDefausse() {return *defausse;}
};
#endif //LO21_P24_PLATEAUJEU_H
