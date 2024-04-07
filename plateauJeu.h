#ifndef LO21_P24_PLATEAUJEU_H
#define LO21_P24_PLATEAUJEU_H
#include <iostream>

class PlateauDeJeu {
private:
    Carte* tab;
    jetonsProgresPioche* piocheJeton;
    jetonProgresPlateau* plateauJeton;
    size_t nb_cartes;
    size_t nb_jeton_pioche;
    size_t nb_jeton_plateau;
public:
    PlateauDeJeu(size_t c, size_t pio, size_t pla) : nb_cartes(c), nb_jeton_pioche(pio), nb_jeton_plateau(pla) {};     //Rajouter l'initialisation avec un fichier csv
    ~PlateauDeJeu() {; nb_jeton_pioche = 0; nb_jeton_plateau = 0; nb_cartes =0;}
    void setDispositionCartes(size_t i);
    void setJetonProgresPioche(size_t i);
    void setJetonProgresPlateau(size_t i);
    Carte getDispositionCarte() {return tab;}
    jetonProgressPioche getJetonProgresPioche() {return piocheJeton;}
    jetonProgresPlateau getJetonProgresPlateau() {return plateauJeton;}
    void prendreCarte(size_t i);
    void prendreJetonPioche(size_t i);
    void prendreJetonPlateau(size_t i);
};
#endif //LO21_P24_PLATEAUJEU_H
