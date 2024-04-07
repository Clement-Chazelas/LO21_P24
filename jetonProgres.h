#ifndef LO21_P24_JETONPROGRES_H
#define LO21_P24_JETONPROGRES_H
#include "joueur.h"
#include "plateauJeu.h"
#include "batiment.h"
#include <iostream>
#include <string>
#include <utility>

class JetonProgres{
private:
    std::string nomJeton;
    std::string effet;
public:
    JetonProgres(std::string n, std::string e) : nomJeton(std::move(n)), effet(std::move(e)) {};
    std::string getNomJeton() {return nomJeton;}
    std::string getEffetJeton() {return effet;}
};

#endif //LO21_P24_JETONPROGRES_H

