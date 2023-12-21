#include "griddrawer.h"


GridDrawer::GridDrawer(QWidget *parent):QWidget(parent), m_columns(3), m_rows(4), m_sizeCell(30)
{
    for (int i = 0; i < m_columns; i++) {
        QVector<QColor> cellsRow = {};
        for (int j = 0; j < m_rows; j++) {
            cellsRow.push_back(Qt::gray);
        }
        cellColors.push_back(cellsRow);
    }
}

int GridDrawer::columns() const
{
    return m_columns;
}

void GridDrawer::setColumns(int newColumns)
{
    m_columns = newColumns;
    cellColors.clear();
    for (int i = 0; i < m_columns; i++) {
        QVector<QColor> cellsRow = {};
        for (int j = 0; j < rows(); j++) {
            cellsRow.push_back(Qt::gray);
        }
        cellColors.push_back(cellsRow);
    }
}

int GridDrawer::rows() const
{
    return m_rows;
}

void GridDrawer::setRows(int newRows)
{
    m_rows = newRows;
    cellColors.clear();
    for (int i = 0; i < columns(); i++) {
        QVector<QColor> cellsRow = {};
        for (int j = 0; j < m_rows; j++) {
            cellsRow.push_back(Qt::gray);
        }
        cellColors.push_back(cellsRow);
    }
}

int GridDrawer::sizeCell() const
{
    return m_sizeCell;
}

void GridDrawer::setSizeCell(int newSizeCell)
{
    m_sizeCell = newSizeCell;
}

QVector<QVector<QColor>> GridDrawer::getCellColors() const
{
    return cellColors;
}

void GridDrawer::setCellColors(const QVector<QVector<QColor> > &newGetCellColors)
{
    cellColors = newGetCellColors;
}

void GridDrawer::draw(QPainter *painter) {
    int cellWidth = m_sizeCell;
    int cellHeight = m_sizeCell;

    for (int i = 0; i < m_columns; i++) {
        for (int j = 0; j < m_rows; j++) {
            painter->setPen(Qt::white);
            painter->setBrush(cellColors[i][j]);
            painter->drawRect(i * cellWidth, j * cellHeight, cellWidth, cellHeight);
        }
    }
    this->update();
}
