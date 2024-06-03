#ifndef PLAYERSELECTION_H
#define PLAYERSELECTION_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QFormLayout>

class PlayerSelection : public QWidget
{
    Q_OBJECT

public:
    PlayerSelection(QWidget *parent = nullptr);

signals:
    void startGameClicked(const QString &player1Name, const QString &player2Name, bool player1IsAI, bool player2IsAI);

private:
    QLineEdit *player1NameEdit;
    QLineEdit *player2NameEdit;
    QCheckBox *player1IsAICheckbox;
    QCheckBox *player2IsAICheckbox;
    QPushButton *startGameButton;
    QVBoxLayout *layout;
    QFormLayout *formLayout;
};

#endif // PLAYERSELECTION_H
