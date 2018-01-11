#ifndef Colors_H
#define Colors_H

#include <QColor>
#include <QVector>

class Colors
{
public:
    Colors(int count,int h1,int h2,int s,int v);

        QVector<QColor> colors;
        void setSize(int size);
        QColor get(int i);
        int count,h1,h2,s,v;

};

#endif // Colors_H
