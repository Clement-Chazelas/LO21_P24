#include "partie.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <set>
#include "cartes.h"
#include "utils.h"
#include "QInputDialog"


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

void Partie::selectionDesBatiments() {
    try {
        bool j2=false;
        bool running=true;
        while (plateau.getNb_batiment_plateau()>0 && running) {
            std::cout << *this << std::endl;
            if (!j2) {
                std::cout << joueur1 << std::endl;
                plateau.afficherSelectionnable();
                bool ok2;
                Batiment* bat(plateau.choisirBatiment());
                // Demander au joueur de choisir une option
                QStringList options;
                options << "Construire" << "Defausser" << "Construire Merveille";
                QString choix = QInputDialog::getItem(nullptr, "Joueur 1", "Choisissez une option:", options, 0, false, &ok2);
                if (choix=="Construire") {
                    if (joueur1.coutAchat(bat, joueur2)<=joueur1.getnbPieces()) {
                        joueur1.pertePieces(joueur1.coutAchat(bat, joueur2));
                        joueur1.ajouterBatiment(bat);
                        plateau.deplacerPionMilitaire(bat->getNbPointsCombats());
                        if (joueur1.checkVictoireScientifique()==6) {
                            std::cout << "Le joueur 1 a gagne par la victoire scientifique !" << std::endl;
                            running = false;
                        }
                    }
                    else std::cout << "Vous n'avez pas assez d'argent pour acheter le batiment" << std::endl;
                }
                else if (choix=="Defausser") joueur1.gainPieces(joueur1.gainDefausse());
                else if (choix=="Construire Merveille") joueur1.choisirMerveilleInactive();
            }
            else {
                std::cout << joueur2 << std::endl;
                plateau.afficherSelectionnable();
                bool ok2;
                Batiment* bat(plateau.choisirBatiment(j2));
                // Demander au joueur de choisir une option
                QStringList options;
                options << "Construire" << "Defausser" << "Construire Merveille";
                QString choix = QInputDialog::getItem(nullptr, "Joueur 2", "Choisissez une option:", options, 0, false, &ok2);
                if (choix=="Construire") {
                    if (joueur2.coutAchat(bat, joueur1)<=joueur2.getnbPieces()) {
                        joueur2.pertePieces(joueur2.coutAchat(bat, joueur1));
                        joueur2.ajouterBatiment(bat);
                        plateau.deplacerPionMilitaire(-bat->getNbPointsCombats());
                        if (joueur2.checkVictoireScientifique()==6) {
                            std::cout << "Le joueur 2 a gagne par la victoire scientifique !" << std::endl;
                            running = false;
                        }
                    }
                    else std::cout << "Vous n'avez pas assez d'argent pour acheter le batiment" << std::endl;
                }
                else if (choix=="Defausser") joueur2.gainPieces(joueur2.gainDefausse());
                else if (choix=="Construire Merveille") joueur2.choisirMerveilleInactive();
                std::cout << joueur2 << std::endl << joueur2.coutAchat(bat, joueur1) << std::endl;
            }
            if (plateau.getEmplacementPionMilitaire()>=9) {
                std::cout << "Le joueur 1 a gagne par la victoire militaire !" << std::endl;
                running=false;
            }
            else if (plateau.getEmplacementPionMilitaire()<=-9) {
                std::cout << "Le joueur 2 a gagne par la victoire militaire !" << std::endl;
                running=false;
            }
            std::cout << "Plateau Militaire : " << plateau.getEmplacementPionMilitaire() << std::endl;
            j2=!j2;
        }
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
    QString filePath = "C:/Users/cheva/OneDrive/Bureau/Qt/Edition_LO21/batimentsAge2_SevenWonders.csv"; //changer l'adresse !

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
    QString filePath = "C:/Users/cheva/OneDrive/Bureau/Qt/Edition_LO21/batimentsAge3_SevenWonders.csv"; //changer l'adresse !

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


std::ostream& operator<<(std::ostream& f, const Partie& p) {
    f << "\033[1mPartie --> " << p.getJoueur1().getNom() << " PV : " << p.getJoueur1().compterPointsVictoires(p.getPlateau())
      << " VS " << p.getJoueur2().getNom() << " PV : " << p.getJoueur2().compterPointsVictoires(p.getPlateau(), true) << "\033[0m";
    return f;
}

