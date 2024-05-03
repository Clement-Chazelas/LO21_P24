#include "partie.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <random>
#include <set>
#include "cartes.h"



Partie::Partie(const string& n_j1, const string& p_j1, const string& n_j2, const string& p_j2)
    : joueur1(Joueur(n_j1, p_j1)), joueur2(Joueur(n_j2, p_j2)) {}

std::set<int> generateRdmBtw1and12() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 12);

    std::set<int> numbers; // Utiliser un ensemble pour garantir des valeurs uniques

    while (numbers.size() < 4) {
        int num = dis(gen);
        numbers.insert(num);
    }
    return numbers;
}

int Partie::genererQuatreMerveilles() {
    // Chemin vers le fichier CSV
    QString filePath = "C:/Users/cheva/OneDrive/Bureau/Qt/Edition_LO21/merveilles_SevenWonders.csv";

    // Ouverture du fichier en lecture seule
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Impossible d'ouvrir le fichier :" << file.errorString();
        return 1;
    }

    // Lecture du contenu du fichier ligne par ligne
    QTextStream in(&file);
    int counter=0;
    std::set<int> numbers=generateRdmBtw1and12();
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (numbers.find(counter)!=numbers.end()) {
            QStringList values = line.split(";");
            string nom=values.value(0).toStdString();
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
            std::cout << m << std::endl;
        }
        counter++;
    }

    // Fermeture du fichier
    file.close();

}


ostream& operator<<(ostream& f, const Partie& p) {
    f << "Partie --> " << p.getJoueur1() << " VS " << p.getJoueur2();
    return f;
}
