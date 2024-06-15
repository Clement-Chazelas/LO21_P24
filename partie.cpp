#include "partie.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <set>
#include "cartes.h"
#include "utils.h"
#include "QInputDialog"


Partie::Partie(const std::string& n_j1, const std::string& p_j1, const std::string& n_j2, const std::string& p_j2, bool iaj1, bool iaj2)
    : joueur1(Joueur(n_j1, p_j1, iaj1)), joueur2(Joueur(n_j2, p_j2, iaj2)), plateau(PlateauDeJeu(20, 5, 5)), age(1), rejouer(false){}


void Partie::genererHuitMerveilles() {
    // Chemin vers le fichier CSV
    QString filePath = "C:/Users/Agaathe/Documents/cours/GI/P24/LO21/projet 7 pyramides/jeu_code/merveilles_SevenWonders.csv"; //changer adresse!
    // Ouverture du fichier en lecture seule
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Impossible d'ouvrir le fichier :" << file.errorString();
    }

    // Lecture du contenu du fichier ligne par ligne
    QTextStream in(&file);
    int counter=0;
    std::set<int> numbers=generateRdmSet(12, 8, 1);
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
            QString resStr=values.value(12);
            QStringList res;
            unsigned int nbResS=0;
            if (resStr!="NULL") {
                res=resStr.split("/");
                nbResS=res.size();
            }
            TypeBatiment tb=qStringToTypeBatiment(values.value(13));

            Merveille m(nom, active, rejouer, ptv, ptc, pR, pS, nbResS, tb);

            for (unsigned int i=0; i<nbPierre; i++) m.ajouterCoutRessources(Ressources::pierre);
            for (unsigned int i=0; i<nbBois; i++) m.ajouterCoutRessources(Ressources::bois);
            for (unsigned int i=0; i<nbArgile; i++) m.ajouterCoutRessources(Ressources::argile);
            for (unsigned int i=0; i<nbVerre; i++) m.ajouterCoutRessources(Ressources::verre);
            for (unsigned int i=0; i<nbPapyrus; i++) m.ajouterCoutRessources(Ressources::papyrus);
            for (unsigned int i=0; i< nbResS; i++) m.ajouterProduitRessources(qStringToRessource(res[i]));
            if (nom=="Le Mausolee") m.setChoixDefausse(true);
            if (nom=="La Grande Bibliotheque") m.setChoixJeton(true);
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
        if (joueur1.robot())
            joueur1.ajouterMerveille(plateau.iaChoisirMerveille());
        else
            joueur1.ajouterMerveille(plateau.choisirMerveille());

        afficherMerveillesRestantes();

        if (joueur2.robot())
            joueur2.ajouterMerveille(plateau.iaChoisirMerveille());
        else
            joueur2.ajouterMerveille(plateau.choisirMerveille(true));

        afficherMerveillesRestantes();

        if (joueur2.robot())
            joueur2.ajouterMerveille(plateau.iaChoisirMerveille());
        else
            joueur2.ajouterMerveille(plateau.choisirMerveille(true));

        afficherMerveillesRestantes();

        if (joueur1.robot())
            joueur1.ajouterMerveille(plateau.iaChoisirMerveille());
        else
            joueur1.ajouterMerveille(plateau.choisirMerveille());

        for (unsigned int i=0; i<4; i++) plateau.getSelectionMerveille()[i]=plateau.getSelectionMerveille()[i+4];

        afficherMerveillesRestantes(true);

        if (joueur2.robot())
            joueur2.ajouterMerveille(plateau.iaChoisirMerveille());
        else
            joueur2.ajouterMerveille(plateau.choisirMerveille(true));

        afficherMerveillesRestantes(true);

        if (joueur1.robot())
            joueur1.ajouterMerveille(plateau.iaChoisirMerveille());
        else
            joueur1.ajouterMerveille(plateau.choisirMerveille());

        afficherMerveillesRestantes(true);

        if (joueur1.robot())
            joueur1.ajouterMerveille(plateau.iaChoisirMerveille());
        else
            joueur1.ajouterMerveille(plateau.choisirMerveille());

        afficherMerveillesRestantes(true);

        if (joueur2.robot())
            joueur2.ajouterMerveille(plateau.iaChoisirMerveille());
        else
            joueur2.ajouterMerveille(plateau.choisirMerveille(true));


        delete[] plateau.getSelectionMerveille(); //On libere la memoire reserve pour les merveilles du plateau
        std::cout << joueur2 << std::endl;
        std::cout << joueur1 << std::endl;
    }
    catch (const char* mes) {
        std::cout << mes << std::endl;
    }
}

