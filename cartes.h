#ifndef CARTES_H
#define CARTES_H

#include <string>
#include <iostream>
#include "utils.h"
#define NMAX 10


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
    Carte(const Carte& other)
        : nom(other.nom), coutRessources(new Ressources[other.nbCoutMax]), nbCout(other.nbCout),
        nbCoutMax(other.nbCoutMax), nbPointVictoire(other.nbPointVictoire) {
        for (unsigned int i=0; i<other.nbCout; i++) coutRessources[i]=other.getCoutRessources()[i];
    }
    Carte& operator=(const Carte& other);
    virtual ~Carte() {delete [] coutRessources;}

    //getters
    const std::string getNom() const {return nom;}
    const unsigned int getNbPointVictoire() const {return nbPointVictoire;}
    const Ressources* const getCoutRessources() const {return coutRessources;}
    const unsigned int getNbCout() const {return nbCout;}
    const unsigned int getNbCoutMax() const {return nbCoutMax;}

    void ajouterCoutRessources(Ressources r);
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
    bool choixDefausse;
    TypeBatiment batimentSacagee;
    bool choixJeton;

public:
    Merveille() : active(false), rejouer(false), produitRessources(nullptr), nbProd(0), nbProdMax(0), nbPointsCombat(0), nbPiecesRapportees(0), nbPiecesSacagees(0), batimentSacagee(TypeBatiment::undefined), choixDefausse(false), choixJeton(false) {}
    Merveille(std::string m, bool act=false, bool rej=false, unsigned int ptv=0,
              unsigned int ptc = 0, unsigned int pieceR = 0, unsigned int pieceS = 0, unsigned int nbRes=0, TypeBatiment bc=TypeBatiment::undefined, bool cd=false, bool cj=false) :
        Carte(m, ptv), active(act), rejouer(rej), nbProd(0),
        nbProdMax(nbRes), nbPointsCombat(ptc), nbPiecesRapportees(pieceR), nbPiecesSacagees(pieceS), produitRessources(new Ressources[nbRes]), batimentSacagee(bc), choixDefausse(cd), choixJeton(cj) {}
    Merveille(const Merveille& mer);
    Merveille& operator=(const Merveille& mer);
    virtual ~Merveille() {delete[] produitRessources;}

    //getters
    const unsigned int getNbPointsCombat() const {return nbPointsCombat;}
    const unsigned int getNbPiecesRapportees() const {return nbPiecesRapportees;}
    const unsigned int getNbPiecesSacagees() const {return nbPiecesSacagees;}
    const bool getRejouer() const {return rejouer;}
    const bool getActive() const {return active;}
    const unsigned int getNbProd() const {return nbProd;}
    const unsigned int getNbProdMax() const {return nbProdMax;}
    const Ressources* getProduitRessources() const {return produitRessources;}
    bool getChoixDefausse() const {return choixDefausse;}
    bool getChoixJeton() const {return choixJeton;}
    TypeBatiment getBatimentSacagee() const {return batimentSacagee;}

    //setter
    void setActive(bool b) {active=b;}
    void setChoixDefausse(bool cd) {choixDefausse=cd;}
    void setChoixJeton(bool cj) {choixJeton=cj;}

    void ajouterProduitRessources(Ressources r);
    //void choisirBatimentADefausser();
};

std::ostream& operator<<(std::ostream& f, const Merveille& m);


class Batiment : public Carte {
private:
    unsigned int coutPieces; //nb de pieces necessaires pour construire le bâtiment
    std::string coutChainage;
    std::string symboleChainage;
    bool faceCachee;
public:
    Batiment()=default;
    Batiment(std::string m, unsigned int cp, std::string cchain, std::string schain, bool fc, unsigned int ptv=0) :
        Carte(m, ptv), coutPieces(cp), coutChainage(cchain),
        symboleChainage(schain), faceCachee(fc) {}
    Batiment(const Batiment& bat);
    virtual Batiment& operator=(const Batiment& bat);
    virtual ~Batiment()=default;

    //getters
    unsigned int getCoutPieces() const {return coutPieces;}
    std::string getCoutChainage() const {return coutChainage;}
    std::string getSymboleChainage() const {return symboleChainage;}
    bool getFaceCachee() const {return faceCachee;}

    virtual Ressources getRessourceProduite() const {return Ressources::undefined;}
    virtual void afficher(std::ostream& f) const; //Virtual pour le polymorphisme
    virtual std::string getType() const=0;
    virtual SymboleScientifique getSymbole() const {return SymboleScientifique::undefined;}
    virtual unsigned int getNbPointsCombats() const {return 0;}
    virtual Ressources* getRessourcesDisponibles() const {return new Ressources(Ressources::undefined);}
    virtual unsigned int getNbRessourcesDisponibles() const {return 0;}
    virtual Ressources* getRessourcesStockees() const {return new Ressources(Ressources::undefined);}
    virtual unsigned int getNbRessourcesStockees() const {return 0;}
};

std::ostream& operator<<(std::ostream& f, const Batiment& bat);


class BatimentRessource : public Batiment {
    Ressources ressourceProduite;
    unsigned int nbRessourcesProduites;
public:
    BatimentRessource(const std::string& nom, unsigned int cp, const std::string& cchain, std::string schain, bool fc, Ressources res, unsigned int nbRes)
        : Batiment(nom, cp, cchain, schain, fc), ressourceProduite(res), nbRessourcesProduites(nbRes) {}
    BatimentRessource(const BatimentRessource& other);
    BatimentRessource& operator=(const BatimentRessource& other);
    BatimentRessource(): Batiment(), ressourceProduite(Ressources::undefined), nbRessourcesProduites(0) {}
    virtual ~BatimentRessource()=default;

