#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QMessageBox>
#include <QMouseEvent>
#include <QGridLayout>

class ClickableLabel : public QLabel {
    Q_OBJECT
public:
    explicit ClickableLabel(QWidget* parent = nullptr) : QLabel(parent) {}

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override {
        emit clicked();
    }
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    QVBoxLayout* mainLayout;
    QGridLayout* phase1Layout;
    QVBoxLayout* player1Area;
    QVBoxLayout* player2Area;
    ClickableLabel* player1Wonders[4];
    ClickableLabel* player2Wonders[4];
    ClickableLabel* selectionAreaLabels[4];
    QLabel* backgroundLabel;

    void loadImages();
    void selectWonder(int index);
    void centerLayout();

private slots:
    void handleWonderSelection(int index);
};

#endif // MAIN_WINDOW_H
