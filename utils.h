#ifndef UTILS_H
#define UTILS_H

#include <set>
#include <QString>
#include <string>

enum class Ressources {bois, pierre, argile, verre, papyrus, undefined};
enum class TypeBatiment {Primaire, Manufacturee, Ressource, Civil, Scientifique, Commercial, Militaire, Guilde, Merveille, Pieces, undefined};
enum class SymboleScientifique {Sphere_armillaire, Balance, Cadran_solaire, Mortier, Plomb, Plume, Roue, undefined};

void viderBuffer();

unsigned int min(unsigned int a, size_t b);

std::set<int> generateRdmSet(unsigned int max, unsigned int sizeSet, unsigned int min=0);

TypeBatiment qStringToTypeBatiment(QString str);

Ressources qStringToRessource(QString str);

SymboleScientifique qStringToSymboleScientifique(QString str);

std::string printRessource(const Ressources& r);

std::string printSymbole(const SymboleScientifique& r);

std::string printTypeBatiment(const TypeBatiment& s);


#endif // UTILS_H
