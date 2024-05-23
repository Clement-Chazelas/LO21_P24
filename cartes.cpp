#include "cartes.h"
#include <string.h>

using namespace std;

void Carte::ajouterCoutRessources(Ressources r) {
    if (nbCout >= nbCoutMax) {
        Ressources* newlist = new Ressources[nbCoutMax+5];
        for (unsigned int i = 0; i<nbCout; i++)
            newlist[i] = coutRessources[i];
        Ressources* old=coutRessources; coutRessources=newlist; delete [] old;
        nbCoutMax += 5;
    }
    coutRessources[nbCout++] = r;
}

Merveille::Merveille(const Merveille& mer) :
    Carte(mer), active(mer.getActive()), rejouer(mer.getRejouer()),
    produitRessources(new Ressources[mer.getNbProdMax()]), nbProd(mer.getNbProd()),
    nbProdMax(mer.getNbProdMax()), nbPointsCombat(mer.getNbPointsCombat()),
    nbPiecesRapportees(mer.getNbPiecesRapportees()), nbPiecesSacagees(mer.getNbPiecesSacagees()),
    batimentSacagee(mer.getBatimentSacagee()), choixDefausse(mer.getChoixDefausse()), choixJeton(mer.getChoixJeton()) {
    std::cout << "entree recopie" << std::endl;
    for (unsigned int i=0; i<nbCout; i++) coutRessources[i]=mer.getCoutRessources()[i];
    for (unsigned int i=0; i<nbProd; i++) produitRessources[i]=mer.getProduitRessources()[i];
}

Batiment::Batiment(const Batiment& bat) :
    Carte(bat), coutPieces(bat.getCoutPieces()), coutChainage(bat.getCoutChainage()),
    symboleChainage(bat.getSymboleChainage()), faceCachee(bat.getFaceCachee()) {}

BatimentRessource::BatimentRessource(const BatimentRessource& other) :
    Batiment(other), ressourceProduite(other.getRessourceProduite()), nbRessourcesProduites(other.getNbRessourcesProduites()) {}

BatimentCivil::BatimentCivil(const BatimentCivil& other) :
    Batiment(other) {}

BatimentScientifique::BatimentScientifique(const BatimentScientifique& other) :
    Batiment(other), symbole(other.getSymbole()) {}

BatimentCommercial::BatimentCommercial(const BatimentCommercial& other) :
    Batiment(other), piecesRapportees(other.getPiecesRapportees()), typePourGainPieces(other.getTypePourGainPiece()),
    nbRessourcesStockees(other.getNbRessourcesStockees()), nbRessourcesDisponibles(other.getNbRessourcesDisponibles()),
    ressourcesStockees(new Ressources[other.getNbRessourcesStockees()]), ressourcesDisponibles(new Ressources[other.getNbRessourcesDisponibles()]) {
    for (unsigned int i=0; i<nbRessourcesStockees; i++) ressourcesStockees[i]=other.getRessourcesStockees()[i];
    for (unsigned int i=0; i<nbRessourcesDisponibles; i++) ressourcesDisponibles[i]=other.getRessourcesDisponibles()[i];
}

BatimentMilitaire::BatimentMilitaire(const BatimentMilitaire& other) :
    Batiment(other), pointsCombats(other.getNbPointsCombats()) {}


Carte& Carte::operator=(const Carte& other) {
    if (this!=&other) {
        nom=other.getNom();
        nbCout=other.getNbCout();
        nbCoutMax=other.getNbCoutMax();
        nbPointVictoire= other.getNbPointVictoire();
        delete[] coutRessources;
        coutRessources=new Ressources[nbCoutMax];
        for (unsigned int i=0; i<nbCout; i++) coutRessources[i]=other.getCoutRessources()[i];
    }
    return *this;
}

