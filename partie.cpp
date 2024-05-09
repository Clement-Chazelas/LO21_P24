#include "partie.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <set>
#include "cartes.h"
#include "utils.h"


Partie::Partie(const std::string& n_j1, const std::string& p_j1, const std::string& n_j2, const std::string& p_j2)
    : joueur1(Joueur(n_j1, p_j1)), joueur2(Joueur(n_j2, p_j2)), plateau(PlateauDeJeu(20, 5, 5)), age(1) {}


void Partie::genererHuitMerveilles() {
    // Chemin vers le fichier CSV
    QString filePath = "C:/Users/cheva/OneDrive/Bureau/Qt/Edition_LO21/merveilles_SevenWonders.csv"; //changer l'adresse !

    // Ouverture du fichier en lecture seule
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Impossible d'ouvrir le fichier :" << file.errorString();
    }

    // Lecture du contenu du fichier ligne par ligne
    QTextStream in(&file);
    int counter=0;
    std::set<int> numbers=generateRdmSet(12, 8);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (numbers.find(counter++)!=numbers.end()) {
            QStringList values = line.split(";");
            std::string nom=values.value(0).toStdString();
            bool active = (values.value(1).compare("true", Qt::CaseInsensitive) == 0);
            bool rejouer = (values.value(2).compare("true", Qt::CaseInsensitive) == 0);
            unsigned int ptv=values.value(3).toUInt();
            unsigned int ptc=values.value(4).toUInt();
            unsigned int pR=values.value(5).toUInt();
            unsigned int pS=values.value(6).toUInt();
            unsigned int nbPierre=values.value(7).toUInt();
            unsigned int nbBois=values.value(8).toUInt();
            unsigned int nbArgile=values.value(9).toUInt();
            unsigned int nbVerre=values.value(10).toUInt();
            unsigned int nbPapyrus=values.value(11).toUInt();

            Merveille m(nom, active, rejouer, ptv, ptc, pR, pS);

            for (unsigned int i=0; i<nbPierre; i++) m.ajouterCoutRessources(Ressources::pierre);
            for (unsigned int i=0; i<nbBois; i++) m.ajouterCoutRessources(Ressources::bois);
            for (unsigned int i=0; i<nbArgile; i++) m.ajouterCoutRessources(Ressources::argile);
            for (unsigned int i=0; i<nbVerre; i++) m.ajouterCoutRessources(Ressources::verre);
            for (unsigned int i=0; i<nbPapyrus; i++) m.ajouterCoutRessources(Ressources::papyrus);
            plateau.ajouterMerveillePlateau(m);
        }
    }
    // Fermeture du fichier
    file.close();
    plateau.melangerMerveilles();
}


void Partie::afficherMerveillesRestantes(bool salve2) const {
    std::cout << "\n\n----    Merveilles Parmis Lesquelles choisir    ----\n" << std::endl;
    unsigned int nb_merveilles(plateau.getNb_merveille_plateau());
    if (!salve2) nb_merveilles-=4;
    for (unsigned int i=0; i<nb_merveilles; i++) std::cout << plateau.getSelectionMerveille()[i] << std::endl;
}

void Partie::selectionDesMerveilles() { // Méthode a finir
    try {
        afficherMerveillesRestantes();
        joueur1.ajouterMerveille(plateau.choisirMerveille());
        afficherMerveillesRestantes();
        joueur2.ajouterMerveille(plateau.choisirMerveille(true));
        afficherMerveillesRestantes();
        joueur2.ajouterMerveille(plateau.choisirMerveille(true));
        afficherMerveillesRestantes();
        joueur1.ajouterMerveille(plateau.choisirMerveille());
        afficherMerveillesRestantes();
        for (unsigned int i=0; i<4; i++) plateau.getSelectionMerveille()[i]=plateau.getSelectionMerveille()[i+4];
        afficherMerveillesRestantes(true);
        joueur2.ajouterMerveille(plateau.choisirMerveille(true));
        afficherMerveillesRestantes(true);
        joueur1.ajouterMerveille(plateau.choisirMerveille());
        afficherMerveillesRestantes(true);
        joueur1.ajouterMerveille(plateau.choisirMerveille());
        afficherMerveillesRestantes(true);
        joueur2.ajouterMerveille(plateau.choisirMerveille(true));
        delete[] plateau.getSelectionMerveille(); //On libere la memoire reserve pour les merveilles du plateau
        std::cout << joueur2 << std::endl;
        std::cout << joueur1 << std::endl;
    }
    catch (const char* mes) {
        std::cout << mes << std::endl;
    }
}