int Partie::selectionDesBatiments(int age) {
    try {
        bool j2=false;
        if (plateau.getEmplacementPionMilitaire() > 0 && !joueur1.robot()) {
            bool ok;
            //Demander au joueur de choisir une option
            QStringList options;
            options << "moi" << "adversaire";
            QString choix = QInputDialog::getItem(nullptr, "Joueur 1", "Choisissez qui commence la partie:", options, 0, false, &ok);
            if (choix == "adversaire")
                j2 = true;
        }

        else if (plateau.getEmplacementPionMilitaire() < 0 && !joueur2.robot()) {
            bool ok;
            //Demander au joueur de choisir une option
            QStringList options;
            options << "moi" << "adversaire";
            QString choix = QInputDialog::getItem(nullptr, "Joueur 1", "Choisissez qui commence la partie:", options, 0, false, &ok);
            if (choix == "moi")
                j2 = true;
        }

        else if (age == 2 && plateau.getEmplacementPionMilitaire() <= 0)
            j2 = true;//a la fin de l'age un, le dernier joueur actif est le joueur 2

        else if (age == 3 && plateau.getEmplacementPionMilitaire() < 0)
            j2 = true; //a la fin de l'age deux, le dernier joueur actif est le joueur 1

        while (plateau.getNb_batiment_plateau()>0) {
            std::cout << *this << std::endl;
            if (!j2) {
                std::cout << joueur1 << std::endl;
                plateau.afficherSelectionnable();
                if (joueur1.robot()) {
                    Batiment* bat(plateau.iaChoisirBatiment());
                    if (joueur1.coutAchat(bat, joueur2)<=joueur1.getnbPieces()) {
                        joueur1.pertePieces(joueur1.coutAchat(bat, joueur2));
                        if (bat->getType()=="BatimentScientifique") {
                            for (unsigned int i=0; i<joueur1.getNbBatiments(); i++) {
                                if (joueur1.getCite()[i]->getSymbole()==bat->getSymbole()) {
                                    plateau.iaPrendreJetonDansPlateau(joueur1);
                                }
                            }
                        }
                        joueur1.ajouterBatiment(bat);
                        if (deplacerPionMilitaire(bat->getNbPointsCombats())){
                            return 1; // si deplacerPionMilitaire retourne 1 alors la methode fin de partie a été appelée
                        }
                        if (joueur1.checkVictoireScientifique()==6) {
                            return victoireScientifique(joueur1);
                        }
                    }
                    else {
                        joueur1.gainPieces(joueur1.gainDefausse());
                        plateau.setDefausse(*bat);
                    }
                }
                else {
                    bool ok2;
                    Batiment* bat = nullptr;
                    while (bat == nullptr)
                         bat = plateau.choisirBatiment();
                    //Demander au joueur de choisir une option
                    QStringList options;
                    options << "Construire" << "Defausser" << "Construire Merveille";
                    QString choix = QInputDialog::getItem(nullptr, "Joueur 1", "Choisissez une option:", options, 0, false, &ok2);
                    if (choix=="Construire") {
                        if (joueur1.coutAchat(bat, joueur2)<=joueur1.getnbPieces()) {
                            joueur1.pertePieces(joueur1.coutAchat(bat, joueur2));
                            if (bat->getType()=="BatimentScientifique") {
                                for (unsigned int i=0; i<joueur1.getNbBatiments(); i++) {
                                    if (joueur1.getCite()[i]->getSymbole()==bat->getSymbole()) {
                                        plateau.prendreJetonDansPlateau(joueur1);
                                    }
                                }
                            }
                            joueur1.ajouterBatiment(bat);
                            if (deplacerPionMilitaire(bat->getNbPointsCombats()))
                                return 1;
                            if (joueur1.checkVictoireScientifique()==6) {
                                return victoireScientifique(joueur1);
                            }
                        }
                        else std::cout << "Vous n'avez pas assez d'argent pour acheter le batiment" << std::endl;
                    }
                    else if (choix=="Defausser") {
                        joueur1.gainPieces(joueur1.gainDefausse());
                        plateau.setDefausse(*bat);
                    }
                    else if (choix=="Construire Merveille") {
                        rejouer=joueur1.choisirMerveilleInactive();
                    }
                    std::cout << joueur1 << std::endl;
                }
            }
            else {
                std::cout << joueur2 << std::endl;
                plateau.afficherSelectionnable();
                if (joueur2.robot()) {
                    Batiment* bat(plateau.iaChoisirBatiment());
                    std::cout<<"test12"<<bat->getType();
                    if (joueur2.coutAchat(bat, joueur1)<=joueur2.getnbPieces()) {
                        joueur2.pertePieces(joueur2.coutAchat(bat, joueur1));
                        if (bat->getType()=="BatimentScientifique") {
                            for (unsigned int i=0; i<joueur2.getNbBatiments(); i++) {
                                if (joueur2.getCite()[i]->getSymbole()==bat->getSymbole()) {
                                    plateau.iaPrendreJetonDansPlateau(joueur2);
                                }
                            }
                        }
                        joueur2.ajouterBatiment(bat);
                        if (deplacerPionMilitaire(bat->getNbPointsCombats())){
                            std::cout<<"vic militaire test ";
                            return 1;
                        }
                        if (joueur2.checkVictoireScientifique()==6) {
                            return victoireScientifique(joueur2);
                        }
                    }
                    else {
                        joueur2.gainPieces(joueur2.gainDefausse());
                        plateau.setDefausse(*bat);
                    }
                }
                else {
                    bool ok2;
                    Batiment* bat = nullptr;
                    while (bat == nullptr)
                        bat = plateau.choisirBatiment(j2);
                    //Demander au joueur de choisir une option
                    QStringList options;
                    options << "Construire" << "Defausser" << "Construire Merveille";
                    QString choix = QInputDialog::getItem(nullptr, "Joueur 2", "Choisissez une option:", options, 0, false, &ok2);
                    if (choix=="Construire") {
                        if (joueur2.coutAchat(bat, joueur1)<=joueur2.getnbPieces()) {
                            joueur2.pertePieces(joueur2.coutAchat(bat, joueur1));
                            if (bat->getType()=="BatimentScientifique") {
                                for (unsigned int i=0; i<joueur2.getNbBatiments(); i++) {
                                    if (joueur2.getCite()[i]->getSymbole()==bat->getSymbole()) {
                                        plateau.prendreJetonDansPlateau(joueur2);
                                    }
                                }
                            }
                            joueur2.ajouterBatiment(bat);
                            if (deplacerPionMilitaire(-bat->getNbPointsCombats()))
                                return 1;
                            if (joueur2.checkVictoireScientifique()==6) {
                                return victoireScientifique(joueur2);
                            }
                        }
                        else std::cout << "Vous n'avez pas assez d'argent pour acheter le batiment" << std::endl;
                    }
                    else if (choix=="Defausser") {
                        joueur2.gainPieces(joueur2.gainDefausse());
                        plateau.setDefausse(*bat);
                    }
                    else if (choix=="Construire Merveille") {
                        rejouer=joueur2.choisirMerveilleInactive();
                    }
                    std::cout << joueur2 << std::endl;
                }
            }
            std::cout << "Plateau Militaire : " << plateau.getEmplacementPionMilitaire() << std::endl;
            if (!rejouer) j2=!j2;
            else rejouer=false;
        }
        std::cout<<"il n'y a plus de bat";
        return 0;
    }
    catch (const char* mes) {
        std::cout << mes << std::endl;
    }
}


