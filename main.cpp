#include <iostream>
#include "joueur.h"
#include "partie.h"
#include "cartes.h"

using namespace std;

int main()
{
    Partie p("Ducasse", "Agathe", "Chazelas", "Clement");


    Merveille m1("Les Pyramides");
    m1.ajouterCoutRessources(Ressources::pierre);
    m1.ajouterCoutRessources(Ressources::pierre);
    m1.ajouterCoutRessources(Ressources::pierre);
    m1.ajouterCoutRessources(Ressources::papyrus);


    Merveille m2("La statue de Zeus", 3, 1);
    m2.ajouterCoutRessources(Ressources::pierre);
    m2.ajouterCoutRessources(Ressources::bois);
    m2.ajouterCoutRessources(Ressources::argile);
    m2.ajouterCoutRessources(Ressources::papyrus);
    m2.ajouterCoutRessources(Ressources::papyrus);

    cout << p << endl;
    cout << m1 << endl;
    cout << m2 << endl;
    return 0;
}
