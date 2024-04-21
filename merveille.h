#ifndef MERVEILLE_H
#define MERVEILLE_H

#include <iostream>
#include <string>

using namespace std;

class Merveille {
    string nom;
public:
    Merveille(const string& n) : nom(n) {}
    const string getNom() const {return nom;}
};

ostream& operator<<(ostream& f, const Merveille& m);

#endif // MERVEILLE_H
