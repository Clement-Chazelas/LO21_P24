#ifndef MERVEILLES_H_INCLUDED
#define MERVEILLES_H_INCLUDED
#include <string>
#include <iostream>
#define NMAX 10

enum class Ressources {bois, pierre, argile, verre, papyrus};

class Carte {
protected:
    std::string nom; //nom de la carte
    Ressources* coutRessources; //liste des ressources necessaires pour construire la merveille
    unsigned int nbCout, nbCoutMax; //permet de controler la liste précédente
    unsigned int nbPointVictoire; //nb de points victoire que la carte rapporte une fois construite
public:
    Carte() : nom("unknown"), coutRessources(new Ressources[NMAX]), nbCout(0), nbCoutMax(NMAX), nbPointVictoire(0) {}
    Carte(std::string m, unsigned int ptv=0) : nom(m), coutRessources(new Ressources[NMAX]),
        nbCout(0), nbCoutMax(NMAX), nbPointVictoire(ptv) {}
    void ajouterCoutRessources(Ressources r);
    ~Carte() {delete [] coutRessources;}
    const std::string getNom() const {return nom;}
    const unsigned int getNbPointVictoire() const {return nbPointVictoire;}
    const Ressources* const getCoutRessources() const {return coutRessources;}
    const unsigned int getNbCout() const {return nbCout;}
};

class Merveille : public Carte {
private:
    bool active; //test si la merveille est activée ou non
    bool rejouer; //permet d'indiquer si la merveille possède l'effet rejouer
    Ressources* produitRessources; //liste des ressources produites par la merveille
    unsigned int nbProd, nbProdMax; //permet de controler la liste précédente
    unsigned int nbPointsCombat; //nb de points combats que la merveille rapporte une fois activée
    unsigned int nbPiecesRapportees; //nb de pièces que la merveille rapporte quand elle est activée
    unsigned int nbPiecesSacagees; //nb de piece perdues par l'adversaire quand elle est activée
public:
    Merveille()=default;
    Merveille(std::string m, bool act=false, bool rej=false, unsigned int ptv=0,
              unsigned int ptc = 0, unsigned int pieceR = 0, unsigned int pieceS = 0) :
                  Carte(m, ptv), active(act), rejouer(rej), produitRessources(nullptr), nbProd(0),
        nbProdMax(NMAX), nbPointsCombat(ptc), nbPiecesRapportees(pieceR), nbPiecesSacagees(pieceS){}
    Merveille(const Merveille& mer);
    Merveille& operator=(const Merveille& mer);
    void ajouterProduitRessources(Ressources r);
    ~Merveille() {delete[] produitRessources;}
    const unsigned int getNbPointsCombat() const {return nbPointsCombat;}
    const unsigned int getNbPiecesRapportees() const {return nbPiecesRapportees;}
    const unsigned int getNbPiecesSacagees() const {return nbPiecesSacagees;}
    const bool getRejouer() const {return rejouer;}
    const bool getActive() const {return active;}
    const unsigned int getNbProd() const {return nbProd;}
    const unsigned int getNbProdMax() const {return nbProdMax;}
    const Ressources* getProduitRessources() const {return produitRessources;}
    choisirBatimentADefausser();
    saccagerRessourceAdverse();
};

std::ostream& operator<<(std::ostream& f, const Merveille& m);


class Batiment : public Carte {
private:
    unsigned int coutPieces; //nb de pieces necessaires pour construire le bâtiment
    std::string coutChainage;
    std::string symboleChainage;
    bool facecachee;
public:
    Batiment()=default;
    Batiment(std::string m, unsigned int cp, std::string cchain, std::string schain, bool fc, unsigned int ptv=0) :
                 Carte(m, ptv), coutPieces(cp), coutChainage(cchain),
                 symboleChainage(schain), facecachee(fc) {}
    ~Batiment()=default;
};

#endif
