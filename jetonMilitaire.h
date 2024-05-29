#ifndef JETONMILITAIRE_H
#define JETONMILITAIRE_H

#include <iostream>
#include <string>

class JetonMilitaire{
private:
    int emplacement;
    int pertePiece;
    bool utilise;
public:
    JetonMilitaire(int e, int p) : emplacement(e), pertePiece(p), utilise(false) {}
    JetonMilitaire() : emplacement(0), pertePiece(0), utilise(false) {}
    int getEmplacement() const {return emplacement;}
    int getPertePiece() const {return pertePiece;}
    bool getUtilise() const {return utilise;}

    void setPertePiece(int qte) {pertePiece = qte;}
/*
    void utiliserJeton(int i, Joueur& joueur) {
        if(!utilise && emplacement == i) {
            joueur.pertePieces(pertePiece);
            utilise = true;
        }
    }
*/
};

#endif // JETONMILITAIRE_H
