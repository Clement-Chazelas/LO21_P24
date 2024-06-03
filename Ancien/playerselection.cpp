#include "playerselection.h"

PlayerSelection::PlayerSelection(QWidget *parent) : QWidget(parent)
{
    player1NameEdit = new QLineEdit(this);
    player2NameEdit = new QLineEdit(this);
    player1IsAICheckbox = new QCheckBox("IA", this);
    player2IsAICheckbox = new QCheckBox("IA", this);
    startGameButton = new QPushButton("Commencer la Partie", this);

    formLayout = new QFormLayout();
    formLayout->addRow("Nom du Joueur 1", player1NameEdit);
    formLayout->addRow("Joueur 1 est une IA", player1IsAICheckbox);
    formLayout->addRow("Nom du Joueur 2", player2NameEdit);
    formLayout->addRow("Joueur 2 est une IA", player2IsAICheckbox);

    layout = new QVBoxLayout(this);
    layout->addLayout(formLayout);
    layout->addWidget(startGameButton);

    setLayout(layout);

    connect(startGameButton, &QPushButton::clicked, [this]() {
        emit startGameClicked(player1NameEdit->text(), player2NameEdit->text(), player1IsAICheckbox->isChecked(), player2IsAICheckbox->isChecked());
    });
}
