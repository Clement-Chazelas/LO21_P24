#ifndef LO21_P24_PLATEAUJEU_H
#define LO21_P24_PLATEAUJEU_H
#include <iostream>
#include "joueur.h"
#include "batiment.h"
#include "jetonProgres.h"
#include "jetonMilitaire.h"


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
    int emplacementPionMilitaire;
public:
    PlateauDeJeu(size_t c, size_t pio, size_t pla) : nb_cartes(c), nb_jeton_pioche(pio), nb_jeton_plateau(pla), nb_defausse(0), nb_max_defausse(10), defausse(new Batiment*[nb_max_defausse]), emplacementPionMilitaire(0) {};     //Rajouter l'initialisation avec un fichier csv
    ~PlateauDeJeu() {delete[] defausse; nb_jeton_pioche = 0; nb_jeton_plateau = 0; nb_cartes =0;}
    void setDispositionCartes(size_t i);
    void setJetonProgresPioche(size_t i);
    void setJetonProgresPlateau(size_t i);
    Batiment* getDispositionCarte() const {return tab;}
    JetonProgres* getJetonProgresPioche() const {return piocheJeton;}
    JetonProgres* getJetonProgresPlateau() const {return plateauJeton;}
    void prendreCarte(size_t i);
    void prendreJetonPioche(size_t i);
    void prendreJetonPlateau(size_t i);
    Batiment * piocher(int i);
    void setDefausse(Batiment& bat);      //Défausser
    Batiment* getDefausse() {return *defausse;}
    void setPionMilitaire(int i) {emplacementPionMilitaire += i ;if(emplacementPionMilitaire >= 10 || emplacementPionMilitaire <= -10){DECLENCHER_FIN_PARTIE};}     //Remplacerr le déclenchement par la méthode de fin
};
#endif //LO21_P24_PLATEAUJEU_H
