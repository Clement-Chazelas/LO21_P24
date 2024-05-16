#include <QApplication>
#include <QString>
#include <iostream>
#include <string>
#include "partie.h"
#include "utils.h"

using namespace std;

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    Partie p("Ducasse", "Agathe", "Chazelas", "Clement");
    cout << p << endl;

    //p.genererHuitMerveilles(); //generation random parmis un csv

    //p.genererAgeUn(); //idem pour les batiments de l'age I
    //p.genererAgeDeux(); // Age I et Age II ne peuvent pas etre genere en meme temps pour le moment

    //p.selectionDesMerveilles(); //Choix successifs des merveilles
    //Il faut mettre le nom exact pour choisir la carte !

    //p.getPlateau().genererStructureAge1(); Permet de generer la tableau statique (dim 2) pour la structure des cartes

    //p.selectionDesBatiments(); Uniquement si la gen de l'age I a ete effectue

    //cout << p.getPlateau(); //afficher les merveilles et les batiments qu'il y a sur le plateau de jeu

    return 0;
}

/*
To Do list :
    - Generation aleatoire des jetons scientifique sur et hors plateau
    - Finaliser l'ajout des attributs spéciaux des merveilles (ressources disponibles, choix du jeton, choix dans la defausse...
    - Gestion du conflit militaire
    - Assigner la gestion du cycle de vie de tous les objets chacun à une classe
    - Nettoyer le code (retirer les methodes inutilises, nettoyer la memoire pendant la partie, commencer à mettre des commentaires pour les méthodes un peu complexes)
    - faire une méthode dans la classe partie pour faire derouler l'integralite de la partie
    - Photocopier les cartes du jeu
    - S'attaquer à la partie graphique...
*/

