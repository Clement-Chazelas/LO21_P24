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

    /*
    p.genererHuitMerveilles(); //generation random parmis un csv pour choisir 8 merveilles
    p.selectionDesMerveilles(); //Choix successifs des merveilles
    */

    /*p.genererAgeUn(); //generation random parmis un csv pour exclure 3 batiments
    p.getPlateau().genererStructureAge1(); //generation de la structure plateau des batiments de l'age 1
    p.selectionDesBatiments(); //Choix successifs des batiments
    p.genererAgeDeux();
    p.getPlateau().genererStructureAge2();
    p.selectionDesBatiments();
    p.genererAgeTrois();
    p.getPlateau().genererStructureAge3();
    p.selectionDesBatiments();*/

    p.getSetPlateau().genererJetons();

    std::cout << "Jetons de la pioche avant choix:\n";
    for (size_t i = 0; i < p.getPlateau().getNb_jeton_pioche(); ++i) {
        std::cout << p.getPlateau().getJetonProgresPioche()[i] << std::endl;
    }

    std::cout << "\nJetons sur le plateau avant choix:\n";
    for (size_t i = 0; i <p.getPlateau().getNb_jeton_plateau(); ++i) {
        std::cout << p.getPlateau().getJetonProgresPlateau()[i] << std::endl;
    }

    // Le joueur 1 prend un jeton dans la pioche
    p.getSetPlateau().prendreJetonDansPioche(p.getSetJoueur1());

    // Le joueur 2 prend un jeton sur le plateau
    p.getSetPlateau().prendreJetonDansPlateau(p.getSetJoueur2());

    // Affichage des jetons des joueurs
    std::cout << "\nJetons de progrès du joueur 1 après choix dans la pioche:\n";
    p.getJoueur1().afficherJetons();

    std::cout << "\nJetons de progrès du joueur 2 après choix sur le plateau:\n";
    p.getJoueur2().afficherJetons();

    // Affichage des jetons restants dans la pioche et sur le plateau
    std::cout << "\nJetons de la pioche après choix:\n";
    for (size_t i = 0; i < p.getPlateau().getNb_jeton_pioche(); ++i) {
        std::cout << p.getPlateau().getJetonProgresPioche()[i] << std::endl;
    }

    std::cout << "\nJetons sur le plateau après choix:\n";
    for (size_t i = 0; i < p.getPlateau().getNb_jeton_plateau(); ++i) {
        std::cout << p.getPlateau().getJetonProgresPlateau()[i] << std::endl;
    }


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
