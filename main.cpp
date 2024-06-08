#include <QtWidgets>
#include "MainWindow.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Créer la fenêtre principale
    QWidget window;
    window.setWindowTitle("Grilles en haut et en bas de l'écran");
    window.setWindowState(Qt::WindowMaximized); // Définir l'état initial de la fenêtre sur maximisé

    // Créer le widget contenant les layouts
    QWidget *widget = new QWidget(&window);
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Créer le layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);

    // Créer le layout en haut de l'écran
    QGridLayout *topGridLayout = new QGridLayout;

    // Ajouter des images dans la grille en haut
    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 2; ++col) {
            QLabel *imageLabel = new QLabel;
            QPixmap pixmap("C:/Users/clemc/Desktop/UTC/GI01/LO21/UI_SevenWondersDuel/Merveilles/LaGrandeBibliotheque.png"); // Chemin vers votre image
            imageLabel->setPixmap(pixmap.scaledToWidth(200)); // Redimensionner l'image pour qu'elle ne prenne pas tout l'écran
            imageLabel->setScaledContents(true); // Pour redimensionner l'image pour s'adapter au QLabel
            topGridLayout->addWidget(imageLabel, row, col);
        }
    }

    // Créer un espace élastique pour étirer entre les deux grilles
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 230, QSizePolicy::Minimum, QSizePolicy::Expanding);

    // Créer le layout en bas de l'écran
    QGridLayout *bottomGridLayout = new QGridLayout;

    // Ajouter des images dans la grille en bas
    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 2; ++col) {
            QLabel *imageLabel = new QLabel;
            QPixmap pixmap("C:/Users/clemc/Desktop/UTC/GI01/LO21/UI_SevenWondersDuel/Merveilles/LaGrandeBibliotheque.png"); // Chemin vers votre image
            imageLabel->setPixmap(pixmap.scaledToWidth(200)); // Redimensionner l'image pour qu'elle ne prenne pas tout l'écran
            imageLabel->setScaledContents(true); // Pour redimensionner l'image pour s'adapter au QLabel
            bottomGridLayout->addWidget(imageLabel, row, col);
        }
    }

    // Ajouter les layouts en haut et en bas dans le layout principal
    mainLayout->addLayout(topGridLayout);
    mainLayout->addItem(verticalSpacer);
    mainLayout->addLayout(bottomGridLayout);

    // Afficher la fenêtre
    window.show();

    MainWindow window2;
    window2.show();

    return app.exec();
}