void Partie::genererAgeUn() {
    // Chemin vers le fichier CSV
    QString filePath = "C:/Users/Agaathe/Documents/cours/GI/P24/LO21/projet 7 pyramides/jeu_code/batimentsAge1_SevenWonders.csv"; //changer l'adresse !

    // Ouverture du fichier en lecture seule
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Impossible d'ouvrir le fichier :" << file.errorString();
    }

    // Lecture du contenu du fichier ligne par ligne
    QTextStream in(&file);
    QString line = in.readLine();
    int counter=0;
    std::set<int> numbers=generateRdmSet(22, 3);
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
                BatimentCommercial* bCo=new BatimentCommercial(nom, coutPiece, "NULL", symboleChainage, true, piecesRapportes, TypeBatiment::undefined);
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


void Partie::genererAgeDeux() {
    // Chemin vers le fichier CSV
    QString filePath = "C:/Users/Agaathe/Documents/cours/GI/P24/LO21/projet 7 pyramides/jeu_code/batimentsAge2_SevenWonders.csv"; //changer l'adresse !

    // Ouverture du fichier en lecture seule
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Impossible d'ouvrir le fichier :" << file.errorString();
    }

    // Lecture du contenu du fichier ligne par ligne
    QTextStream in(&file);
    QString line = in.readLine();
    int counter=0;
    std::set<int> numbers=generateRdmSet(22, 3);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (numbers.find(counter++)==numbers.end()) {
            QStringList values = line.split(";");
            std::string nom=values.value(0).toStdString();
            TypeBatiment type=qStringToTypeBatiment(values.value(1));
            unsigned int coutPiece=values.value(2).toUInt();
            std::string coutChainage=values.value(3).toStdString();
            std::string symboleChainage=values.value(4).toStdString();
            unsigned int ptv=values.value(5).toUInt();
            unsigned int ptc=values.value(6).toUInt();
            QString resStr=values.value(7);
            QStringList res;
            unsigned int nbResS=0;
            bool stock=true;
            if (resStr=="NULL") stock=false;
            else {res=resStr.split("/");}
            unsigned int nbRessourceProd=values.value(8).toUInt();
            SymboleScientifique symboleScientifique=qStringToSymboleScientifique(values.value(9));
            unsigned int piecesRapportes=values.value(10).toUInt();
            QString coutRessourceStr=values.value(11);
            QStringList coutRessource = coutRessourceStr.split("/");
            switch (type) {
            case TypeBatiment::Ressource: {
                BatimentRessource* bR=new BatimentRessource(nom, coutPiece, coutChainage, symboleChainage, true, qStringToRessource(res.at(0)), nbRessourceProd);
                if (coutRessourceStr!="NULL") {
                    for (const QString &item : coutRessource) {
                        bR->ajouterCoutRessources(qStringToRessource(item));
                    }
                }
                plateau.ajouterBatimentPlateau(bR);
                break; }
            case TypeBatiment::Civil: {
                BatimentCivil* bCi=new BatimentCivil(nom, coutPiece, coutChainage, symboleChainage, true, ptv);
                if (coutRessourceStr!="NULL") {
                    for (const QString &item : coutRessource) {
                        bCi->ajouterCoutRessources(qStringToRessource(item));
                    }
                }
                plateau.ajouterBatimentPlateau(bCi);
                break; }
            case TypeBatiment::Scientifique: {
                BatimentScientifique* bS=new BatimentScientifique(nom, coutPiece, coutChainage, symboleChainage, true, symboleScientifique, ptv);
                if (coutRessourceStr!="NULL") {
                    for (const QString &item : coutRessource) {
                        bS->ajouterCoutRessources(qStringToRessource(item));
                    }
                }
                plateau.ajouterBatimentPlateau(bS);
                break; }
            case TypeBatiment::Commercial: {
                BatimentCommercial* bCo=new BatimentCommercial(nom, coutPiece, coutChainage, symboleChainage, true, piecesRapportes, TypeBatiment::undefined);
                if (coutRessourceStr!="NULL") {
                    for (const QString &item : coutRessource) {
                        bCo->ajouterCoutRessources(qStringToRessource(item));
                    }
                }
                if (nbRessourceProd==2) {
                    for (const QString &item : res) {
                        bCo->AjouterRessourcesStockees(qStringToRessource(item));
                    }
                }
                if (nbRessourceProd==1) {
                    for (const QString &item : res) {
                        bCo->AjouterRessourcesDisponibles(qStringToRessource(item));
                    }
                }
                plateau.ajouterBatimentPlateau(bCo);
                break; }
            case TypeBatiment::Militaire: {
                BatimentMilitaire* bM=new BatimentMilitaire(nom, coutPiece, coutChainage, symboleChainage, true, ptc);
                if (coutRessourceStr!="NULL") {
                    for (const QString &item : coutRessource) {
                        bM->ajouterCoutRessources(qStringToRessource(item));
                    }
                }
                plateau.ajouterBatimentPlateau(bM);
                break; }
            }
        }
    }
    file.close();
    plateau.melangerBatiments();
}


