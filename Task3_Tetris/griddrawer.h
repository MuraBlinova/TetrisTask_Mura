#ifndef GRIDDRAWER_H
#define GRIDDRAWER_H

#include <QWidget>
#include <QVector>
#include <QPainter>

class GridDrawer : public QWidget {
    Q_OBJECT
    Q_PROPERTY(int columns READ columns WRITE setColumns)
    Q_PROPERTY(int rows READ rows WRITE setRows)
    Q_PROPERTY(int sizeCell READ sizeCell WRITE setSizeCell)

public:
    GridDrawer(QWidget *parent = 0);

    int columns() const;
    void setColumns(int newColumns);

    int rows() const;
    void setRows(int newRows);

    int sizeCell() const;
    void setSizeCell(int newSizeCell);

    QVector<QVector<QColor> > getCellColors() const;
    void setCellColors(const QVector<QVector<QColor> > &newGetCellColors);

    void draw(QPainter *painter);

private:
    int m_columns;
    int m_rows;
    int m_sizeCell;
    QVector<QVector<QColor>> cellColors;
};

#endif // GRIDDRAWER_H
