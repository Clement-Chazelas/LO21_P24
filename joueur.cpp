#include "joueur.h"
#include "utils.h"
#include "jetonProgres.h"
#include "plateauJeu.h"
#include "QInputDialog"
#include "QLineEdit"

using namespace std;


void Joueur::ajouterMerveille(const Merveille& mer) {
    merveilles[nbMerveilles++]= mer; //Pas necessaire pour l'instant de gerer le nombre de merveilles du joueur (tjs = 4)
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
    std::cout << "entree dans cout achat... check" << std::endl;
    unsigned int total=bat->getCoutPieces();
    if (nbBatiments==0 && nbMerveilles==0) return bat->getNbCout()*2+bat->getCoutPieces();
    Ressources* res=new Ressources[bat->getNbCout()];
    for (unsigned int i=0; i<bat->getNbCout(); i++) res[i]=bat->getCoutRessources()[i];
    std::cout << "copie des ressources a acquerir ... check" << std::endl;
    for (unsigned i=0; i<nbBatiments; i++) {
        if (bat->getCoutChainage()!="NULL") {
            if (cite[i]->getSymboleChainage()==bat->getCoutChainage()) return 0;
        }
        if (cite[i]->getType()=="BatimentRessource") { // On vient parcourir la cite pour voir les ressources produites
            bool found=false;
            unsigned int counter=0;
            while (!found && counter<bat->getNbCout()) {
                if (cite[i]->getRessourceProduite()==res[counter]) {
                    res[counter]=Ressources::undefined;
                    found=true;
                }
                counter++;
            }
        }
    }
    std::cout << "Parcours des batiments ressources ... check" << std::endl;
    for (unsigned i=0; i<nbBatiments; i++) { // De même pour voir les ressources disponibles pour les batiments commmerciaux
        if (cite[i]->getType()=="BatimentCommercial") {
            bool found=false;
            unsigned int counter=0;
            while (!found && counter<bat->getNbCout()) {
                if (res[counter]!=Ressources::undefined) {
                    for (unsigned int j=0; j<cite[i]->getNbRessourcesDisponibles(); j++) {
                        if (cite[i]->getRessourcesDisponibles()[j]==res[counter]) {
                            res[counter]=Ressources::undefined;
                            found=true;
                        }
                    }
                }
                counter++;
            }
        }
    }
    std::cout << "Parcours des batiments commerciaux dispo ... check" << std::endl;
    for (unsigned i=0; i<nbBatiments; i++) { // Puis une derniere fois pour voir ajouter les ressources produites mais payantes par les batiments commerciaux
        if (cite[i]->getType()=="BatimentCommercial") {
            bool found=false;
            unsigned int counter=0;
            while (!found && counter<bat->getNbCout()) {
                if (res[counter]!=Ressources::undefined) {
                    for (unsigned int j=0; j<cite[i]->getNbRessourcesStockees(); j++) {
                        if (cite[i]->getRessourcesStockees()[j]==res[counter]) {
                            res[counter]=Ressources::undefined;
                            total++;
                            found=true;
                        }
                    }
                }
                counter++;
            }
        }
    }
    std::cout << "Parcours des batiments commerciaux stockees ... check" << std::endl;
    for (unsigned int i=0; i<bat->getNbCout(); i++) {
        if (res[i]!=Ressources::undefined) {
            total+=2;
            for (unsigned int j=0; j<adversaire.getNbBatiments(); j++) {
                if (adversaire.getCite()[j]->getType()=="BatimentRessource") {
                    if (adversaire.getCite()[j]->getRessourceProduite()==res[i]) total++;
                }
            }
        }
    }
    std::cout << "Parcours des batiments adverses ... check" << std::endl;
    delete[] res;
    return total;
}


