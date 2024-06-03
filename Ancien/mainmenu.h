#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *event);

signals:
    void newGameClicked();

private:
    QPushButton *newGameButton;
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
};

#endif // MAINMENU_H
