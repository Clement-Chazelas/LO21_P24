#include "PyramidWidget.h"

PyramidWidget::PyramidWidget(QWidget *parent) : QWidget(parent) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Créer le layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Ajouter un espace élastique en haut pour centrer verticalement
    mainLayout->addStretch();

    // Créer un layout horizontal pour centrer horizontalement
    QHBoxLayout *horizontalLayout = new QHBoxLayout;

    // Ajouter un espace élastique à gauche pour centrer horizontalement
    horizontalLayout->addStretch();

    // Créer une grille pour la pyramide
    QGridLayout *pyramidLayout = new QGridLayout;

    // Ajouter les widgets pour former la pyramide
    int numRows = 5; // Nombre de lignes dans la pyramide
    int widgetWidth = 100; // Largeur des widgets

    for (int row = 0; row < numRows; ++row) {
        int numWidgets = row + 2;
        int startCol = (numRows - row - 1);
        for (int col = 0; col < numWidgets; ++col) {
            QStackedWidget *stackedWidget = new QStackedWidget;

            // Créer le bouton avec l'image
            QPushButton *imageButton = new QPushButton;
            QPixmap pixmap("C:/Users/clemc/Desktop/UTC/GI01/LO21/UI_SevenWondersDuel/BatAge1/Dos.png"); // Chemin vers votre image
            imageButton->setIcon(pixmap);
            imageButton->setIconSize(QSize(75, 150));
            imageButton->setFixedSize(75, 150);
            imageButton->setFlat(true); // Pour supprimer les bordures du bouton

            // Ajouter le bouton et un widget vide au QStackedWidget
            QWidget *emptyWidget = new QWidget;
            stackedWidget->addWidget(imageButton);
            stackedWidget->addWidget(emptyWidget);

            // Connecter le signal clicked du bouton pour afficher le widget vide
            connect(imageButton, &QPushButton::clicked, [stackedWidget]() {
                stackedWidget->setCurrentIndex(1); // Afficher le widget vide
            });

            pyramidLayout->addWidget(stackedWidget, row, startCol + 2 * col);
        }
    }

    // Ajouter la grille de la pyramide au layout horizontal
    horizontalLayout->addLayout(pyramidLayout);

    // Ajouter un espace élastique à droite pour centrer horizontalement
    horizontalLayout->addStretch();

    // Ajouter le layout horizontal au layout principal
    mainLayout->addLayout(horizontalLayout);

    // Ajouter un espace élastique en bas pour centrer verticalement
    mainLayout->addStretch();
}
