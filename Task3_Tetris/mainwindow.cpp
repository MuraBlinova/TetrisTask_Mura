#include "mainwindow.h"

#include "griddrawer.h"
#include "tetris.h"
#include "nextfigure.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    tetris *tetris_ = new tetris();
    nextfigure *nextfigure_ = new nextfigure();

    QPushButton *button = new QPushButton("Новая игра");  // Create a QPushButton
    connect(button, &QPushButton::clicked, tetris_, &tetris::newGame);

    connect(tetris_, &tetris::nextStep, nextfigure_, &nextfigure::nextStep);
    connect(nextfigure_, &nextfigure::figureChanged, tetris_, &tetris::onFigureChanged);
//    connect(tetris_, &tetris::gameFinished, this, &MainWindow::gameFinishedApp);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(tetris_);
    layout->addWidget(nextfigure_);
    layout->addWidget(button);

    setCentralWidget(new QWidget);
    centralWidget()->setLayout(layout);


    tetris_->setFocus();
}
MainWindow::~MainWindow() {}