const unsigned int Joueur::compterPointsVictoires(const PlateauDeJeu& pla, const Joueur& adv, const bool j2) const {
    unsigned int total=0;
    for (unsigned int i=0; i<nbBatiments; i++) {
        total+=cite[i]->getNbPointVictoire();
    }
    for (unsigned int i=0; i<nbMerveilles; i++) {
        if (merveilles[i].getActive())
            total+=merveilles[i].getNbPointVictoire();
    }
    for (unsigned int i=0; i<jetonsProgres.size(); i++) {
        total+=jetonsProgres[i].getPointsVictoire();
    }
    if (!j2) {
        if (pla.getEmplacementPionMilitaire()>5) total+=10;
        else if (pla.getEmplacementPionMilitaire()>2) total+=5;
        else if (pla.getEmplacementPionMilitaire()>0) total+=2;
    }
    else {
        if (pla.getEmplacementPionMilitaire()<-5) total+=10;
        else if (pla.getEmplacementPionMilitaire()<-2) total+=5;
        else if (pla.getEmplacementPionMilitaire()<0) total+=2;
    }

    //point des guildes :

    for (unsigned int i = 0; i < nbBatiments; i++) {
        unsigned int nbjoueur, nbadv;
        if (cite[i]->getNom() == "Guilde des Magistrats"){
            nbjoueur = compterNbCartesCouleur(1);
            nbadv = adv.compterNbCartesCouleur(1);
            if (nbjoueur > nbadv)
                total += nbjoueur;
        }
        if (cite[i]->getNom() == "Guilde des Tacticiens"){
            nbjoueur = compterNbCartesCouleur(2);
            nbadv = adv.compterNbCartesCouleur(2);
            if (nbjoueur > nbadv)
                total += nbjoueur;
        }
        if (cite[i]->getNom() == "Guilde des Scientifiques"){
            nbjoueur = compterNbCartesCouleur(3);
            nbadv = adv.compterNbCartesCouleur(3);
            if (nbjoueur > nbadv)
                total += nbjoueur;
        }
        if (cite[i]->getNom() == "Guilde des Commercants"){
            nbjoueur = compterNbCartesCouleur(4);
            nbadv = adv.compterNbCartesCouleur(4);
            if (nbjoueur > nbadv)
                total += nbjoueur;
        }
        if (cite[i]->getNom() == "Guilde des Armateurs"){
            nbjoueur = compterNbCartesCouleur(5);
            nbadv = adv.compterNbCartesCouleur(5);
            if (nbjoueur > nbadv)
                total += nbjoueur;
        }
        if (cite[i]->getNom() == "Guilde des Usuriers"){
            nbjoueur = getnbPieces();
            nbadv = adv.getnbPieces();
            if (nbjoueur > nbadv)
                total += nbjoueur/3;
        }
        if (cite[i]->getNom() == "Guilde des Batisseurs"){
            nbjoueur = 0;
            for (unsigned int i = 0; i< nbMerveilles; i++){
                if (merveilles[i].getActive())
                    nbjoueur ++;
            }
            nbadv = 0;
            for (unsigned int i = 0; i< adv.getNbMerveilles(); i++){
                if (adv.getMerveilles()[i].getActive())
                    nbadv ++;
            }
            if (nbjoueur > nbadv)
                total += 2 * nbjoueur;
        }
    }

    return total;
}

unsigned int Joueur::compterNbCartesCouleur(unsigned int couleur) const {
    unsigned int compteur = 0;
    switch (couleur) {
    case 1:
        //couleur bleu
        for (unsigned int i=0; i<nbBatiments; i++) {
            if (cite[i]->getType()=="BatimentCivil")
                compteur++;
        }
        break;
    case 2:
        //couleur rouge
        for (unsigned int i=0; i<nbBatiments; i++) {
            if (cite[i]->getType()=="BatimentMilitaire")
                compteur++;
        }
        break;
    case 3:
        //couleur vert
        for (unsigned int i=0; i<nbBatiments; i++) {
            if (cite[i]->getType()=="BatimentScientifique")
                compteur++;
        }
        break;
    case 4:
        //couleur jaune
        for (unsigned int i=0; i<nbBatiments; i++) {
            if (cite[i]->getType()=="BatimentCommercial")
                compteur++;
        }
        break;
    case 5:
        //couleur grise et marron
        for (unsigned int i=0; i<nbBatiments; i++) {
            if (cite[i]->getType()=="BatimentRessource")
                compteur++;
        }
    default:
        throw "erreur couleur inconnue";
    }
    return compteur;
}

unsigned int Joueur::checkVictoireScientifique() const {
    std::set<SymboleScientifique> science;
    for (unsigned int i=0; i<nbBatiments; i++) {
        if (cite[i]->getType()=="BatimentScientifique") {
            science.insert(cite[i]->getSymbole());
        }
    }
    return science.size();
}