void Partie::genererAgeTrois() {
    // Chemin vers le fichier CSV
    QString filePath = "C:/Users/Agaathe/Documents/cours/GI/P24/LO21/projet 7 pyramides/jeu_code/batimentsAge3_SevenWonders.csv"; //changer l'adresse !

    // Ouverture du fichier en lecture seule
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Impossible d'ouvrir le fichier :" << file.errorString();
    }

    // Lecture du contenu du fichier ligne par ligne
    QTextStream in(&file);
    QString line = in.readLine();
    int counter=0;
    std::set<int> numbers=generateRdmSet(19, 3);
    std::set<int> numbersGuildes=generateRdmSet(26, 4, 20);
    for (std::set<int>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    for (std::set<int>::iterator it = numbersGuildes.begin(); it != numbersGuildes.end(); ++it) {
        std::cout << *it << " ";
    }
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (numbers.find(counter)==numbers.end() && numbersGuildes.find(counter)==numbersGuildes.end()) {
            QStringList values = line.split(";");
            std::string nom=values.value(0).toStdString();
            TypeBatiment type=qStringToTypeBatiment(values.value(1));
            unsigned int coutPiece=values.value(2).toUInt();
            std::string coutChainage=values.value(3).toStdString();
            unsigned int ptv=values.value(4).toUInt();
            unsigned int ptc=values.value(5).toUInt();
            TypeBatiment typePourAvantage=qStringToTypeBatiment(values.value(6));
            SymboleScientifique symboleScientifique=qStringToSymboleScientifique(values.value(7));
            QString coutRessourceStr=values.value(8);
            QStringList coutRessource = coutRessourceStr.split("/");
            switch (type) {
            case TypeBatiment::Ressource: {
                throw "Un batiment ressource ne peut pas etre genere durant l'age III";
                break; }
            case TypeBatiment::Civil: {
                BatimentCivil* bCi=new BatimentCivil(nom, coutPiece, coutChainage, "NULL", true, ptv);
                if (coutRessourceStr!="NULL") {
                    for (const QString &item : coutRessource) {
                        bCi->ajouterCoutRessources(qStringToRessource(item));
                    }
                }
                plateau.ajouterBatimentPlateau(bCi);
                std::cout << *bCi << std::endl;break; }
            case TypeBatiment::Scientifique: {
                BatimentScientifique* bS=new BatimentScientifique(nom, coutPiece, coutChainage, "NULL", true, symboleScientifique, ptv);
                if (coutRessourceStr!="NULL") {
                    for (const QString &item : coutRessource) {
                        bS->ajouterCoutRessources(qStringToRessource(item));
                    }
                }
                plateau.ajouterBatimentPlateau(bS);
                std::cout << *bS << std::endl;break; }
            case TypeBatiment::Commercial: {
                BatimentCommercial* bCo=new BatimentCommercial(nom, coutPiece, coutChainage, "NULL", true, 0, TypeBatiment::undefined);
                if (coutRessourceStr!="NULL") {
                    for (const QString &item : coutRessource) {
                        bCo->ajouterCoutRessources(qStringToRessource(item));
                    }
                }
                bCo->setTypePourGainPieces(typePourAvantage);
                plateau.ajouterBatimentPlateau(bCo);
                std::cout << *bCo << std::endl;break; }
            case TypeBatiment::Militaire: {
                BatimentMilitaire* bM=new BatimentMilitaire(nom, coutPiece, coutChainage, "NULL", true, ptc);
                if (coutRessourceStr!="NULL") {
                    for (const QString &item : coutRessource) {
                        bM->ajouterCoutRessources(qStringToRessource(item));
                    }
                }
                plateau.ajouterBatimentPlateau(bM);
                std::cout << *bM << std::endl;break; }
            case TypeBatiment::Guilde: {
                BatimentGuilde* bG=new BatimentGuilde(nom, coutPiece, coutChainage, "NULL", true, ptc, typePourAvantage);
                if (coutRessourceStr!="NULL") {
                    for (const QString &item : coutRessource) {
                        bG->ajouterCoutRessources(qStringToRessource(item));
                    }
                }
                plateau.ajouterBatimentPlateau(bG);
                std::cout << *bG << std::endl;break; }
            }
        }
        else std::cout << counter << std::endl;
        counter++;
    }
    file.close();
    plateau.melangerBatiments();
}

