#include "tetris.h"

tetris::tetris(QWidget *parent): QWidget(parent), grid(new GridDrawer()), figure_(new figure())
{
    grid->setColumns(7);
    grid->setRows(10);

    figure_->setData();
    figure_->setColor();
    int x = (grid->columns() + 2 - figure_->data()[0].size())/2;
    figure_->setX(x);
    int y = 2;
    if(figure_->data()[0][0].size() == 4){
        y = 0;
    }
    figure_->setY(y);
    qDebug() << x << " " << y;

    for(int i = 0; i < grid->columns()+2; i++){
        QVector<int> vectorInt;
        gridInt.push_back(vectorInt);
        for(int j = 0; j < grid->rows()+5; j++){
            if(i == 0 || i == grid->columns() + 1 || j == grid->rows() + 4){
                gridInt[i].push_back(1);
            }else{
                gridInt[i].push_back(0);
            }
        }
    }

    for(int i = 0; i < figure_->data()[0].size(); i++){
        for(int j = 0; j < figure_->data()[0][i].size(); j++){
            if(figure_->data()[0][i][j]){
                gridInt[i + x][j + y] = 2;
            }
        }
    }

    for(int i = 0; i < grid->columns()+2; i++){
        qDebug() << gridInt[i];
    }

    QVector<QVector<QColor>> cellColors = grid->getCellColors();

    for(int i = 1; i < grid->columns()+1; i++){
        for(int j = 4; j < grid->rows()+4; j++){
            if(gridInt[i][j] == 0){
                cellColors[i-1][j-4] = Qt::black;
            }
            if(gridInt[i][j] == 1){
                cellColors[i-1][j-4] = Qt::gray;
            }
            if(gridInt[i][j] == 2){
                cellColors[i-1][j-4] = figure_->color();
            }
        }
    }
    grid->setCellColors(cellColors);
}

GridDrawer *tetris::getGridDrawer()
{
    return grid;
}

void tetris::checkRows()
{
    for(int j = grid->rows() + 3; j >= 0; j--){
        bool ind = true;
        for(int i = 0; i < grid->columns()+2; i++){
            if(gridInt[i][j] != 1){
                ind = false;
                break;
            }
        }
        if(ind){
            for(int i = 0; i < grid->columns()+2; i++){
                gridInt[i].remove(j);
                if(i == 0 || i == grid->columns()+1){
                    gridInt[i].push_front(1);
                }else{
                    gridInt[i].push_front(0);
                }
            }
        }
    }
}

int tetris::checkLastRow()
{
    for(int i = 1; i < grid->columns()+1; i++){
        if(gridInt[i][4] == 1){
            return 0;
        }
    }
    return 1;
}

void tetris::newGame()
{
    for(int i = 1; i < grid->columns()+1; i++){
        for(int j = 0; j < grid->rows()+4; j++){
            gridInt[i][j] = 0;
        }
    }
}

void tetris::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    grid->draw(&painter);
    this->update();
}

