#include "joueur.h"
#include "plateauJeu.h"
#include "utils.h"
#include "QInputDialog"
#include "QLineEdit"

using namespace std;


void Joueur::ajouterMerveille(const Merveille& mer) {
    merveilles[nbMerveilles++]=mer; //Pas necessaire pour l'instant de gerer le nombre de merveilles du joueur (tjs = 4)
}


void Joueur::ajouterBatiment(Batiment* bat) {
    cite[nbBatiments++]=bat;
}


unsigned int Joueur::gainDefausse() {
    unsigned int total=2;
    for (unsigned i=0; i<nbBatiments; i++) {
        if (cite[i]->getType()=="BatimentCommercial") total++;
    }
    return total;
}

unsigned int Joueur::coutAchat(Batiment* bat, const Joueur& adversaire) {
    unsigned int total=bat->getCoutPieces();
    if (nbBatiments==0) return bat->getNbCout()*2;
    Ressources* res=new Ressources[bat->getNbCout()];
    for (unsigned int i=0; i<bat->getNbCout(); i++) res[i]=bat->getCoutRessources()[i];
    for (unsigned i=0; i<nbBatiments; i++) {
        if (bat->getCoutChainage()!="NULL") {
            if (cite[i]->getSymboleChainage()==bat->getCoutChainage()) return 0;
        }
        if (cite[i]->getType()=="BatimentRessource") {
            bool found=false;
            unsigned int counter=0;
            while (!found && counter<bat->getNbCout()) {
                if (cite[i]->getRessourceProduite()==res[counter]) {
                    res[counter]=Ressources::undefined;
                    found=true;
                    for (unsigned int i=0; i<bat->getNbCout(); i++) std::cout << printRessource(res[i]) << " ! ";

                }
                counter++;
            }
        }
    }
    for (unsigned int i=0; i<bat->getNbCout(); i++) if (res[i]!=Ressources::undefined) {
        total+=2;
        for (unsigned int j=0; j<adversaire.getNbBatiments(); j++) {
            if (adversaire.getCite()[j]->getType()=="BatimentRessource") {
                if (adversaire.getCite()[j]->getRessourceProduite()==res[i]) total++;
            }
        }
    }
    delete[] res;
    return total;
}


unsigned int Joueur::compterPointsVictoires() const {
    unsigned int total=0;
    for (unsigned int i=0; i<nbBatiments; i++) {
        total+=cite[i]->getNbPointVictoire();
    }
    for (unsigned int i=0; i<nbMerveilles; i++) {
        total+=merveilles[i].getNbPointVictoire();
    }
    return total;
}


void Joueur::choisirMerveilleInactive() {
    bool ok;
    QString merveilleChoisie = QInputDialog::getText(nullptr, QString::fromStdString(nom), "Merveille a activer :", QLineEdit::Normal, "", &ok);
    for (unsigned int i=0; i<nbMerveilles; i++) {
        if (merveilleChoisie.toStdString()==merveilles[i].getNom()) merveilles[i].setActive(true); //il faudra verifier si la merveille n'est pas deja active
    }
}


ostream& operator<<(ostream& f, const Joueur& j) {
    f << "===Joueur : " << j.getPrenom() << " " << j.getNom() << " - PV : " << j.compterPointsVictoires() << " - Pieces : " << j.getnbPieces() << "===" << endl;
    f << "Merveilles dans sa cite : " << endl;
    for (unsigned int i=0; i<j.getNbMerveilles(); i++) f << j.getMerveilles()[i];
    f << "Batiments dans sa cite : " << endl;
    for (unsigned int i=0; i<j.getNbBatiments(); i++) f << *(j.getCite()[i]);
    return f;
}
