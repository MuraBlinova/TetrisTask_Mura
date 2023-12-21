#ifndef FIGURE_H
#define FIGURE_H

#include <QObject>
#include <QColor>
#include <QVector>

class figure : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int x READ x WRITE setX)
    Q_PROPERTY(int y READ y WRITE setY)
    Q_PROPERTY(int condition READ condition WRITE setCondition)

public:
    figure();
    int x() const;
    void setX(int newX);
    int y() const;
    void setY(int newY);
    int condition() const;
    void setCondition(int newCondition);
    QColor color() const;
    void setColor();
    QVector<QVector<QVector<bool>>> data() const;
    void setData();
    void setSpecificColor(QColor color_);
    void setSpecificData(QVector<QVector<QVector<bool>>> data_);
    void nextCondition();

private:
    int m_x;
    int m_y;
    int m_condition;
    QColor m_color;
    QVector<QVector<QVector<bool>>> m_data;
};

#endif // FIGURE_H
