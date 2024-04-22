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
    Partie(const string& n_j1, const string& p_j1, const string& n_j2, const string& p_j2);
    const Joueur& getJoueur1() const {return joueur1;}
    const Joueur& getJoueur2() const {return joueur2;}
};

ostream& operator<<(ostream& f, const Partie& p);

#endif // PARTIE_H
