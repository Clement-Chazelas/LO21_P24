#include "partie.h"

Partie::Partie(const string& n_j1, const string& p_j1, const string& n_j2, const string& p_j2)
    : joueur1(Joueur(n_j1, p_j1)), joueur2(Joueur(n_j2, p_j2)) {}

ostream& operator<<(ostream& f, const Partie& p) {
    f << "Partie --> " << p.getJoueur1() << " VS " << p.getJoueur2();
    return f;
}
