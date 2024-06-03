#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QPushButton>

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    GameWindow(const QString &player1Name, const QString &player2Name, bool player1IsAI, bool player2IsAI, QWidget *parent = nullptr);

signals:
    void exitClicked();

private:
    QLabel *player1Label;
    QLabel *player2Label;
};

#endif // GAMEWINDOW_H
