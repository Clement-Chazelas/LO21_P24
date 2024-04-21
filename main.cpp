#include <iostream>
#include "joueur.h"
#include "merveille.h"

using namespace std;

int main()
{
    Joueur j("Chevalier", "Titouan");
    Merveille m1("Les Pyramides", 9);
    m1.ajoutCoutRessources(pierre, 3);
    m1.ajoutCoutRessources(papyrus, 1);

    Merveille m2("La statue de Zeus", 3, 1);
    m2.ajoutCoutRessources(pierre, 1);
    m2.ajoutCoutRessources(bois, 1);
    m2.ajoutCoutRessources(brique, 1);
    m2.ajoutCoutRessources(papyrus, 2);

    cout << j << endl;
    cout << m1 << endl;
    cout << m2 << endl;
    return 0;
}
