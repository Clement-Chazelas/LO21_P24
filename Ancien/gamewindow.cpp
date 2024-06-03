#include "gamewindow.h"

GameWindow::GameWindow(const QString &player1Name, const QString &player2Name, bool player1IsAI, bool player2IsAI, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    player1Label = new QLabel("Joueur 1: " + player1Name + (player1IsAI ? " (IA)" : ""), this);
    player2Label = new QLabel("Joueur 2: " + player2Name + (player2IsAI ? " (IA)" : ""), this);

    layout->addWidget(player1Label);
    layout->addWidget(player2Label);
}
