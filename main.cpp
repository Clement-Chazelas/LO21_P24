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


    p.genererHuitMerveilles(); //generation random parmis un csv pour choisir 8 merveilles
    p.selectionDesMerveilles(); //Choix successifs des merveilles

    /*
    p.genererAgeUn(); //generation random parmis un csv pour exclure 3 batiments
    p.getPlateau().genererStructureAge1(); //generation de la structure plateau des batiments de l'age 1
    p.selectionDesBatiments(); //Choix successifs des batiments

    p.genererAgeDeux();
    p.getPlateau().genererStructureAge2();
    p.selectionDesBatiments();

    p.genererAgeTrois();
    p.getPlateau().genererStructureAge3();
    p.selectionDesBatiments();
    */

    p.getPlateau().genererJetons();    //Génération aléatoire des Jetons Progrès

    return 0;
}

/*
To Do list :
    - Finaliser la methode de decompte des points de victoires
    - Finaliser la methode de decompte des symboles scientifiques
    - Ecrire la methode pour supprimer une ressource (manufacture ou primaire) a l'adversaire
    - Ecrire la methode pour choisir un jeton scientifique hors plateau selon les regles du jeu
    - Generation aleatoire des jetons scientifique sur et hors plateau
    - Gestion du conflit militaire
    - Assigner la gestion du cycle de vie de tous les objets chacun à une classe
    - Nettoyer le code (retirer les methodes inutilises, nettoyer la memoire pendant la partie, commencer à mettre des commentaires pour les méthodes un peu complexes)
    - faire une méthode dans la classe partie pour faire derouler l'integralite de la partie
    - Photocopier les cartes du jeu
    - S'attaquer à la partie graphique...
*/

