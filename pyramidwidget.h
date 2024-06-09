#ifndef PYRAMIDWIDGET_H
#define PYRAMIDWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QStackedWidget>

class PyramidWidget : public QWidget {
    Q_OBJECT

public:
    PyramidWidget(QWidget *parent = nullptr);
};

#endif // PYRAMIDWIDGET_H
