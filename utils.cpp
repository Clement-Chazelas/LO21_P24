#include <stdio.h>
#include <iostream>
#include <random>
#include <set>
#include "utils.h"

using namespace std;

void viderBuffer() {
    int c;
    int count = 0; // Pour compter les caractères lus
    while ((c = getchar()) != '\n' && c != EOF) {
        cout << "Lu: " << static_cast<char>(c) << endl;
        count++;
    }
    cout << count << " caracteres lus et vides du buffer." << endl;
}

unsigned int min(unsigned int a, size_t b) {
    if (a<=b) return a;
    return b;
}

std::set<int> generateRdmSet(unsigned int max, unsigned int sizeSet, unsigned int min) { //Genere un ensemble de sizeSet entiers differents compris entre min et max
    if (sizeSet>max-min) throw "Impossible de generer un ensemble aleatoire avec une plage inferieur au nombre d'element"; //But : selectionner les cartes non utilisées
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);

    std::set<int> numbers; // Utiliser un ensemble pour garantir des valeurs uniques

    while (numbers.size() < sizeSet) {
        int num = dis(gen);
        numbers.insert(num);
    }
    return numbers;
}

TypeBatiment qStringToTypeBatiment(QString str) {
    if (str=="Ressource") return TypeBatiment::Ressource;
    else if (str=="Civil") return TypeBatiment::Civil;
    else if (str=="Scientifique") return TypeBatiment::Scientifique;
    else if (str=="Commercial") return TypeBatiment::Commercial;
    else if (str=="Militaire") return TypeBatiment::Militaire;
    else if (str=="Guilde") return TypeBatiment::Guilde;
    else if (str=="Merveille") return TypeBatiment::Merveille;
    else if (str=="Pieces") return TypeBatiment::Pieces;
    else if (str=="Primaire") return TypeBatiment::Primaire;
    else if (str=="Manufacturee") return TypeBatiment::Manufacturee;
    else return TypeBatiment::undefined;
}

Ressources qStringToRessource(QString str) {
    if (str=="Pierre") return Ressources::pierre;
    else if (str=="Argile") return Ressources::argile;
    else if (str=="Bois") return Ressources::bois;
    else if (str=="Papyrus") return Ressources::papyrus;
    else if (str=="Verre") return Ressources::verre;
    else throw "La ressource n'existe pas";
}

SymboleScientifique qStringToSymboleScientifique(QString str) {
    if (str=="Sphere armillaire") return SymboleScientifique::Sphere_armillaire;
    else if (str=="Balance") return SymboleScientifique::Balance;
    else if (str=="Cadran solaire") return SymboleScientifique::Cadran_solaire;
    else if (str=="Mortier") return SymboleScientifique::Mortier;
    else if (str=="Plomb") return SymboleScientifique::Plomb;
    else if (str=="Plume") return SymboleScientifique::Plume;
    else if (str=="Roue") return SymboleScientifique::Roue;
    else return SymboleScientifique::undefined;
}

string printRessource(const Ressources& r) {
    switch (r) {
    case Ressources::bois:
        return "Bois";
        break;
    case Ressources::pierre:
        return "Pierre";
        break;
    case Ressources::argile:
        return "Argile";
        break;
    case Ressources::papyrus:
        return "Papyrus";
        break;
    case Ressources::verre:
        return "Verre";
        break;
    }
    return "inexistant";
}

string printSymbole(const SymboleScientifique& s) {
    switch (s) {
    case SymboleScientifique::Sphere_armillaire:
        return "Sphere_armillaire";
        break;
    case SymboleScientifique::Balance:
        return "Balance";
        break;
    case SymboleScientifique::Cadran_solaire:
        return "Cadran_solaire";
        break;
    case SymboleScientifique::Mortier:
        return "Mortier";
        break;
    case SymboleScientifique::Plomb:
        return "Plomb";
        break;
    case SymboleScientifique::Plume:
        return "Plume";
        break;
    case SymboleScientifique::Roue:
        return "Roue";
        break;
    }
    return "inexistant";
}

string printTypeBatiment(const TypeBatiment& s) {
    switch (s) {
    case TypeBatiment::Ressource:
        return "Ressource";
        break;
    case TypeBatiment::Civil:
        return "Civil";
        break;
    case TypeBatiment::Scientifique:
        return "Scientifique";
        break;
    case TypeBatiment::Commercial:
        return "Commercial";
        break;
    case TypeBatiment::Militaire:
        return "Militaire";
        break;
    case TypeBatiment::Guilde:
        return "Guilde";
        break;
    case TypeBatiment::Merveille:
        return "Merveille";
        break;
    case TypeBatiment::Pieces:
        return "Pieces";
        break;
    case TypeBatiment::Primaire:
        return "Primaire";
        break;
    case TypeBatiment::Manufacturee:
        return "Manufacturee";
        break;
    }
    return "inexistant";
}

