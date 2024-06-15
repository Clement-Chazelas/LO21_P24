#include <QApplication>
#include <QString>
#include <iostream>
#include <string>
#include "partie.h"
#include "utils.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "QInputDialog"

using namespace std;


int mafonction(int argc, char *argv[]) {

    QApplication a(argc, argv);

    bool ok1;
    QString windowJoueur = "Joueur 1";
    QString prenomj1 = QInputDialog::getText(nullptr, windowJoueur, "entrez votre prenom : ", QLineEdit::Normal, "", &ok1);

    bool ok2;
    QString nomj1 = QInputDialog::getText(nullptr, windowJoueur, "entrez votre nom : ", QLineEdit::Normal, "", &ok2);

    bool ok3;
    windowJoueur = "Joueur 2";
    QString prenomj2 = QInputDialog::getText(nullptr, windowJoueur, "entrez votre prenom : ", QLineEdit::Normal, "", &ok3);

    bool ok4;
    QString nomj2 = QInputDialog::getText(nullptr, windowJoueur, "entrez votre nom : ", QLineEdit::Normal, "", &ok4);

    bool ok5;
    windowJoueur = "Joueur 1";
    int iaj1 = QInputDialog::getInt(nullptr, windowJoueur, "Si le joueur 1 est une IA entrez 1, sinon entrez 0:", 0, 0, 1, 1, &ok5);

    bool ok6;
    windowJoueur = "Joueur 2";
    int iaj2 = QInputDialog::getInt(nullptr, windowJoueur, "Si le joueur 2 est une IA entrez 1, sinon entrez 0:", 0, 0, 1, 1, &ok6);

     if (!ok1 || !ok2 || !ok3 || !ok4 || !ok5 || !ok6)
        throw "erreur";

    Partie p(nomj1.toStdString(), prenomj1.toStdString(), nomj2.toStdString(), prenomj2.toStdString(), iaj1, iaj2);

    //Partie p("Ducasse", "Agathe", "Chazelas", "Clement", true, true);
    cout << p << endl;

    p.genererHuitMerveilles(); //generation random parmis un csv pour choisir 8 merveilles
    p.selectionDesMerveilles(); //Choix successifs des merveilles

    p.getSetPlateau().genererJetons();


    int i=1;
    bool finDePartie =false;

    while (i<=3 && !finDePartie) {
        switch (i) {
        case 1:
            p.genererAgeUn(); //generation random parmis un csv pour exclure 3 batiments
            p.getSetPlateau().genererStructureAge1(); //generation de la structure plateau des batiments de l'age 1
            break;
        case 2:
            p.genererAgeDeux();
            p.getSetPlateau().genererStructureAge2();
            break;
        case 3:
            p.genererAgeTrois();
            p.getSetPlateau().genererStructureAge3();
            break;
        default:
            throw "erreur";
            break;
        }

        finDePartie = p.selectionDesBatiments(i);
        i++;
    }

    if (finDePartie == false)
        p.victoireCivile();

    return 0;

}

int main(int argc, char *argv[]) {

    mafonction(argc, argv);
    return 0;

}


