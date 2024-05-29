#ifndef PLATEAUJEU_H
#define PLATEAUJEU_H

#include <iostream>
#include <vector>
#include "cartes.h"
#include "jetonProgres.h"
#include "jetonMilitaire.h"

// Forward declaration
class Joueur;

class PlateauDeJeu {
private:
    Batiment** defausse;
    Batiment** tab; // Les batiments sont de tailles differents => il faut passer par un tableau de pointeur
    Batiment* structure[8][13];
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
    JetonMilitaire* plateauMilitaire;
public:
    PlateauDeJeu(size_t c, size_t pio, size_t pla);
    ~PlateauDeJeu() {delete[] defausse; delete[] tab; delete[] piocheJeton; delete[] plateauJeton; delete[] selectionMerveille; delete[] plateauMilitaire;}

    // getters
    Batiment** getTab() const { return tab; }
    Batiment** getDispositionCarte() const { return tab; }
    JetonProgres* getJetonProgresPioche() const { return piocheJeton; }
    JetonProgres* getJetonProgresPlateau() const { return plateauJeton; }
    unsigned int getNb_merveille_plateau() const { return nb_merveille_plateau; }
    unsigned int getNb_batiment_plateau() const { return nb_batiment_plateau; }
    Merveille* getSelectionMerveille() const { return selectionMerveille; }
    Batiment* getDefausse() { return *defausse; }
    int getEmplacementPionMilitaire() const { return emplacementPionMilitaire; }
    unsigned int getNb_jeton_pioche() const {return nb_jeton_pioche;}
    unsigned int getNb_jeton_plateau() const {return nb_jeton_plateau;}
    JetonMilitaire getZonePlateauMilitaire(unsigned int i) {return plateauMilitaire[i];}

    // setters
    void setDispositionCartes(size_t i);
    void setJetonProgresPioche(size_t i);
    void setJetonProgresPlateau(size_t i);
    void setDefausse(Batiment& bat); // Défausser
    void setPionMilitaire(int i) { emplacementPionMilitaire += i; }
    void setZonePlateauMilitaire(JetonMilitaire& zone, unsigned int i);

    // Pour les merveilles
    Merveille prendreMerveillePlateau(size_t i);
    Merveille choisirMerveille(bool j2 = false);
    void melangerMerveilles();
    void ajouterMerveillePlateau(Merveille& mer);

    // Pour les batiments
    void prendreBatimentPlateau(size_t i);
    void ajouterBatimentPlateau(Batiment* bat);
    Batiment* piocher(int i);
    void melangerBatiments();
    void genererStructureAge1();
    void genererStructureAge2();
    void genererStructureAge3();
    void afficherStructure();
    void afficherSelectionnable();
    Batiment* choisirBatiment(bool j2 = false);

    // Pour les jetons
    void genererJetons();
    void prendreJetonDansPioche(Joueur& joueur);
    void prendreJetonDansPlateau(Joueur& joueur);
};

std::ostream& operator<<(std::ostream& f, const PlateauDeJeu& pla);

#endif // PLATEAUJEU_H
