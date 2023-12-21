#ifndef NEXTFIGURE_H
#define NEXTFIGURE_H

#include "griddrawer.h"
#include "figure.h"
#include <QVector>
#include <QPaintEvent>
#include <QKeyEvent>

class nextfigure : public QWidget {
    Q_OBJECT

signals:
    void figureChanged(figure* newFigure);

public slots:
    void nextStep();

public:
    nextfigure(QWidget *parent = 0);
    GridDrawer *getGridDrawer();
    void updateFigure();
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    GridDrawer* grid;
    figure* figure_;
};

#endif // NEXTFIGURE_H
