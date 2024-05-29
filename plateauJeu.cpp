#include "plateauJeu.h"
#include <stdio.h>
#include "utils.h"
#include "joueur.h"
#include <QInputDialog>
#include <algorithm> // Pour std::random_shuffle
#include <ctime>     // Pour std::time
#include <cstdlib>   // Pour std::rand et std::srand
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>


using namespace std;

PlateauDeJeu::PlateauDeJeu(size_t c, size_t pio, size_t pla)
    : nb_batiment_plateau(0), nb_jeton_pioche(pio), nb_jeton_plateau(pla), nb_defausse(0), nb_max_defausse(10),
    defausse(new Batiment*[c]), tab(new Batiment*[c]),
    piocheJeton(new JetonProgres[pio]), plateauJeton(new JetonProgres[pla]),
    selectionMerveille(new Merveille[8]), emplacementPionMilitaire(0), nb_merveille_plateau(0),
    plateauMilitaire(new JetonMilitaire[8]) {
    for (size_t i = 0; i < 8; ++i) {
        for (size_t j = 0; j < 13; ++j) {
            structure[i][j]=nullptr;
        }
    }
}



void PlateauDeJeu::prendreBatimentPlateau(size_t i) {
    if(i >= nb_batiment_plateau){
        throw "Erreur : cette carte n'est pas sur le plateau";
    }
    else{
        for(i; i < nb_batiment_plateau-1; i++){
            tab[i] = tab[i + 1];
        }
        nb_batiment_plateau--;
    }
}


void PlateauDeJeu::prendreJetonDansPioche(Joueur& joueur)
{
    // Afficher les jetons dans la pioche
    QStringList jetonsPioche;
    for (size_t i = 0; i < nb_jeton_pioche; ++i) {
        jetonsPioche << QString::fromStdString(piocheJeton[i].getNomJeton());
    }

    // Demander au joueur de choisir un jeton dans la pioche
    bool ok;
    QString jetonChoisi = QInputDialog::getItem(nullptr, "Choisir un jeton dans la pioche", "Jeton à piocher :", jetonsPioche, 0, false, &ok);
    if (ok && !jetonChoisi.isEmpty()) {
        // Trouver le jeton choisi dans la pioche
        JetonProgres jeton;
        for (size_t i = 0; i < nb_jeton_pioche; ++i) {
            if (jetonChoisi.toStdString() == piocheJeton[i].getNomJeton()) {
                jeton = piocheJeton[i];
                break;
            }
        }

        // Ajouter le jeton choisi au joueur
        joueur.ajouterJeton(jeton);

        // Supprimer le jeton de la pioche
        for (size_t i = 0; i < nb_jeton_pioche; ++i) {
            if (jetonChoisi.toStdString() == piocheJeton[i].getNomJeton()) {
                // Déplacer les éléments suivants pour remplir le trou
                for (size_t j = i; j < nb_jeton_pioche - 1; ++j) {
                    piocheJeton[j] = piocheJeton[j + 1];
                }
                // Diminuer le nombre de jetons dans la pioche
                --nb_jeton_pioche;
                break;
            }
        }
    }
}


void PlateauDeJeu::prendreJetonDansPlateau(Joueur& joueur)
{
    // Afficher les jetons sur le plateau
    QStringList jetonsPlateau;
    for (size_t i = 0; i < nb_jeton_plateau; ++i) {
        jetonsPlateau << QString::fromStdString(plateauJeton[i].getNomJeton());
    }

    // Demander au joueur de choisir un jeton du plateau
    bool ok;
    QString jetonChoisi = QInputDialog::getItem(nullptr, "Choisir un jeton du plateau", "Jeton à prendre :", jetonsPlateau, 0, false, &ok);
    if (ok && !jetonChoisi.isEmpty()) {
        // Trouver le jeton choisi dans le plateau
        JetonProgres jeton;
        for (size_t i = 0; i < nb_jeton_plateau; ++i) {
            if (jetonChoisi.toStdString() == plateauJeton[i].getNomJeton()) {
                jeton = plateauJeton[i];
                break;
            }
        }

        // Ajouter le jeton choisi au joueur
        joueur.ajouterJeton(jeton);

        // Supprimer le jeton du plateau
        for (size_t i = 0; i < nb_jeton_plateau; ++i) {
            if (jetonChoisi.toStdString() == plateauJeton[i].getNomJeton()) {
                // Déplacer les éléments suivants pour remplir le trou
                for (size_t j = i; j < nb_jeton_plateau - 1; ++j) {
                    plateauJeton[j] = plateauJeton[j + 1];
                }
                // Diminuer le nombre de jetons sur le plateau
                --nb_jeton_plateau;
                break;
            }
        }
    }
}