Merveille& Merveille::operator=(const Merveille& mer) {
    if (this!=&mer) {
        std::cout << "entree affectation" << std::endl;
        Carte::operator=(mer);
        nbPointsCombat=mer.getNbPointsCombat();
        active=mer.getActive();
        rejouer=mer.getRejouer();
        nbProd=mer.getNbProd();
        nbProdMax=mer.getNbProdMax();
        nbPiecesRapportees=mer.getNbPiecesRapportees();
        nbPiecesSacagees=mer.getNbPiecesSacagees();
        batimentSacagee=mer.getBatimentSacagee();
        choixDefausse=mer.getChoixDefausse();
        choixJeton=mer.getChoixJeton();
        delete[] produitRessources;
        produitRessources=new Ressources[nbProdMax];
        for (unsigned int i=0; i<nbProd; i++) {
            std::cout << i << std::endl;
            produitRessources[i]=mer.getProduitRessources()[i];
        }
    }
    return *this;
}


Batiment& Batiment::operator=(const Batiment& other) {
    if (this!=&other) {
        Carte::operator=(other);
        coutPieces=other.getCoutPieces();
        coutChainage=other.getCoutChainage();
        symboleChainage=other.getSymboleChainage();
        faceCachee=other.getFaceCachee();
    }
    return *this;
}

BatimentRessource& BatimentRessource::operator=(const BatimentRessource& other) {
    if (this!=&other) {
        Batiment::operator=(other);
        ressourceProduite=other.getRessourceProduite();
        nbRessourcesProduites=other.getNbRessourcesProduites();
    }
    return *this;
}

BatimentCivil& BatimentCivil::operator=(const BatimentCivil& other) {
    if (this!=&other) {
        Batiment::operator=(other);
    }
    return *this;
}

BatimentScientifique& BatimentScientifique::operator=(const BatimentScientifique& other) {
    if (this!=&other) {
        Batiment::operator=(other);
        symbole=other.getSymbole();
    }
    return *this;
}

BatimentCommercial& BatimentCommercial::operator=(const BatimentCommercial& other) {
    if (this!=&other) {
        Batiment::operator=(other);
        piecesRapportees=other.getPiecesRapportees();
        typePourGainPieces=other.getTypePourGainPiece();
        nbRessourcesStockees=other.getNbRessourcesStockees();
        nbRessourcesDisponibles=other.getNbRessourcesDisponibles();
        delete[] ressourcesStockees; delete[] ressourcesDisponibles;
        ressourcesStockees=new Ressources[nbRessourcesStockees];
        ressourcesDisponibles=new Ressources[nbRessourcesDisponibles];
        for (unsigned int i=0; i<nbRessourcesStockees; i++) ressourcesStockees[i]=other.getRessourcesStockees()[i];
        for (unsigned int i=0; i<nbRessourcesDisponibles; i++) ressourcesDisponibles[i]=other.getRessourcesDisponibles()[i];
    }
    return *this;
}

BatimentMilitaire& BatimentMilitaire::operator=(const BatimentMilitaire& other) {
    if (this!=&other) {
        Batiment::operator=(other);
        pointsCombats=other.getNbPointsCombats();
    }
    return *this;
}


void Merveille::ajouterProduitRessources(Ressources r) {
    if (nbProd >= nbProdMax) {
        Ressources* newlist = new Ressources[nbProdMax+5];
        for (unsigned int i = 0; i<nbCout; i++)
            newlist[i] = produitRessources[i];
        Ressources* old = produitRessources; produitRessources = newlist; delete [] old;
        nbProdMax += 5;
    }
    produitRessources[nbProd++] = r;
}

void BatimentCommercial::AjouterRessourcesStockees(Ressources r) {
    ressourcesStockees[nbRessourcesStockees++]=r;
}


void BatimentCommercial::AjouterRessourcesDisponibles(Ressources r) {
    ressourcesDisponibles[nbRessourcesDisponibles++]=r;
}


