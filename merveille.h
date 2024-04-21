#ifndef MERVEILLE_H
#define MERVEILLE_H

#include <iostream>
#include <string>
#include <map>

using namespace std;

enum ressource {bois, brique, pierre, papyrus, flacon};

class Merveille {
    string nom;
    map<ressource, unsigned int> coutRessources;
    bool activee=false, rejouer=false;
    unsigned int nbPointVictoire=0, nbPointCombat=0, nbPieces=0, nbPieceDetruites=0;
public:
    Merveille(const string& n, unsigned int pv=0, unsigned int pc=0, unsigned int pieces=0, unsigned int piecesDetruites=0)
        : nom(n), nbPointVictoire(pv), nbPointCombat(pc), nbPieces(pieces), nbPieceDetruites(piecesDetruites) {}
    const string getNom() const {return nom;}
    const unsigned int getNbPointVictoire() const {return nbPointVictoire;}
    const unsigned int getNbPointCombat() const {return nbPointCombat;}
    const unsigned int getNbPieces() const {return nbPieces;}
    const unsigned int getNbPieceDetruites() const {return nbPieceDetruites;}
    const map<ressource, unsigned int>& getCoutRessources() const {return  coutRessources;}
    void ajoutCoutRessources(ressource r, unsigned int nb) {coutRessources.insert(pair(r, nb));}
};

ostream& operator<<(ostream& f, const Merveille& m);

#endif // MERVEILLE_H