void Partie::genererAgeUn() {
    // Chemin vers le fichier CSV
    QString filePath = "C:/Users/cheva/OneDrive/Bureau/Qt/Edition_LO21/batimentsAge1_SevenWonders.csv"; //changer l'adresse !

    // Ouverture du fichier en lecture seule
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Impossible d'ouvrir le fichier :" << file.errorString();
    }

    // Lecture du contenu du fichier ligne par ligne
    QTextStream in(&file);
    QString line = in.readLine();
    int counter=0;
    std::set<int> numbers=generateRdmSet(23, 4);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (numbers.find(counter++)==numbers.end()) {
            QStringList values = line.split(";");
            std::string nom=values.value(0).toStdString();
            TypeBatiment type=qStringToTypeBatiment(values.value(1));
            unsigned int coutPiece=values.value(2).toUInt();
            std::string symboleChainage=values.value(3).toStdString();
            unsigned int ptv=values.value(4).toUInt();
            unsigned int ptc=values.value(5).toUInt();
            QString resStr=values.value(6);
            Ressources res;
            unsigned int nbResS=0;
            bool stock=true;
            if (resStr=="NULL") stock=false;
            else {res=qStringToRessource(resStr); nbResS=1;}
            SymboleScientifique symboleScientifique=qStringToSymboleScientifique(values.value(7));
            unsigned int piecesRapportes=values.value(8).toUInt();
            QString coutRessourceStr=values.value(9);
            switch (type) {
            case TypeBatiment::Ressource: {
                BatimentRessource* bR=new BatimentRessource(nom, coutPiece, "NULL", symboleChainage, true, res, 1);
                if (coutRessourceStr!="NULL") bR->ajouterCoutRessources(qStringToRessource(coutRessourceStr));
                plateau.ajouterBatimentPlateau(bR);
                break; }
            case TypeBatiment::Civil: {
                BatimentCivil* bCi=new BatimentCivil(nom, coutPiece, "NULL", symboleChainage, true, ptv);
                if (coutRessourceStr!="NULL") bCi->ajouterCoutRessources(qStringToRessource(coutRessourceStr));
                plateau.ajouterBatimentPlateau(bCi);
                break; }
            case TypeBatiment::Scientifique: {
                BatimentScientifique* bS=new BatimentScientifique(nom, coutPiece, "NULL", symboleChainage, true, symboleScientifique, ptv);
                if (coutRessourceStr!="NULL") bS->ajouterCoutRessources(qStringToRessource(coutRessourceStr));
                plateau.ajouterBatimentPlateau(bS);
                break; }
            case TypeBatiment::Commercial: {
                BatimentCommercial* bCo=new BatimentCommercial(nom, coutPiece, "NULL", symboleChainage, true, nbResS, 0, piecesRapportes, TypeBatiment::undefined);
                if (coutRessourceStr!="NULL") bCo->ajouterCoutRessources(qStringToRessource(coutRessourceStr));
                plateau.ajouterBatimentPlateau(bCo);
                if (stock) bCo->AjouterRessourcesStockees(res);
                break; }
            case TypeBatiment::Militaire: {
                BatimentMilitaire* bM=new BatimentMilitaire(nom, coutPiece, "NULL", symboleChainage, true, ptc);
                if (coutRessourceStr!="NULL") bM->ajouterCoutRessources(qStringToRessource(coutRessourceStr));
                plateau.ajouterBatimentPlateau(bM);
                break; }
            }
        }
    }
    file.close();
    plateau.melangerBatiments();
}


std::ostream& operator<<(std::ostream& f, const Partie& p) {
    f << "\033[1mPartie --> " << p.getJoueur1().getNom() << " VS " << p.getJoueur2().getNom() << "\033[0m";
    return f;
}

