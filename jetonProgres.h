#ifndef LO21_P24_JETONPROGRES_H
#define LO21_P24_JETONPROGRES_H
#include "joueur.h"
#include "plateauJeu.h"
#include "batiment.h"
#include <iostream>
#include <string>

class JetonProgres{
private:
    std::string nomJeton;
    std::string effet;
public:
    JetonProgres(std::string n, std::string e) : nomJeton(std::move(n)), effet(std::move(e)) {};
    std::string getNomJeton() const {return nomJeton;}
    std::string getEffetJeton() const {return effet;}
};

#endif //LO21_P24_JETONPROGRES_H

