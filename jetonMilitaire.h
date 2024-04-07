#ifndef LO21_P24_JETONMILITAIRE_H
#define LO21_P24_JETONMILITAIRE_H

#include <iostream>
#include <string>
#include "joueur.h"
#include "plateauJeu.h"

class JetonMilitaire{
private:
    int emplacement;
    int pertePiece;
    bool utilise;
public:
    JetonMilitaire(int e, int p) : emplacement(e), pertePiece(p), utilise(false) {}
    int getEmplacement() const {return emplacement;}
    int getPertePiece() const {return pertePiece;}
    bool getUtilise() const {return utilise;}
    void utiliserJeton(int i,Joueur& joueur) {
        if(!utilise && emplacement == i) {
            joueur.pertePieces(pertePiece);
            utilise = true;
        }
    }
};

#endif //LO21_P24_JETONMILITAIRE_H
