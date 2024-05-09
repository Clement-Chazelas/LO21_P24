#ifndef UTILS_H
#define UTILS_H

#include <set>
#include <QString>
#include <string>

enum class Ressources {bois, pierre, argile, verre, papyrus};
enum class TypeBatiment {Ressource, Civil, Scientifique, Commercial, Militaire, undefined};
enum class SymboleScientifique {Sphere_armillaire, Balance, Cadran_solaire, Mortier, Plomb, Plume, Roue, undefined};

void viderBuffer();

unsigned int min(unsigned int a, size_t b);

std::set<int> generateRdmSet(unsigned int max, unsigned int sizeSet);

TypeBatiment qStringToTypeBatiment(QString str);

Ressources qStringToRessource(QString str);

SymboleScientifique qStringToSymboleScientifique(QString str);

std::string printRessource(const Ressources& r);

std::string printSymbole(const SymboleScientifique& r);

#endif // UTILS_H