void PlateauDeJeu::ajouterMerveillePlateau(Merveille& mer) {
    selectionMerveille[nb_merveille_plateau++]=mer;
}

void PlateauDeJeu::ajouterBatimentPlateau(Batiment* bat) {
    if (nb_batiment_plateau>=20) throw "Pas assez d'espace memoire alloue pour les batiments";
    tab[nb_batiment_plateau++]=bat;
}


Merveille PlateauDeJeu::prendreMerveillePlateau(size_t i) {
    if(i >= nb_merveille_plateau || i>4){
        throw "Erreur : cette merveille n'est pas sur le plateau";
    }
    else{
        Merveille merveilleChoisie(selectionMerveille[i]);
        for(i; i < 4; i++){
            selectionMerveille[i] = selectionMerveille[i+1];
        }
        nb_merveille_plateau--;
        return merveilleChoisie;
    }
}


void PlateauDeJeu::melangerMerveilles() {
    // Initialisation du générateur de nombres aléatoires
    std::srand(std::time(nullptr));
    for (unsigned int i=nb_merveille_plateau-1; i>0; i--) {
        unsigned int j=std::rand()%(i+1);
        if (i!=j) {
            Merveille temp(selectionMerveille[i]);
            selectionMerveille[i]=selectionMerveille[j];
            selectionMerveille[j]=temp;
        }
    }
}

void PlateauDeJeu::melangerBatiments() {
    // Initialisation du générateur de nombres aléatoires
    std::srand(std::time(nullptr));
    for (unsigned int i=nb_batiment_plateau-1; i>0; i--) {
        unsigned int j=std::rand()%(i+1);
        if (i!=j) {
            Batiment* temp(tab[i]);
            tab[i]=tab[j];
            tab[j]=temp;
        }
    }
}

