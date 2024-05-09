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
    nbPiecesRapportees(mer.getNbPiecesRapportees()), nbPiecesSacagees(mer.getNbPiecesSacagees()) {
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
        Carte::operator=(mer);
        nbPointsCombat=mer.getNbPointsCombat();
        active=mer.getActive();
        rejouer=mer.getRejouer();
        nbProd=mer.getNbProd();
        nbProdMax=mer.getNbProdMax();
        nbPiecesRapportees=mer.getNbPiecesRapportees();
        nbPiecesSacagees=mer.getNbPiecesSacagees();
        for (unsigned int i=0; i<nbProd; i++) produitRessources[i]=mer.getProduitRessources()[i];
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


void Merveille::ajouterProduitRessources(Ressources r){
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
    return f << std::endl;
}

std::ostream& operator<<(std::ostream& f, const Batiment& bat) {
    bat.afficher(f);
    f << "Points de victoire: " << bat.getNbPointVictoire() << " - ";
    f << "Cout en pieces: " << bat.getCoutPieces() << "   ";
    if (bat.getCoutChainage()!="NULL") f << "Chainage requis: " << bat.getCoutChainage() << "   ";
    if (bat.getSymboleChainage()!="NULL") f << "Symbole de chainage: " << bat.getSymboleChainage() << "   ";
    if (!bat.getFaceCachee()) f << "Face cachee: " << (bat.getFaceCachee() ? "Oui" : "Non");
    f << "\n" << std::endl;
    return f;
}