void Partie::genererPlateauMilitaire(){

    for (unsigned int i=1; i<=8; i++){
        JetonMilitaire zone(i,0);
        if (i==3)
            zone.JetonMilitaire::setPertePiece(2);
        else if (i==6)
            zone.JetonMilitaire::setPertePiece(5);
        plateau.setZonePlateauMilitaire(zone, i-1);
    }
}


int Partie::deplacerPionMilitaire(int i) {
    plateau.setPionMilitaire(i);
    if (i>0){
        for (size_t c=0; c< joueur1.getJetonsProgres().size(); c++){
            if (joueur1.getJetonsProgres()[c].getNomJeton() == "Stratégie"){
                plateau.setPionMilitaire(1);
                break;
            }
        }
    }
    if (i<0){
        for (size_t c=0; c< joueur2.getJetonsProgres().size(); c++){
            if (joueur2.getJetonsProgres()[c].getNomJeton() == "Stratégie"){
                plateau.setPionMilitaire(-1);
                break;
            }
        }
    }

    if (plateau.getEmplacementPionMilitaire() >=9)
        return victoireMilitaire(joueur1);
    //victoire joueur1
    if (plateau.getEmplacementPionMilitaire() <=-9)
        return victoireMilitaire(joueur2);
    //victoire joueur2;
    for (unsigned int j=1; j<=8; j++){
        if (plateau.getEmplacementPionMilitaire()==plateau.getZonePlateauMilitaire(j).getEmplacement()){
            if (!plateau.getZonePlateauMilitaire(j).getUtilise()){
                joueur2.pertePieces(plateau.getZonePlateauMilitaire(j).getPertePiece());
                break;
            }
        }
        if (plateau.getEmplacementPionMilitaire()== - plateau.getZonePlateauMilitaire(j).getEmplacement()){
            if (!plateau.getZonePlateauMilitaire(j).getUtilise()){
                joueur1.pertePieces(plateau.getZonePlateauMilitaire(j).getPertePiece());
                break;
            }
        }
    }
    return 0;
}

