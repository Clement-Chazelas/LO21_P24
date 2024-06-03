#include "mainmenu.h"
#include "qlabel.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    // Créer un widget vide pour déplacer le bouton vers le bas
    QWidget *spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    // Calculer la hauteur du carré pour l'image
    int imageSize = this->height() * 0.4;
    int butonSize = this->width() * 0.6;

    // Charger l'image
    QPixmap originalPixmap("C:/Users/clemc/Desktop/UTC/GI01/LO21/LO21_Projet/SevenWondersImage.png");

    // Redimensionner l'image pour qu'elle ne dépasse pas un carré de 40% de la hauteur de la fenêtre
    QPixmap scaledPixmap = originalPixmap.scaledToHeight(imageSize);

    // Créer une étiquette pour afficher l'image
    QLabel *imageLabel = new QLabel(this);
    imageLabel->setPixmap(scaledPixmap);
    imageLabel->setAlignment(Qt::AlignHCenter);

    // Créer un bouton pour afficher le texte
    newGameButton = new QPushButton("Nouvelle Partie", this);

    // Ajouter le bouton à un layout vertical
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(imageLabel);
    mainLayout->addWidget(spacerWidget); // Ajouter le widget vide en haut pour déplacer le bouton vers le bas
    mainLayout->addWidget(newGameButton, 0, Qt::AlignHCenter); // Centrer le bouton horizontalement
    newGameButton->setFixedSize(butonSize, 80);
    setLayout(mainLayout);

    connect(newGameButton, &QPushButton::clicked, this, &MainMenu::newGameClicked);
}


// Redéfinir la méthode resizeEvent pour mettre à jour la taille du bouton lorsque la fenêtre est redimensionnée
void MainMenu::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    // Calculer la nouvelle largeur du bouton lorsque la fenêtre est redimensionnée
    int buttonWidth = this->width() * 0.6;

    // Ajuster la taille du bouton pour qu'il soit 60% de la largeur de la fenêtre
    newGameButton->setFixedWidth(buttonWidth);
}
