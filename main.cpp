#include <QtWidgets>
#include "PyramidWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Créer la fenêtre principale
    QWidget mainWidget;
    mainWidget.setWindowTitle("Affichage des Deux Fenêtres");
    mainWidget.setWindowState(Qt::WindowMaximized);

    // Créer le layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout(&mainWidget);

    // Créer le layout en haut de l'écran
    QGridLayout *topGridLayout = new QGridLayout;

    // Ajouter des images dans la grille en haut
    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 2; ++col) {
            QLabel *imageLabel = new QLabel;
            QPixmap pixmap("C:/Users/clemc/Desktop/UTC/GI01/LO21/UI_SevenWondersDuel/Merveilles/LaGrandeBibliotheque.png"); // Chemin vers votre image
            imageLabel->setPixmap(pixmap.scaled(200, 100, Qt::KeepAspectRatio)); // Ajuster la taille de l'image
            imageLabel->setFixedSize(200, 100); // Définir une taille fixe pour les QLabel
            imageLabel->setScaledContents(true); // Pour redimensionner l'image pour s'adapter au QLabel
            topGridLayout->addWidget(imageLabel, row, col);
        }
    }

    // Ajouter la grille du haut au layout principal
    mainLayout->addLayout(topGridLayout);

    // Créer un espace élastique pour séparer la grille du haut et la pyramide
    mainLayout->addStretch();

    // Créer la pyramide
    PyramidWidget *pyramidWidget = new PyramidWidget(&mainWidget);

    // Ajouter la pyramide au layout principal, centrée horizontalement
    QHBoxLayout *pyramidLayout = new QHBoxLayout;
    pyramidLayout->addStretch();
    pyramidLayout->addWidget(pyramidWidget);
    pyramidLayout->addStretch();

    mainLayout->addLayout(pyramidLayout);

    // Ajouter un espace élastique pour séparer la pyramide et la grille du bas
    mainLayout->addStretch();

    // Créer le layout en bas de l'écran
    QGridLayout *bottomGridLayout = new QGridLayout;

    // Ajouter des images dans la grille en bas
    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 2; ++col) {
            QLabel *imageLabel = new QLabel;
            QPixmap pixmap("C:/Users/clemc/Desktop/UTC/GI01/LO21/UI_SevenWondersDuel/Merveilles/LaGrandeBibliotheque.png"); // Chemin vers votre image
            imageLabel->setPixmap(pixmap.scaled(200, 100, Qt::KeepAspectRatio)); // Ajuster la taille de l'image
            imageLabel->setFixedSize(200, 100); // Définir une taille fixe pour les QLabel
            imageLabel->setScaledContents(true); // Pour redimensionner l'image pour s'adapter au QLabel
            bottomGridLayout->addWidget(imageLabel, row, col);
        }
    }

    // Ajouter la grille du bas au layout principal
    mainLayout->addLayout(bottomGridLayout);

    // Ajuster les marges et les alignements pour placer les grilles en haut à gauche et en bas à gauche
    mainLayout->setContentsMargins(20, 20, 20, 20); // Ajuster les marges pour positionner les grilles
    topGridLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft); // Alignement de la grille du haut
    bottomGridLayout->setAlignment(Qt::AlignBottom | Qt::AlignLeft); // Alignement de la grille du bas

    // Afficher la fenêtre principale
    mainWidget.show();

    return app.exec();
}