void PlateauDeJeu::genererStructureAge1() {
    bool modele[8][13]={
        {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    unsigned int nbBatInseres=0;
    for (unsigned int i=0; i<5; i++) {
        for (unsigned int j=1; j<12; j++) {
            if (modele[i][j]) {
                structure[i][j]=tab[nbBatInseres];
                tab[nbBatInseres++]=nullptr;
            }
        }
    }
}

void PlateauDeJeu::genererStructureAge2() {
    bool modele[8][13]={
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    unsigned int nbBatInseres=0;
    for (unsigned int i=0; i<5; i++) {
        for (unsigned int j=1; j<12; j++) {
            if (modele[i][j]) {
                structure[i][j]=tab[nbBatInseres];
                tab[nbBatInseres++]=nullptr;
            }
        }
    }
}


void PlateauDeJeu::genererStructureAge3() {
    bool modele[8][13]={
        {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    unsigned int nbBatInseres=0;
    for (unsigned int i=0; i<5; i++) {
        for (unsigned int j=1; j<12; j++) {
            if (modele[i][j]) {
                structure[i][j]=tab[nbBatInseres];
                tab[nbBatInseres++]=nullptr;
            }
        }
    }
}

void PlateauDeJeu::afficherStructure() {
    std::cout << "\n ____________Batiments dans la structure : _________\n";
    for (unsigned int i=0; i<7; i++) {
        for (unsigned int j=1; j<12; j++) {
            if (structure[i][j]!=nullptr) {
                std::cout << *(structure[i][j]);
            }
        }
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    }
}

void PlateauDeJeu::afficherSelectionnable() {
    std::cout << "\n ____________Batiments a selectionner : _________\n";
    for (unsigned int i=0; i<8; i++) {
        for (unsigned int j=1; j<13; j++) {
            if (structure[i][j]!=nullptr && structure[i+1][j-1]==nullptr && structure[i+1][j+1]==nullptr) {
                std::cout << i << " " << j << " " << *(structure[i][j]);
            }
        }
    }
}


Batiment* PlateauDeJeu::choisirBatiment(bool j2) {
    bool ok1;
    QString windowJoueur = j2 ? "Joueur 2" : "Joueur 1";
    QString batimentChoisie = QInputDialog::getText(nullptr, windowJoueur, "Batiment choisie :", QLineEdit::Normal, "", &ok1);
    for (unsigned int i=0; i<7; i++) {
        for (unsigned int j=1; j<12; j++) {
            if (structure[i][j]!=nullptr && structure[i+1][j-1]==nullptr && structure[i+1][j+1]==nullptr && batimentChoisie.toStdString()==structure[i][j]->getNom()) {
                Batiment* temp=structure[i][j];
                structure[i][j]=nullptr;
                nb_batiment_plateau--;
                return temp;
            }
        }
    }
    throw "Le batiment choisie n'existe pas sur le plateau de jeu ou n'est pas accessible";
}


Merveille PlateauDeJeu::choisirMerveille(bool j2) {
    bool ok;
    QString windowJoueur;
    if (j2) windowJoueur="Joueur 2";
    else windowJoueur="Joueur 1";
    QString merveilleChoisie = QInputDialog::getText(nullptr, windowJoueur, "Merveille choisie :", QLineEdit::Normal, "", &ok);
    for (unsigned int i=0; i<min(4, nb_merveille_plateau); i++) {
        if (merveilleChoisie.toStdString()==selectionMerveille[i].getNom()) return prendreMerveillePlateau(i);
    }
    throw "La merveille choisie n'existe pas sur le plateau de jeu";
}

void PlateauDeJeu::setDefausse(Batiment& bat) {
    if( nb_defausse >= nb_max_defausse){
        Batiment** newdefausse = new Batiment*[nb_max_defausse*2];
        for(int i = 0; i < nb_defausse; i++){
            newdefausse[i] = defausse[i];
        }
        Batiment **old = defausse;
        defausse = newdefausse;
        nb_max_defausse*=2;
        delete[] old;
    }
    defausse[nb_defausse++] = &bat;
}


Batiment* PlateauDeJeu::piocher(int i) {
    if(i >= nb_defausse){
        throw "Erreur : cette carte n'est pas dans la pioche";
    }
    else{
        Batiment *bat = defausse[i];
        for(int j; j < nb_defausse; j++){
            defausse[j] = defausse[j + 1];
        }
        return bat;
    }
}


void PlateauDeJeu::genererJetons() {
    std::vector<JetonProgres> jetons;
    std::ifstream fichier("C:/Users/Agaathe/Documents/cours/GI/P24/LO21/projet 7 pyramides/jeu_code/jeton_progres_SevenWonders.csv");
    std::string ligne;

    int ligne_numero = 0;

    // Ignorer l'en-tête et gérer le BOM
    std::getline(fichier, ligne);
    if (!ligne.empty() && ligne[0] == '\xEF' && ligne[1] == '\xBB' && ligne[2] == '\xBF') {
        ligne = ligne.substr(3);  // Supprimer le BOM
    }

    while (std::getline(fichier, ligne)) {
        ligne_numero++;
        std::istringstream ss(ligne);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(ss, token, ';')) {  // Utiliser ';' comme séparateur
            tokens.push_back(token);
        }

        if (tokens.size() == 3) {
            std::string nom = tokens[0];
            std::string effet = tokens[1];
            int points;
            try {
                points = std::stoi(tokens[2]);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Erreur de conversion pour les points de victoire : " << tokens[2] << " à la ligne " << ligne_numero << std::endl;
                continue;
            }
            JetonProgres jeton(nom, effet, points);
            jetons.push_back(jeton);
        } else {
            std::cerr << "Ligne invalide (tokens attendus: 3, obtenus: " << tokens.size() << ") dans le fichier CSV à la ligne " << ligne_numero << " : " << ligne << std::endl;
        }
    }

    fichier.close();

    if (jetons.size() < (nb_jeton_pioche + nb_jeton_plateau)) {
        std::cerr << "Nombre de jetons insuffisant pour remplir la pioche et le plateau" << std::endl;
        return;
    }

    // Fonction pour distribuer les jetons aléatoirement dans les tableaux piocheJeton et plateauJeton

    nb_jeton_pioche = 3;
    nb_jeton_plateau = 5;

    // Mélanger aléatoirement les jetons
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(jetons.begin(), jetons.end(), g);

    // Distribuer les jetons dans les tableaux piocheJeton et plateauJeton
    for (int i = 0; i < nb_jeton_pioche; ++i) {
        piocheJeton[i] = jetons[i];
    }

    for (int i = 0; i < nb_jeton_plateau; ++i) {
        plateauJeton[i] = jetons[nb_jeton_pioche + i];
    }
}

void PlateauDeJeu::setZonePlateauMilitaire(JetonMilitaire& zone, unsigned int i) {
    if (i>=8) throw "Pas assez d'espace memoire alloue pour le plateau militaire.";
    plateauMilitaire[i] = zone;
}

std::ostream& operator<<(std::ostream& f, const PlateauDeJeu& pla) {
    f << "Merveilles sur le plateau : " << std::endl;
    for (unsigned int i=0; i<pla.getNb_merveille_plateau(); i++) f << pla.getSelectionMerveille()[i] << std::endl;
    f << "Batiments sur le plateau : " << pla.getNb_batiment_plateau() << std::endl;
    for (unsigned int i=0; i<pla.getNb_batiment_plateau(); i++) f << *(pla.getTab()[i]);
    return f;
}
