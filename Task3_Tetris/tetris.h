#ifndef TETRIS_H
#define TETRIS_H

#include "griddrawer.h"
#include "figure.h"
#include "nextfigure.h"
#include <QVector>
#include <QPaintEvent>
#include <QKeyEvent>

class tetris : public QWidget {
    Q_OBJECT

signals:
    void nextStep();
    void gameFinished();

public slots:
    void onFigureChanged(figure* newFigure) {
        figure_ = newFigure;
    }
    void newGame();

public:
    tetris(QWidget *parent = 0);

    GridDrawer *getGridDrawer();
    void checkRows();
    int checkLastRow();


protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    GridDrawer* grid;
    figure* figure_;
    QVector<QVector<int>> gridInt;

};


#endif // TETRIS_H