Merveille& Joueur::choisirMerveilleInactive() {
    bool ok;
    QString merveilleChoisie = QInputDialog::getText(nullptr, QString::fromStdString(nom), "Merveille a activer :", QLineEdit::Normal, "", &ok);
    for (unsigned int i=0; i<nbMerveilles; i++) {
        if (merveilleChoisie.toStdString()==merveilles[i].getNom() && !merveilles[i].getActive()) {
            merveilles[i].setActive(true);
            return merveilles[i];
        }
    }
    throw "erreur : impossible d'activer la merveille";
}

void Joueur::saccagerRessourceAdverse(const Merveille& mer, Joueur& adversaire){
    if (mer.getBatimentSacagee() == TypeBatiment::undefined)
        throw "Cette merveille est incapable de saccager une ressource.";
    BatimentRessource* select = new BatimentRessource[adversaire.getNbBatiments()];
    unsigned int counter = 0;
    if (mer.getBatimentSacagee() == TypeBatiment::Primaire){
        for (unsigned int i = 0; i < adversaire.getNbBatiments(); i++) {
            if (adversaire.getCite()[i]->getType() == "BatimentRessource"){
                BatimentRessource* tmp = dynamic_cast<BatimentRessource*>(adversaire.getCite()[i]);
                if (tmp->getTypeRessource() == "RessourcePrimaire") {
                    select[counter++] = *tmp;
                }
            }
        }
        if (counter == 0)
            return; //L'adversaire ne possède pas de ressources primaires.
    }
    else if (mer.getBatimentSacagee() == TypeBatiment::Manufacturee){
        for (unsigned int i = 0; i < adversaire.getNbBatiments(); i++) {
            if (adversaire.getCite()[i]->getType() == "BatimentRessource"){
                BatimentRessource* tmp = dynamic_cast<BatimentRessource*>(adversaire.getCite()[i]);
                if (tmp->getTypeRessource() == "RessourceManufacturee") {
                    select[counter++] = *tmp;
                }
            }
        }
        if (counter == 0)
            return; //L'adversaire ne possède pas de ressources manufacturées.
    }
    std::cout << "\n\n----    Ressources Parmis Lesquelles choisir    ----\n" << std::endl;
    for (unsigned int i=0; i<counter; i++)
        std::cout << select[i].getNom() << std::endl;
    bool ok1;
    QString ressourceChoisie = QInputDialog::getText(nullptr, QString::fromStdString(nom), "Ressource choisie :", QLineEdit::Normal, "", &ok1);
    bool verif = false;
    for (unsigned int i=0; i<counter; i++){
        if (ressourceChoisie.toStdString() == select[i].getNom())
            verif = true;
    }
    if (verif = false)
        throw "carte choisie non trouvée dans les ressources selectionnables.";
    counter = 0;
    while (ressourceChoisie.toStdString() != adversaire.getCite()[counter]->getNom() &&  counter < adversaire.getNbBatiments() ){
        counter++;
    }
    if (counter == adversaire.getNbBatiments())
        throw "carte choisie non trouvé dans les ressources de l'adversaire.";

    for (unsigned int i=counter; i<adversaire.getNbBatiments()-1; i++){
        adversaire.setElementCite(adversaire.getCite()[i+1], i);
    }
    adversaire.setNbBatiments(adversaire.getNbBatiments()-1);

}

ostream& operator<<(ostream& f, const Joueur& j) {
    f << "===Joueur : " << j.getPrenom() << " " << j.getNom() << " - Pieces : " << j.getnbPieces() << " - Science : " << j.checkVictoireScientifique() << "/6 ===" << endl;
    f << "Merveilles dans sa cite : " << endl;
    for (unsigned int i=0; i<j.getNbMerveilles(); i++) f << j.getMerveilles()[i];
    f << "Batiments dans sa cite : " << endl;
    for (unsigned int i=0; i<j.getNbBatiments(); i++) f << *(j.getCite()[i]);
    f << "Jetons scientifiques : " << endl;
    for (unsigned int i=0; i<j.getJetonsProgres().size(); i++) f << j.getJetonsProgres()[i];
    return f;
}

void Joueur::ajouterJeton(const JetonProgres& jeton) {
    jetonsProgres.push_back(jeton);
}

void Joueur::afficherJetons() const {
    std::cout << "Jetons du joueur :" << std::endl;
    for (const auto& jeton : jetonsProgres) {
        std::cout << "Nom : " << jeton.getNomJeton() << ", Effet : " << jeton.getEffetJeton() << ", Points de victoire : " << jeton.getPointsVictoire() << std::endl;
    }
}
