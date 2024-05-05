#ifndef LO21_P24_PLATEAUJEU_H
#define LO21_P24_PLATEAUJEU_H
#include <iostream>
#include "cartes.h"
#include "jetonProgres.h"
#include "jetonMilitaire.h"


class PlateauDeJeu {
private:
    Batiment** defausse;
    Batiment* tab;
    JetonProgres* piocheJeton;
    JetonProgres* plateauJeton;
    Merveille* selectionMerveille;
    size_t nb_cartes;
    size_t nb_jeton_pioche;
    size_t nb_jeton_plateau;
    size_t nb_defausse;
    size_t nb_max_defausse;
    size_t nb_merveille_plateau;
    int emplacementPionMilitaire;
public:
    PlateauDeJeu(size_t c, size_t pio, size_t pla);
    ~PlateauDeJeu() {delete[] defausse; delete[] tab; delete[] piocheJeton; delete[] plateauJeton; delete[] selectionMerveille;}
    void setDispositionCartes(size_t i);
    void setJetonProgresPioche(size_t i);
    void setJetonProgresPlateau(size_t i);
    Batiment* getDispositionCarte() const {return tab;}
    JetonProgres* getJetonProgresPioche() const {return piocheJeton;}
    JetonProgres* getJetonProgresPlateau() const {return plateauJeton;}
    unsigned int getNb_merveille_plateau() const {return nb_merveille_plateau;}
    Merveille* getSelectionMerveille() const {return selectionMerveille;}
    void prendreCarte(size_t i);
    void prendreJetonPioche(size_t i);
    void prendreJetonPlateau(size_t i);
    Merveille prendreMerveillePlateau(size_t i);
    Batiment* piocher(int i);
    void setDefausse(Batiment& bat);      //Défausser
    Batiment* getDefausse() {return *defausse;}
    void ajouterMerveillePlateau(Merveille& mer);
    Merveille& choisirMerveille();
    void setPionMilitaire(int i) {emplacementPionMilitaire += i ;if(emplacementPionMilitaire >= 10 || emplacementPionMilitaire <= -10){/*DECLENCHER_FIN_PARTIE*/};}     //Remplacerr le déclenchement par la méthode de fin
};

std::ostream& operator<<(std::ostream& f, const PlateauDeJeu& pla);

#endif //LO21_P24_PLATEAUJEU_H

