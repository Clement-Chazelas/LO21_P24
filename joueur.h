#ifndef JOUEUR_H
#define JOUEUR_H
#include <iostream>
#include <string>
#include "jetonProgres.h"
#include "plateauJeu.h"
#include "batiment.h"


using namespace std;

class Joueur {
private:
    string nom;
    string prenom;
    unsigned int nbPieces;
    /*
    Batiment* cite=nullptr;
    JetonProgres* jetonsScientifiques=nullptr;
    Merveille* merveilles=nullptr;
    */
public:
    Joueur(string n, string p, unsigned int m=7) : nom(n), prenom(p), nbPieces(m) {}
    //~Joueur() {delete[] cite; delete[] jetonsScientifiques; delete[] merveilles;}
    Joueur(const Joueur& j)=delete;

    string getNom() const {return nom;}
    string getPrenom() const {return prenom;}
    unsigned int getnbPieces() const {return nbPieces;}

    void gainPieces(unsigned int n) {nbPieces+=n;}
    void pertePieces(unsigned int n) {if (n>nbPieces) nbPieces=0; else nbPieces-=n;}
};

ostream& operator<<(ostream& f, const Joueur& j);

#endif // JOUEUR_H