void tetris::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "Key event";

    if (event->key() == Qt::Key_Down){
        qDebug() << "Key Down Pressed";
        bool ind = true;
        QVector<QVector<int>> tmpGridInt = gridInt;
        for(int j = grid->rows()+4; j > 0; j--){
            if(ind){
                for(int i = 0; i < grid->columns()+2; i++){
                    if(gridInt[i][j-1] != 1 && gridInt[i][j-1] != 0 && gridInt[i][j] == 1){
                        ind = false;
                        break;
                    }else{
                        if(gridInt[i][j] != 1 && gridInt[i][j-1] != 1){
                            tmpGridInt[i][j] = gridInt[i][j-1];
                            tmpGridInt[i][j-1] = 0;
                        }
                    }
                }
            }else{
                break;
            }
        }
        if(ind){
            gridInt = tmpGridInt;
        }else{
            checkRows();
            qDebug() << checkLastRow();
            if(checkLastRow()){
                emit gameFinished();
                for(int i = 0; i < grid->columns()+2; i++){
                    for(int j = 0; j < grid->rows()+5; j++){
                        if(gridInt[i][j] > 1){
                            gridInt[i][j] = 1;
                        }
                    }
                }
                emit nextStep();
                int x = (grid->columns() + 2 - figure_->data()[0].size())/2;
                figure_->setX(x);
                int y = 2;
                if(figure_->data()[0][0].size() == 4){
                    y = 0;
                }
                figure_->setY(y);

                for(int i = 0; i < figure_->data()[0].size(); i++){
                    for(int j = 0; j < figure_->data()[0][i].size(); j++){
                        if(figure_->data()[0][i][j]){
                            gridInt[i + x][j + y] = 2;
                        }
                    }
                }

                for(int i = 0; i < grid->columns()+2; i++){
                    qDebug() << gridInt[i];
                }
            }
        }
        QVector<QVector<QColor>> cellColors = grid->getCellColors();

        for(int i = 1; i < grid->columns()+1; i++){
            for(int j = 4; j < grid->rows()+4; j++){
                if(gridInt[i][j] == 0){
                    cellColors[i-1][j-4] = Qt::black;
                }
                if(gridInt[i][j] == 1){
                    cellColors[i-1][j-4] = Qt::gray;
                }
                if(gridInt[i][j] == 2){
                    cellColors[i-1][j-4] = figure_->color();
                }
            }
        }
        grid->setCellColors(cellColors);
    }


    if(event->key() == Qt::Key_Space){
        qDebug() << "Key Space Pressed";
        bool ind = true;
        while(ind){
            QVector<QVector<int>> tmpGridInt = gridInt;
            for(int j = grid->rows()+4; j > 0; j--){
                if(ind){
                    for(int i = 0; i < grid->columns()+2; i++){
                        if(gridInt[i][j-1] != 1 && gridInt[i][j-1] != 0 && gridInt[i][j] == 1){
                            ind = false;
                            break;
                        }else{
                            if(gridInt[i][j] != 1 && gridInt[i][j-1] != 1){
                                tmpGridInt[i][j] = gridInt[i][j-1];
                                tmpGridInt[i][j-1] = 0;
                            }
                        }
                    }
                }else{
                    break;
                }
            }
            if(ind){
                gridInt = tmpGridInt;
            }else{
                checkRows();
                qDebug() << checkLastRow();
                if(checkLastRow()){
                    emit gameFinished();
                    for(int i = 0; i < grid->columns()+2; i++){
                        for(int j = 0; j < grid->rows()+5; j++){
                            if(gridInt[i][j] > 1){
                                gridInt[i][j] = 1;
                            }
                        }
                    }
                    emit nextStep();
                    int x = (grid->columns() + 2 - figure_->data()[0].size())/2;
                    figure_->setX(x);
                    int y = 2;
                    if(figure_->data()[0][0].size() == 4){
                        y = 0;
                    }
                    figure_->setY(y);

                    for(int i = 0; i < figure_->data()[0].size(); i++){
                        for(int j = 0; j < figure_->data()[0][i].size(); j++){
                            if(figure_->data()[0][i][j]){
                                gridInt[i + x][j + y] = 2;
                            }
                        }
                    }

                    for(int i = 0; i < grid->columns()+2; i++){
                        qDebug() << gridInt[i];
                    }
                }
            }
            QVector<QVector<QColor>> cellColors = grid->getCellColors();

            for(int i = 1; i < grid->columns()+1; i++){
                for(int j = 4; j < grid->rows()+4; j++){
                    if(gridInt[i][j] == 0){
                        cellColors[i-1][j-4] = Qt::black;
                    }
                    if(gridInt[i][j] == 1){
                        cellColors[i-1][j-4] = Qt::gray;
                    }
                    if(gridInt[i][j] == 2){
                        cellColors[i-1][j-4] = figure_->color();
                    }
                }
            }
            grid->setCellColors(cellColors);
        }
    }
    if (event->key() == Qt::Key_Left){
        qDebug() << "Key Right Pressed";
        bool ind = true;
        QVector<QVector<int>> tmpGridInt = gridInt;
        for(int i = 1; i < grid->columns()+2; i++){
            if(ind){
                for(int j = 0; j < grid->rows() + 5; j++){
                    if(gridInt[i][j] != 1 && gridInt[i][j] != 0 && gridInt[i-1][j] == 1){
                        ind = false;
                        break;
                    }else{
                        if(gridInt[i][j] != 1 && gridInt[i-1][j] != 1){
                            tmpGridInt[i-1][j] = gridInt[i][j];
                            tmpGridInt[i][j] = 0;
                        }
                    }
                }
            }else{
                break;
            }
        }
        if(ind){
            gridInt = tmpGridInt;
        }
        QVector<QVector<QColor>> cellColors = grid->getCellColors();

        for(int i = 1; i < grid->columns()+1; i++){
            for(int j = 4; j < grid->rows()+4; j++){
                if(gridInt[i][j] == 0){
                    cellColors[i-1][j-4] = Qt::black;
                }
                if(gridInt[i][j] == 1){
                    cellColors[i-1][j-4] = Qt::gray;
                }
                if(gridInt[i][j] == 2){
                    cellColors[i-1][j-4] = figure_->color();
                }
            }
        }
        grid->setCellColors(cellColors);
    }

    if (event->key() == Qt::Key_Right){
        qDebug() << "Key Right Pressed";
        bool ind = true;
        QVector<QVector<int>> tmpGridInt = gridInt;
        for(int i = grid->columns()+1; i >0; i--){
            if(ind){
                for(int j = 0; j < grid->rows() + 5; j++){
                    if(gridInt[i-1][j] != 1 && gridInt[i-1][j] != 0 && gridInt[i][j] == 1){
                        ind = false;
                        break;
                    }else{
                        if(gridInt[i][j] != 1 && gridInt[i-1][j] != 1){
                            tmpGridInt[i][j] = gridInt[i-1][j];
                            tmpGridInt[i-1][j] = 0;
                        }
                    }
                }
            }else{
                break;
            }
        }
        if(ind){
            gridInt = tmpGridInt;
        }
        QVector<QVector<QColor>> cellColors = grid->getCellColors();

        for(int i = 1; i < grid->columns()+1; i++){
            for(int j = 4; j < grid->rows()+4; j++){
                if(gridInt[i][j] == 0){
                    cellColors[i-1][j-4] = Qt::black;
                }
                if(gridInt[i][j] == 1){
                    cellColors[i-1][j-4] = Qt::gray;
                }
                if(gridInt[i][j] == 2){
                    cellColors[i-1][j-4] = figure_->color();
                }
            }
        }
        grid->setCellColors(cellColors);
    }
    for(int i = 0; i < grid->columns()+2; i++){
        qDebug() << gridInt[i];
    }
    this->update();
}
