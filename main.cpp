#include <iostream>
#include "joueur.h"
#include "merveille.h"

using namespace std;

int main()
{
    Joueur j("Chevalier", "Titouan");
    Merveille m("colisee");
    cout << j << endl;
    cout << m << endl;
    return 0;
}
