#include "mainwindow.h"
#include <QResizeEvent>
#include <QStackedWidget>
#include <QLabel>
#include <QPixmap>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), mainLayout(new QVBoxLayout), phase1Layout(new QGridLayout),
    player1Area(new QVBoxLayout), player2Area(new QVBoxLayout) {

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Set up the main layout as a stack to manage layers
    QStackedWidget* stackedWidget = new QStackedWidget(centralWidget);
    centralWidget->setLayout(new QVBoxLayout);
    centralWidget->layout()->addWidget(stackedWidget);

    // Background label setup
    backgroundLabel = new QLabel(centralWidget);
    backgroundLabel->setPixmap(QPixmap("C:/Users/clemc/Desktop/UTC/GI01/LO21/UI_SevenWondersDuel/Fond.png"));
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setGeometry(0, 0, width(), height());

    // Add background to the stacked layout
    //stackedWidget->addWidget(backgroundLabel);

    // Widget to overlay the background
    QWidget* overlayWidget = new QWidget(centralWidget);
    overlayWidget->setLayout(mainLayout);
    stackedWidget->addWidget(overlayWidget);

    // Configure the main layout
    mainLayout->addLayout(phase1Layout);

    for (int i = 0; i < 4; ++i) {
        player1Wonders[i] = new ClickableLabel();
        connect(player1Wonders[i], &ClickableLabel::clicked, [this, i]() { handleWonderSelection(i); });

        selectionAreaLabels[i] = new ClickableLabel();
        connect(selectionAreaLabels[i], &ClickableLabel::clicked, [this, i]() { handleWonderSelection(i); });

        player2Wonders[i] = new ClickableLabel();
        connect(player2Wonders[i], &ClickableLabel::clicked, [this, i]() { handleWonderSelection(i); });
    }

    // Add the wonders to the grid layout in a 2x2 grid
    phase1Layout->addWidget(selectionAreaLabels[0], 0, 0);
    phase1Layout->addWidget(selectionAreaLabels[1], 0, 1);
    phase1Layout->addWidget(selectionAreaLabels[2], 1, 0);
    phase1Layout->addWidget(selectionAreaLabels[3], 1, 1);

    loadImages();
    centerLayout();
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    backgroundLabel->setGeometry(0, 0, width(), height());
    centerLayout();
}

void MainWindow::loadImages() {
    QStringList imagePaths = {
        "C:/Users/clemc/Desktop/UTC/GI01/LO21/UI_SevenWondersDuel/Merveilles/LaGrandeBibliotheque.png",
        "C:/Users/clemc/Desktop/UTC/GI01/LO21/UI_SevenWondersDuel/Merveilles/LaStatueDeZeus.png",
        "C:/Users/clemc/Desktop/UTC/GI01/LO21/UI_SevenWondersDuel/Merveilles/LaViaAppia.png",
        "C:/Users/clemc/Desktop/UTC/GI01/LO21/UI_SevenWondersDuel/Merveilles/LeCircusMaximus.png"
    };

    for (int i = 0; i < 4; ++i) {
        QPixmap pixmap(imagePaths[i]);
        selectionAreaLabels[i]->setPixmap(pixmap.scaled(300, 200, Qt::KeepAspectRatio));  // Adjust size as needed
    }
}

void MainWindow::handleWonderSelection(int index) {
    QMessageBox::information(this, "Selected", QString("Wonder %1 selected").arg(index + 1));
}

void MainWindow::selectWonder(int index) {
    // Logic for selecting wonder during phase 1
    QMessageBox::information(this, "Selected", QString("Wonder %1 selected").arg(index + 1));
}

void MainWindow::centerLayout() {
    // Calculate the center of the window
    int windowWidth = width();
    int windowHeight = height();

    int gridWidth = phase1Layout->sizeHint().width();
    int gridHeight = phase1Layout->sizeHint().height();

    int leftMargin = (windowWidth - gridWidth) / 2;
    int topMargin = (windowHeight - gridHeight) / 2;

    phase1Layout->setContentsMargins(leftMargin, topMargin, leftMargin, topMargin);
    phase1Layout->setSpacing(10);  // Adjust spacing as needed
}
