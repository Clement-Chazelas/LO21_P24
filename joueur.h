#ifndef JOUEUR_H
#define JOUEUR_H

#include <iostream>
#include <string>
#include <vector>
#include "cartes.h"

// Forward declaration
class PlateauDeJeu;
class JetonProgres;

class Joueur {
private:
    Merveille* merveilles;
    std::string nom;
    std::string prenom;
    bool ia;
    unsigned int nbPieces;
    Batiment** cite;
    unsigned int nbBatiments;
    std::vector<JetonProgres> jetonsProgres;
    unsigned int nbMerveilles;
public:
    Joueur(std::string n, std::string p, bool i=false, unsigned int m=07)
        : merveilles(new Merveille[4]), cite(new Batiment*[30]), nbBatiments(0), nom(n), prenom(p), ia(i), nbPieces(m), nbMerveilles(0) {}
    virtual ~Joueur() { delete[] merveilles; delete [] cite;}
    Joueur(const Joueur& j) = delete;

    // getters
    std::string getNom() const { return nom; }
    std::string getPrenom() const { return prenom; }
    bool robot() const {return ia;} //getter de l'attribut ia
    unsigned int getnbPieces() const { return nbPieces; }
    unsigned int getNbMerveilles() const { return nbMerveilles; }
    const Merveille* const getMerveilles() const { return merveilles; }
    unsigned int getNbBatiments() const { return nbBatiments; }
    Batiment** getCite() const { return cite; }
    std::vector<JetonProgres> getJetonsProgres() {return jetonsProgres;}
    std::vector<JetonProgres> getJetonsProgres() const {return jetonsProgres;}


    //setters
    void setNbBatiments(unsigned int val) {nbBatiments = val;}
    void setElementCite(Batiment* bat, unsigned int position) {cite[position] = bat;}

    void gainPieces(unsigned int n) { nbPieces += n; }
    void pertePieces(unsigned int n) { if (n > nbPieces) nbPieces = 0; else nbPieces -= n; }
    void ajouterMerveille(const Merveille& mer);
    void ajouterBatiment(Batiment* bat);
    unsigned int gainDefausse();
    unsigned int coutAchat(Batiment* bat, const Joueur& adversaire);
    const unsigned int compterPointsVictoires(const PlateauDeJeu& pla, const bool j2 = false) const;
    bool choisirMerveilleInactive();
    unsigned int checkVictoireScientifique() const;
    void saccagerRessourceAdverse(const Merveille& mer, Joueur& adversaire);
    void ajouterJeton(const JetonProgres& jeton);
    void afficherJetons() const;
};

std::ostream& operator<<(std::ostream& f, const Joueur& j);

#endif // JOUEUR_H
