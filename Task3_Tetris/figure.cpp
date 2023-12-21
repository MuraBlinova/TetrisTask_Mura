#include "figure.h"
#include <QRandomGenerator>

figure::figure()
{
    m_x = 0;
    m_y = 0;
    m_color = QColor(Qt::red);
    m_data = {{{1}}};
}

int figure::x() const
{
    return m_x;
}

void figure::setX(int newX)
{
    m_x = newX;
}

int figure::y() const
{
    return m_y;
}

void figure::setY(int newY)
{
    m_y = newY;
}

int figure::condition() const
{
    return m_condition;
}

void figure::setCondition(int newCondition)
{
    m_condition = newCondition;
}

QColor figure::color() const
{
    return m_color;
}

void figure::setColor()
{
    QRandomGenerator *rg = QRandomGenerator::global();
    int randomNumber = rg->bounded(0, 6);

    QVector<QColor> colorRand = {Qt::red, Qt::blue, Qt::green, Qt::yellow, Qt::cyan, Qt::magenta};
    m_color = colorRand[randomNumber];
}

void figure::setSpecificColor(QColor color_)
{
    m_color = color_;
}

QVector<QVector<QVector<bool>>> figure::data() const
{
    return m_data;
}

void figure::setData()
{
    QRandomGenerator *rg = QRandomGenerator::global();
    int randomNumber = rg->bounded(1, 7);
    switch (randomNumber) {
    case 1:
        m_data = {{{1,1,1,1}}, {{1},{1},{1},{1}}};
        break;
    case 2:
        m_data = {{{1,0},{1,1},{1,0}},
                  {{1,1,1},{0,1,0}},
                  {{0,1},{1,1},{0,1}},
                  {{0,1,0},{1,1,1}}
                  };
        break;
    case 3:
        m_data = {{{1,1},{1,0},{1,0}},
            {{1,1,1},{0,0,1}},
            {{0,1},{0,1},{1,1}},
            {{1,0,0},{1,1,1}}
        };
        break;
    case 4:
        m_data = {{{1,1},{0,1},{0,1}},
            {{0,0,1},{1,1,1}},
            {{1,0},{1,0},{1,1}},
            {{1,1,1},{1,0,0}}
        };
        break;
    case 5:
        m_data = {{{1,0},{1,1},{0,1}},
                  {{0,1,1},{1,1,0}}
        };
        break;
    case 6:
        m_data = {{{0,1},{1,1},{1,0}},
                  {{1,1,0},{0,1,1}}
        };
        break;
    default:
        break;
    }
}

void figure::setSpecificData(QVector<QVector<QVector<bool>>> data_){
    m_data = data_;
}

void figure::nextCondition(){
    setCondition((condition() + 1)%data().size());
}