int Partie::victoireMilitaire(const Joueur& gagnant){
    std::cout<<"Victoire militaire de "<<gagnant.getPrenom()<<" "<<gagnant.getNom()<<"\n"<<std::endl;
    return 1;
}

int Partie::victoireScientifique (const Joueur& gagnant){
    std::cout<<"Victoire scientifique de "<<gagnant.getPrenom()<<" "<<gagnant.getNom()<<"\n"<<std::endl;
    return 1;
}

void Partie::victoireCivile(){
    const unsigned int scorej1 = joueur1.compterPointsVictoires(plateau, joueur2, false);
    const unsigned int scorej2 = joueur2.compterPointsVictoires(plateau, joueur1, true);
    if (scorej1 == scorej2){
        std::cout<<"égalité des deux joueurs \n"<<std::endl;
    }
    else {
        Joueur& gagnant = joueur1;
        if (scorej1 < scorej2)
            gagnant = joueur2;
        std::cout<<"Victoire de "<<gagnant.getPrenom()<<" "<<gagnant.getNom()<<"\n"<<std::endl;
    }
    std::cout<<"score de "<<joueur1.getPrenom()<<" "<<joueur1.getNom()<<" : "<<scorej1<<std::endl;
    std::cout<<"score de "<<joueur2.getPrenom()<<" "<<joueur2.getNom()<<" : "<<scorej2<<std::endl;
    std::cout<<"Fin de partie"<<std::endl;
}

std::ostream& operator<<(std::ostream& f, const Partie& p) {
    f << "\033[1mPartie --> " << p.getJoueur1().getNom() << " PV : " << p.getJoueur1().compterPointsVictoires(p.getPlateau(), p.getJoueur2())
      << " VS " << p.getJoueur2().getNom() << " PV : " << p.getJoueur2().compterPointsVictoires(p.getPlateau(), p.getJoueur1(), true) << "\033[0m";
    return f;
}
