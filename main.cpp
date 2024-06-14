#include <QApplication>
#include <QString>
#include <iostream>
#include <string>
#include "partie.h"
#include "utils.h"

using namespace std;


int mafonction() {

    Partie p("Ducasse", "Agathe", "Chazelas", "Clement", true, true);
    cout << p << endl;



    p.genererHuitMerveilles(); //generation random parmis un csv pour choisir 8 merveilles
    p.selectionDesMerveilles(); //Choix successifs des merveilles


    p.getSetPlateau().genererJetons();

    p.genererAgeUn(); //generation random parmis un csv pour exclure 3 batiments
    p.getSetPlateau().genererStructureAge1(); //generation de la structure plateau des batiments de l'age 1
    if (p.selectionDesBatiments(1)){
        std::cout << "Fin de partie après âge 1" << std::endl;
        return 1;
    }
    //Choix successifs des batiments

    std::cout<<"fin age1";
    p.genererAgeDeux();
    p.getSetPlateau().genererStructureAge2();
    if (p.selectionDesBatiments(2)){
        std::cout << "Fin de partie après âge 2" << std::endl;
        return 2;
    }

    std::cout<<"fin age2";
    p.genererAgeTrois();
    p.getSetPlateau().genererStructureAge3();
    if (p.selectionDesBatiments(3)){
        std::cout << "Fin de partie après âge 3" << std::endl;
        return 3;
    }

    std::cout<<"fin age3";
    p.victoireCivile();
    return 0;

}

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    mafonction();
    return 0;

    /*
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
*/
}


/*
To Do list pour le back_end :
    - Creer une IA simple
    - Permettre aux joueurs d'utiliser les effets des merveilles (qui sont pour la plupart déjà implémentés)
    - prendre en compte les batiments guilde dans le calcul des points de victoire
    - calculer les gains rapportés par la construction des batiments guildes
    - concernant les jetons il reste à coder (du plus facile au plus dur) : Loi, Theologie, Mathematiques, Economie, Architecture, Maconnerie et Urbanisme (attention ce n'est pas le plus important !)
    - Nettoyer le code
    - Tester le code sous toutes ses coutures
*/
