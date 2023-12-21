#include "nextfigure.h"

nextfigure::nextfigure(QWidget *parent):QWidget(parent), grid(new GridDrawer()), figure_(new figure()) {
    figure_->setData();
    figure_->setColor();
    int x = (4 - figure_->data()[0].size())/2;
    figure_->setX(x);
    int y = (4 - figure_->data()[0][0].size())/2;
    figure_->setY(y);

    QVector<QVector<QColor>> cellColors = grid->getCellColors();
    for(int i = 0; i < figure_->data()[0].size(); i++){
        for(int j = 0; j < figure_->data()[0][i].size(); j++){
            if(figure_->data()[0][i][j]){
                cellColors[i + x][j + y] = figure_->color();
            }
        }
    }
    grid->setCellColors(cellColors);
}

void nextfigure::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    grid->draw(&painter);
    this->update();
}

GridDrawer *nextfigure::getGridDrawer()
{
    return grid;
}

void nextfigure::nextStep()
{
    figure* nextFigure_ = new figure();
    nextFigure_->setSpecificColor(figure_->color());
    nextFigure_->setSpecificData(figure_->data());
    emit figureChanged(nextFigure_);
    updateFigure();
}

void nextfigure::updateFigure(){
    figure_->setData();
    figure_->setColor();
    int x = (4 - figure_->data()[0].size())/2;
    figure_->setX(x);
    int y = (4 - figure_->data()[0][0].size())/2;
    figure_->setY(y);

    QVector<QVector<QColor>> cellColors = grid->getCellColors();
    for(int i = 0; i < cellColors.size(); i++){
        for(int j = 0; j < cellColors[i].size(); j++){
            cellColors[i][j] = Qt::gray;
        }
    }
    for(int i = 0; i < figure_->data()[0].size(); i++){
        for(int j = 0; j < figure_->data()[0][i].size(); j++){
            if(figure_->data()[0][i][j]){
                cellColors[i + x][j + y] = figure_->color();
            }
        }
    }
    grid->setCellColors(cellColors);
}
