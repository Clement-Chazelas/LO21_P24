#ifndef PARTIE_H
#define PARTIE_H
#include <iostream>
#include "joueur.h"
#include "plateauJeu.h"

class Partie
{
    Joueur joueur1;
    Joueur joueur2;
    PlateauDeJeu plateau;
    unsigned int age;
public:
    Partie(const std::string& n_j1, const std::string& p_j1, const std::string& n_j2, const std::string& p_j2);
    ~Partie()=default;

    //getters
    const Joueur& getJoueur1() const {return joueur1;}
    const Joueur& getJoueur2() const {return joueur2;}
    Joueur& getSetJoueur1() {return joueur1;}
    Joueur& getSetJoueur2() {return joueur2;}
    PlateauDeJeu& getSetPlateau() {return plateau;}
    const PlateauDeJeu& getPlateau() const {return plateau;}

    void genererHuitMerveilles();
    void genererAgeUn();
    void genererAgeDeux();
    void genererAgeTrois();
    void genererPlateauMilitaire();
    void afficherMerveillesRestantes(bool salve2=false) const;
    void selectionDesMerveilles();
    void selectionDesBatiments();
    void deplacerPionMilitaire(int i);
};

std::ostream& operator<<(std::ostream& f, const Partie& p);

#endif // PARTIE_H
