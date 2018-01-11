#include "colors.h"



Colors::Colors(int _count, int _h1, int _h2, int _s, int _v):
 count(_count),h1(_h1),h2(_h2),s(_s),v(_v)
{
    colors.clear();

    int hStep = (h2-h1)/count;
    for(int i=0;i<count;i++){

        int h = i*hStep;
        QColor col = QColor::fromHsv(h,v,s);
        colors.append(col);
    }
}

void Colors::setSize(int size)
{
    int hStep = 200/size;
    for(int i=0;i<size;i++){

        int h = i*hStep;
        QColor col = QColor::fromHsv(h,v,s);
        colors.append(col);
    }
}

QColor Colors::get(int i)
{
    if(i>=colors.size())
        return QColor();
    return colors.at(i);
}



