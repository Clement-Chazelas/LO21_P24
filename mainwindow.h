#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QMouseEvent>


class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = Q_NULLPTR) : QLabel(parent) {}

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) {
        if (event->button() == Qt::LeftButton) {
            emit clicked();
        }
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onImageClicked();

private:
    void setupUI();
    void replaceHiddenImages();
    int visibleCount = 4;

    ClickableLabel *label1;
    ClickableLabel *label2;
    ClickableLabel *label3;
    ClickableLabel *label4;
    QLabel *emptyLabel1;
    QLabel *emptyLabel2;
    QLabel *emptyLabel3;
    QLabel *emptyLabel4;

    QGridLayout *gridLayout;
};

#endif // MAINWINDOW_H
