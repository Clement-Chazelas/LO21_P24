#include "MainWindow.h"
#include <QApplication>
#include <QScreen>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();

    // Taille fixe pour la fenêtre
    setFixedSize(800, 600); // Ajustez ces valeurs selon vos besoins

    // Centrer la fenêtre sur l'écran
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    setGeometry(x, y, width(), height());

    // Connecter le signal clicked() des labels à notre slot
    connect(label1, SIGNAL(clicked()), this, SLOT(onImageClicked()));
    connect(label2, SIGNAL(clicked()), this, SLOT(onImageClicked()));
    connect(label3, SIGNAL(clicked()), this, SLOT(onImageClicked()));
    connect(label4, SIGNAL(clicked()), this, SLOT(onImageClicked()));
}

void MainWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    gridLayout = new QGridLayout(centralWidget);

    label1 = new ClickableLabel();
    label2 = new ClickableLabel();
    label3 = new ClickableLabel();
    label4 = new ClickableLabel();
    emptyLabel1 = new QLabel();
    emptyLabel2 = new QLabel();
    emptyLabel3 = new QLabel();
    emptyLabel4 = new QLabel();

    QPixmap pixmap1("C:/Users/clemc/Desktop/UTC/GI01/LO21/UI_SevenWondersDuel/Merveilles/LaGrandeBibliotheque.png");
    QPixmap pixmap2("C:/Users/clemc/Desktop/UTC/GI01/LO21/UI_SevenWondersDuel/Merveilles/LaGrandeBibliotheque.png");
    QPixmap pixmap3("C:/Users/clemc/Desktop/UTC/GI01/LO21/UI_SevenWondersDuel/Merveilles/LaGrandeBibliotheque.png");
    QPixmap pixmap4("C:/Users/clemc/Desktop/UTC/GI01/LO21/UI_SevenWondersDuel/Merveilles/LaGrandeBibliotheque.png");

    label1->setPixmap(pixmap1.scaledToWidth(400, Qt::SmoothTransformation));
    label1->setAlignment(Qt::AlignCenter);
    label1->setScaledContents(true);
    label1->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    label1->setCursor(Qt::PointingHandCursor);
    label1->setObjectName("label1");

    label2->setPixmap(pixmap2.scaledToWidth(400, Qt::SmoothTransformation));
    label2->setAlignment(Qt::AlignCenter);
    label2->setScaledContents(true);
    label2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    label2->setCursor(Qt::PointingHandCursor);
    label2->setObjectName("label2");

    label3->setPixmap(pixmap3.scaledToWidth(400, Qt::SmoothTransformation));
    label3->setAlignment(Qt::AlignCenter);
    label3->setScaledContents(true);
    label3->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    label3->setCursor(Qt::PointingHandCursor);
    label3->setObjectName("label3");

    label4->setPixmap(pixmap4.scaledToWidth(400, Qt::SmoothTransformation));
    label4->setAlignment(Qt::AlignCenter);
    label4->setScaledContents(true);
    label4->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    label4->setCursor(Qt::PointingHandCursor);
    label4->setObjectName("label4");

    gridLayout->addWidget(label1, 0, 0);
    gridLayout->addWidget(label2, 0, 1);
    gridLayout->addWidget(label3, 1, 0);
    gridLayout->addWidget(label4, 1, 1);

    centralWidget->setLayout(gridLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::onImageClicked() {
    ClickableLabel *clickedLabel = qobject_cast<ClickableLabel*>(sender());
    if (clickedLabel) {
        clickedLabel->hide();
        replaceHiddenImages();

        // Si seulement 2 images restent, cacher l'autre image
        if (visibleCount == 1) {
            label1->hide();
            label2->hide();
            label3->hide();
            label4->hide();
        }
    }
}



void MainWindow::replaceHiddenImages() {
    if (!label1->isVisible()) {
        gridLayout->removeWidget(label1);
        label1->deleteLater();
        label1 = new ClickableLabel();
        gridLayout->addWidget(label1, 0, 0);
        visibleCount--;
    }
    if (!label2->isVisible()) {
        gridLayout->removeWidget(label2);
        label2->deleteLater();
        label2 = new ClickableLabel();
        gridLayout->addWidget(label2, 0, 1);
        visibleCount--;
    }
    if (!label3->isVisible()) {
        gridLayout->removeWidget(label3);
        label3->deleteLater();
        label3 = new ClickableLabel();
        gridLayout->addWidget(label3, 1, 0);
        visibleCount--;
    }
    if (!label4->isVisible()) {
        gridLayout->removeWidget(label4);
        label4->deleteLater();
        label4 = new ClickableLabel();
        gridLayout->addWidget(label4, 1, 1);
        visibleCount--;
    }
}