ostream& operator<<(ostream& f, const Merveille& m) {
    f << "___Merveille : " << m.getNom() << "___";
    if (!m.getActive()) f << " (inactive)";
    f << "\ncout : ";
    for (unsigned int i=0; i<m.getNbCout(); i++) {
        f << "# " << printRessource(m.getCoutRessources()[i]) << "    ";
    }
    if (m.getNbPointVictoire()!=0) {
        f << std::endl << "Cette merveille confere " << m.getNbPointVictoire() << " points de victoire";
    }
    if (m.getNbPointsCombat()!=0) {
        f << std::endl << "Cette merveille confere " << m.getNbPointsCombat() << " points de combat";
    }
    if (m.getNbPiecesRapportees()!=0) {
        f << std::endl << "Cette merveille confere " << m.getNbPiecesRapportees() << " pieces";
    }
    if (m.getNbPiecesSacagees()!=0) {
        f << std::endl << "Cette merveille sacage " << m.getNbPiecesSacagees() << " pieces a l'adversaire";
    }
    if (m.getRejouer()==true) {
        f << std::endl << "Cette merveille a l'effet rejouer";
    }
    if (m.getChoixDefausse()) f << std::endl << "Cette merveille permet de choisir un batiment dans la defausse";
    if (m.getBatimentSacagee()==TypeBatiment::Primaire) f << std::endl << "Cette merveille permet de detruire une ressource primaire a l'adversaire";
    else if (m.getBatimentSacagee()==TypeBatiment::Manufacturee) f << std::endl << "Cette merveille permet de detruire un produit manufacture a l'adversaire";
    if (m.getChoixJeton()) f << std::endl << "Cette merveille permet de choisir un jeton progres";
    if (m.getNbProd()!=0) {
        f << "\nRessources disponibles : ";
        for (unsigned int i=0; i<m.getNbProd(); i++) f << " # " << printRessource(m.getProduitRessources()[i]);
    }
    return f << std::endl;
}

void Batiment::afficher(std::ostream& f) const {f << "~~~Batiment : "<< nom << "~~~" << std::endl;}

void BatimentRessource::afficher(std::ostream& f) const {f << "\033[0;37m~~~Batiment : "<< nom << "~~~\033[0m" << std::endl << "Ressource produite : " << printRessource(ressourceProduite) << std::endl;}

void BatimentCivil::afficher(std::ostream& f) const {f << "\033[0;34m~~~Batiment : "<< nom << "~~~\033[0m" << std::endl;}

void BatimentScientifique::afficher(std::ostream& f) const {f << "\033[0;32m~~~Batiment : "<< nom << "~~~\033[0m" << std::endl << "Symbole scientifique : " << printSymbole(symbole) << std::endl;}

void BatimentCommercial::afficher(std::ostream& f) const {
    f << "\033[0;33m~~~Batiment : "<< nom << "~~~\033[0m";
    if (piecesRapportees!=0) f << "\nPieces rapportees : " << piecesRapportees;
    if (nbRessourcesStockees!=0) {
        f << "\nRessources stockees : ";
        for (unsigned int i=0; i<nbRessourcesStockees; i++) f << " # " << printRessource(ressourcesStockees[i]);
    }
    if (nbRessourcesDisponibles!=0) {
        f << "\nRessources disponibles : ";
        for (unsigned int i=0; i<nbRessourcesDisponibles; i++) f << " # " << printRessource(ressourcesDisponibles[i]);
    }
    f << std::endl;
}

void BatimentMilitaire::afficher(std::ostream& f) const {f << "\033[0;31m~~~Batiment : "<< nom << "~~~\033[0m" << std::endl << "Points de combats : " << pointsCombats << std::endl;}

void BatimentGuilde::afficher(std::ostream& f) const {f << "\033[0;35m~~~Batiment : "<< nom << "~~~\033[0m" << std::endl << "Type pour avantages : " << printTypeBatiment(typePourAvantages) << std::endl;}

std::ostream& operator<<(std::ostream& f, const Batiment& bat) {
    bat.afficher(f);
    if (bat.getNbPointVictoire()!=0) f << "Points de victoire: " << bat.getNbPointVictoire() << "   ";
    if (bat.getCoutPieces()!=0) f << "Cout en pieces: " << bat.getCoutPieces() << "   ";
    if (bat.getCoutChainage()!="NULL") f << "Chainage requis: " << bat.getCoutChainage() << "   ";
    if (bat.getSymboleChainage()!="NULL") f << "Symbole de chainage: " << bat.getSymboleChainage() << "   ";
    if (!bat.getFaceCachee()) f << "Face cachee: " << (bat.getFaceCachee() ? "Oui" : "Non");
    if (bat.getNbCout()!=0) {
        f << "\nCout Ressource : ";
        for (unsigned int i=0; i<bat.getNbCout(); i++) f << " # " << printRessource(bat.getCoutRessources()[i]);
    }
    f << "\n" << std::endl;
    return f;
}
