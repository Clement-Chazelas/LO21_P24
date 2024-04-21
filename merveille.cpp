#include "merveille.h"

string printRessource(ressource r) {
    switch (r) {
    case bois:
        return "bois";
        break;
    case pierre:
        return "pierre";
        break;
    case brique:
        return "brique";
        break;
    case papyrus:
        return "papyrus";
        break;
    case flacon:
        return "flacon";
        break;
    }
}

ostream& operator<<(ostream& f, const Merveille& m) {
    f << "Merveille : " << m.getNom() << std::endl;
    f << "cout : ";
    map<ressource, unsigned int>::const_iterator it;
    for (it=m.getCoutRessources().begin(); it!=m.getCoutRessources().end(); it++) {
        f << "# " << printRessource(it->first) << " -> " << it->second << "    ";
    }
    if (m.getNbPointVictoire()!=0) {
        f << std::endl << "Cette merveille confere " << m.getNbPointVictoire() << " points de victoire";
    }
    if (m.getNbPointCombat()!=0) {
        f << std::endl << "Cette merveille confere " << m.getNbPointCombat() << " points de combat";
    }
    if (m.getNbPieces()!=0) {
        f << std::endl << "Cette merveille confere " << m.getNbPieces() << " pieces";
    }
    if (m.getNbPieceDetruites()!=0) {
        f << std::endl << "Cette merveille detruit " << m.getNbPointVictoire() << " pieces a l'adversaire";
    }
    return f << std::endl;
}