    //getters
    Ressources getRessourceProduite() const {return ressourceProduite;}
    unsigned int getNbRessourcesProduites() const {return nbRessourcesProduites;}

    void afficher(std::ostream& f) const;
    virtual std::string getType() const {return "BatimentRessource";}
    std::string getTypeRessource() const {
        if (ressourceProduite==Ressources::papyrus || ressourceProduite==Ressources::verre) return "RessourcePrimaire";
        else return "RessourceManufacturee";
    }
};

std::ostream& operator<<(std::ostream& f, const BatimentRessource& bat);


class BatimentCivil : public Batiment { //Une classe fille sans nouveaux attributs
public:
    BatimentCivil(const std::string& nom, unsigned int cp, const std::string& cchain, std::string schain, bool fc, unsigned int ptv)
        : Batiment(nom, cp, cchain, schain, fc, ptv) {}
    BatimentCivil(const BatimentCivil& other);
    BatimentCivil& operator=(const BatimentCivil& other);
    virtual ~BatimentCivil()=default;

    void afficher(std::ostream& f) const;
    virtual std::string getType() const {return "BatimentCivil";}
};


class BatimentScientifique : public Batiment {
    SymboleScientifique symbole;
public:
    BatimentScientifique(const std::string& nom, unsigned int cp, const std::string& cchain, std::string schain, bool fc, SymboleScientifique symb, unsigned int ptv=0)
        : Batiment(nom, cp, cchain, schain, fc, ptv), symbole(symb) {}
    BatimentScientifique(const BatimentScientifique& other);
    BatimentScientifique& operator=(const BatimentScientifique& other);
    virtual ~BatimentScientifique()=default;

    //getters
    SymboleScientifique getSymbole() const {return symbole;}

    void afficher(std::ostream& f) const;
    virtual std::string getType() const {return "BatimentScientifique";}
};


class BatimentCommercial : public Batiment {
    unsigned int piecesRapportees;
    TypeBatiment typePourGainPieces; //Cette attribut sera utile pour l'age 3 uniquement
    Ressources* ressourcesStockees; //Liste des ressources pour lesquelles il faudra payer une pieces (tailleListe <= 2)
    unsigned int nbRessourcesStockees;
    Ressources* ressourcesDisponibles; //Liste des ressources parmis lesquels un seul peut être chosie (il faudra egalement rajouter cette attribut aux merveilles dans le futur)
    unsigned int nbRessourcesDisponibles;
public:
    BatimentCommercial(const std::string& nom, unsigned int cp, const std::string& cchain, std::string schain, bool fc, unsigned int pR, TypeBatiment type)
        : Batiment(nom, cp, cchain, schain, fc), nbRessourcesStockees(0), nbRessourcesDisponibles(0),
        ressourcesStockees(new Ressources[3]), ressourcesDisponibles(new Ressources[3]),
        typePourGainPieces(type), piecesRapportees(pR) {}
    BatimentCommercial(const BatimentCommercial& other);
    BatimentCommercial& operator=(const BatimentCommercial& other);
    virtual ~BatimentCommercial() {delete[] ressourcesStockees, delete[] ressourcesDisponibles;}

    //getters
    unsigned int getPiecesRapportees() const {return piecesRapportees;}
    unsigned int getNbRessourcesStockees() const {return nbRessourcesStockees;}
    unsigned int getNbRessourcesDisponibles() const {return nbRessourcesDisponibles;}
    TypeBatiment getTypePourGainPiece() const {return typePourGainPieces;}
    Ressources* getRessourcesDisponibles() const {return ressourcesDisponibles;}
    Ressources* getRessourcesStockees() const {return ressourcesStockees;}

    //setter
    void setTypePourGainPieces(TypeBatiment t) {typePourGainPieces=t;}

    void AjouterRessourcesStockees(Ressources res);
    void AjouterRessourcesDisponibles(Ressources res);
    void afficher(std::ostream& f) const;
    virtual std::string getType() const {return "BatimentCommercial";}
};


class BatimentMilitaire : public Batiment {
    unsigned int pointsCombats;
public:
    BatimentMilitaire(const std::string& nom, unsigned int cp, const std::string& cchain, std::string schain, bool fc, unsigned int ptc)
        : Batiment(nom, cp, cchain, schain, fc), pointsCombats(ptc) {}
    BatimentMilitaire(const BatimentMilitaire& other);
    BatimentMilitaire& operator=(const BatimentMilitaire& other);
    virtual ~BatimentMilitaire()=default;

    //getters
    unsigned int getNbPointsCombats() const {return pointsCombats;}

    void afficher(std::ostream& f) const;
    virtual std::string getType() const {return "BatimentMilitaire";}
};


class BatimentGuilde : public Batiment {
    TypeBatiment typePourAvantages;
public:
    BatimentGuilde(const std::string& nom, unsigned int cp, const std::string& cchain, std::string schain, bool fc, unsigned int ptc, TypeBatiment type)
        : Batiment(nom, cp, cchain, schain, fc), typePourAvantages(type) {}
    virtual ~BatimentGuilde() = default;
    //getters
    TypeBatiment getTypePourAvantages() const {return typePourAvantages;}

    //setters
    void setTypePourAvantages(TypeBatiment t) {typePourAvantages=t;}

    void afficher(std::ostream& f) const;
    virtual std::string getType() const {return "BatimentGuilde";}
};

#endif // CARTES_H
