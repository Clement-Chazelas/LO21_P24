#include <QApplication>
#include <QString>
#include <iostream>
#include <string>
#include "partie.h"
#include "utils.h"
#include <QStackedWidget>
#include "mainmenu.h"
#include "playerselection.h"
#include "gamewindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

using namespace std;





class MainWindow : public QWidget {
    Q_OBJECT
public:
    MainWindow() {
        // Création de la partie
        Partie partie("Joueur1", "Prenom1", "Joueur2", "Prenom2");

        // Configuration de la fenêtre principale
        QVBoxLayout* layout = new QVBoxLayout(this);
        QLabel* label = new QLabel("Sélectionnez une merveille :");
        layout->addWidget(label);

        // Affichage des merveilles à sélectionner
        for (unsigned int i = 0; i < partie.getPlateau().getNb_merveille_plateau(); ++i) {
            QPushButton* button = new QPushButton(QString::fromStdString(partie.getPlateau().getSelectionMerveille()[i].getNom()));
            layout->addWidget(button);

            // Connexion du bouton à une fonction de sélection
            connect(button, &QPushButton::clicked, [this, &partie, i] {
                partie.getSetJoueur1().ajouterMerveille(partie.getSetPlateau().prendreMerveillePlateau(i));
                updateMerveilles(partie);
            });
        }
    }

private slots:
    void updateMerveilles(Partie& partie) {
        // Mettre à jour l'interface après sélection d'une merveille
        // Par exemple, masquer les boutons déjà sélectionnés
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}











/*
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

    /*p.getSetPlateau().genererJetons();

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
    }*/



    /*QApplication app(argc, argv);

    QStackedWidget stackedWidget;

    MainMenu mainMenu;
    PlayerSelection playerSelection;
    GameWindow *gameWindow = nullptr;

    stackedWidget.addWidget(&mainMenu);
    stackedWidget.addWidget(&playerSelection);

    QObject::connect(&mainMenu, &MainMenu::newGameClicked, [&stackedWidget, &playerSelection]() {
        stackedWidget.setCurrentIndex(1);
        playerSelection.showMaximized(); // Utiliser showMaximized() ici
    });

    QObject::connect(&playerSelection, &PlayerSelection::startGameClicked, [&stackedWidget, &gameWindow](const QString &player1Name, const QString &player2Name, bool player1IsAI, bool player2IsAI) {
        gameWindow = new GameWindow(player1Name, player2Name, player1IsAI, player2IsAI);
        stackedWidget.addWidget(gameWindow);
        stackedWidget.setCurrentIndex(2);
        gameWindow->showMaximized(); // Utiliser showMaximized() ici

        QObject::connect(gameWindow, &GameWindow::exitClicked, &QApplication::quit);
    });

    stackedWidget.showMaximized(); // Utiliser showMaximized() ici

    return app.exec();*//*




    return 0;
}*/

/*
To Do list :
    - Generation aleatoire des jetons scientifique sur et hors plateau
    - Finaliser l'ajout des attributs spéciaux des merveilles (ressources disponibles, choix du jeton, choix dans la defausse...
    - Gestion du conflit militaire
    - Assigner la gestion du cycle de vie de tous les objets chacun à une classe
    - Nettoyer le code (retirer les methodes inutilises, nettoyer la memoire pendant la partie, commencer à mettre des commentaires pour les méthodes un peu complexes)
    - faire une méthode dans la classe partie pour faire derouler l'integralite de la partie
*/

