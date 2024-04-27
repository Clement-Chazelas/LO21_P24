#ifndef MERVEILLES_H_INCLUDED
#define MERVEILLES_H_INCLUDED
#include <string>
#include <iostream>
#define NMAX 10
using namespace std;

enum class Ressources {bois, pierre, argile, minerai, verre, papyrus, tissu};

class Carte {
protected:
    string nom; //nom de la carte
    Ressources* coutRessources[NMAX]; //liste des ressources necessaires pour construire la merveille
    unsigned int nbCout, nbCoutMax; //permet de controler la liste précédente
    unsigned int pointsVictoire; //nb de points victoire que la carte rapporte une fois construite
    Carte ()
    Carte (string m, unsigned int ptv = 0): nom(m), coutRessources(nullptr),
    nbCout(0), nbCoutMax(NMAX), pointsVictoire(ptv){}
    void ajouterCoutRessources(Ressources& r);
    ~Carte() {delete [] coutRessources;}
};

class Merveille : public Carte {
private:
    bool active; //test si la merveille est activée ou non
    bool rejouer; //permet d'indiquer si la merveille possède l'effet rejouer
    Ressources* produitRessources[NMAX]; //liste des ressources produites par la merveille
    unsigned int nbProd, nbProdMax; //permet de controler la liste précédente
    unsigned int pointsCombats; //nb de points combats que la merveille rapporte une fois activée
    unsigned int piecesRapportee; //nb de pièces que la merveille rapporte quand elle est activée
    unsigned int piecesSacagees; //nb de piece perdues par l'adversaire quand elle est activée
    Merveille(string m, act = False, rej = False, unsigned int ptv = 0,
              unsigned int ptc = 0, unsigned int pieceR = 0, unsigned int pieceS = 0):
                  Carte(m, ptv), active(act), rejouer(rej), produitRessources(nullptr), nbProd(0),
                  nbProdMax(NMAX), pointsCombats(ptc), piecesRapportee(pieceR), piecesSacagees(pieceS){}
    void ajouterProduitRessources(Ressources& r);
    ~Merveille () {delete [] produitRessources;}
public:
    choisirBatimentADefausser();
    saccagerRessourceAdverse();
};

class Batiment : public Carte{
private:
    unsigned int coutPieces; //nb de pieces necessaires pour construire le bâtiment
    string coutChainage;
    string symboleChainage;
    bool facecachee;
    Batiment(string m, unsigned int cp, string cchain, string schain,
             bool fc, unsigned int ptv=0):
                 Carte(m, ptv), coutPieces(cp), coutChainage(cchain),
                 symboleChainage(schain), facecachee(fc) {}
    ~Batiment = default;
};


#endif
