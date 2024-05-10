#ifndef LO21_P24_PLATEAUJEU_H
#define LO21_P24_PLATEAUJEU_H
#include <iostream>
#include "cartes.h"
#include "jetonProgres.h"
#include "jetonMilitaire.h"


class PlateauDeJeu {
private:
    Batiment** defausse;
    Batiment** tab; //Les batiments sont de tailles differents => il faut passer par un tableau de pointeur
    Batiment* structure[7][13];
    JetonProgres* piocheJeton;
    JetonProgres* plateauJeton;
    Merveille* selectionMerveille;
    size_t nb_batiment_plateau;
    size_t nb_jeton_pioche;
    size_t nb_jeton_plateau;
    size_t nb_defausse;
    size_t nb_max_defausse;
    size_t nb_merveille_plateau;
    int emplacementPionMilitaire;
public:
    PlateauDeJeu(size_t c, size_t pio, size_t pla);
    ~PlateauDeJeu() {delete[] defausse; delete[] tab; delete[] piocheJeton; delete[] plateauJeton; delete[] selectionMerveille;}

    //getters
    Batiment** getTab() const {return tab;}
    Batiment** getDispositionCarte() const {return tab;}
    JetonProgres* getJetonProgresPioche() const {return piocheJeton;}
    JetonProgres* getJetonProgresPlateau() const {return plateauJeton;}
    unsigned int getNb_merveille_plateau() const {return nb_merveille_plateau;}
    unsigned int getNb_batiment_plateau() const {return nb_batiment_plateau;}
    Merveille* getSelectionMerveille() const {return selectionMerveille;}
    Batiment* getDefausse() {return *defausse;}

    //setters
    void setDispositionCartes(size_t i);
    void setJetonProgresPioche(size_t i);
    void setJetonProgresPlateau(size_t i);
    void setDefausse(Batiment& bat);      //Défausser
    void setPionMilitaire(int i) {emplacementPionMilitaire += i ;if(emplacementPionMilitaire >= 10 || emplacementPionMilitaire <= -10){/*DECLENCHER_FIN_PARTIE*/};}     //Remplacerr le déclenchement par la méthode de fin

    //Pour les merveilles
    Merveille prendreMerveillePlateau(size_t i);
    Merveille choisirMerveille(bool j2=false);
    void melangerMerveilles();
    void ajouterMerveillePlateau(Merveille& mer);

    //Pour les batiments
    void prendreBatimentPlateau(size_t i);
    void ajouterBatimentPlateau(Batiment* bat);
    Batiment* piocher(int i);
    void melangerBatiments();
    void genererStructureAge1();
    void afficherStructureAge1();
    void afficherSelectionnableAge1();
    Batiment* choisirBatiment(bool j2=false);

    //Pour les jetons
    void prendreJetonPioche(size_t i);
    void prendreJetonPlateau(size_t i);
};

std::ostream& operator<<(std::ostream& f, const PlateauDeJeu& pla);

#endif //LO21_P24_PLATEAUJEU_H
