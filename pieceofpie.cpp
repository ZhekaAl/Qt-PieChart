#include "pieceofpie.h"
#include <QPainter>
#include <QModelIndex>

#include "colors.h"





//{
//QPainterPath roundRectPath;
//   roundRectPath.moveTo(50, 50);
//  // roundRectPath.arcTo(70.0, 30.0, 10.0, 10.0, 0.0, 90.0);
//   roundRectPath.lineTo(100.0, 50.0);
//    roundRectPath.arcTo(boundingRect(), 0 ,lengthAngle );
//    roundRectPath.lineTo(50, 50);
// //  roundRectPath.arcTo(0.0, 10, 100.0, 100.0, .0, 180*16.0);
//   //roundRectPath.lineTo(20.0, 65.0);
//   //roundRectPath.arcTo(20.0, 60.0, 10.0, 10.0, 180.0, 90.0);
//  // roundRectPath.lineTo(75.0, 70.0);
//  // roundRectPath.arcTo(70.0, 60.0, 10.0, 10.0, 270.0, 90.0);
////   roundRectPath.closeSubpath();

//painter->rotate(startAngle);
//painter->setBrush(QBrush(fillColor));
//painter->drawPath(roundRectPath);


//}

Pie::Pie(QList<double> angles,QObject*par):QObject(par)
{
   // double summ3 = std::accumulate(angles.begin(),angles.end(),0);

   double  startAngle=0.;int i=0;
    Colors colors(angles.size(),0,255,150,150);

    rectIt = new QGraphicsRectItem();

    rectIt->setRect(0,0,200,200);
   // rectIt->setBrush(QBrush(Qt::gray));
    rectIt->setFlag(QGraphicsItem::ItemIsMovable,true);
    QPen pen;
    pen.setColor(Qt::transparent);
    rectIt->setPen(pen);

   // double indent = (360.-summ3)/(angles.size()+1);
    for(double angle:angles)
     {
          PieceOfPie *piece= new PieceOfPie(startAngle,angle,colors.get(i),rectIt);
         // scene->addItem(pie);
          startAngle+=angle;//+indent;
          i++;
      }
}

void Pie::selectPiece(QModelIndex index)
{
    int row = index.row();
    QList<QGraphicsItem*> itemList =  rectIt->childItems();

    for(QGraphicsItem* it:itemList )
        it->setSelected(false);

    if(row < itemList.length()){
        itemList.at(row)->setSelected(true);
       // bool b=itemList.at(row)->isSelected();
       // qDebug()<<b;
    }
}



void Pie::catchSelection()
{
    int selectedIndex;
    QList<QGraphicsItem*> itemList =  rectIt->childItems();

    for(int i=0;i<itemList.length();i++)
    {
        if(itemList.at(i)->isSelected())
            selectedIndex = i;
    }
    emit selectedPice(selectedIndex);
}









PieceOfPie::PieceOfPie(double startAngle_, double lengthAngle_,QColor baseColor_, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    startAngle(startAngle_),
    lengthAngle(lengthAngle_),
    penColor(Qt::black),
    alternateColor(Qt::blue),
    baseColor(baseColor_)

{

    setFlag(QGraphicsItem::ItemIsSelectable,true);
   // setFlag(QGraphicsItem::ItemIsMovable,true);


//    QGraphicsSimpleTextItem* textIt = new QGraphicsSimpleTextItem(this);
//    textIt->setText(QString().setNum(lengthAngle));
//    textIt->setRotation(startAngle_);
//    textIt->setPos(startAngle_,lengthAngle_ );


}





QPainterPath PieceOfPie::shape() const
{
//    QPainterPath roundRectPath;
//    roundRectPath.moveTo(boundingRect().center());
//    roundRectPath.arcTo(boundingRect(), startAngle ,lengthAngle );
//    roundRectPath.closeSubpath();
//    return roundRectPath;

    QRectF rect =  boundingRect();

    double w = rect.width();
    double h =rect.height();



    QRectF smallRect = rect.adjusted(w/4,h/4,w/(-4),h/(-4));


    QPainterPath roundRectPath;
       roundRectPath.moveTo(boundingRect().center());
        roundRectPath.arcTo(boundingRect(), startAngle ,lengthAngle );
        roundRectPath.moveTo(boundingRect().center());
        roundRectPath.arcTo(smallRect, startAngle ,lengthAngle );

       roundRectPath.closeSubpath();
       return roundRectPath;

}


QRectF PieceOfPie::boundingRect() const
{
  //  qreal penWidth = 1;

   return parentItem()->boundingRect();

   // return QRectF(0, 0, 300, 300);
}

void PieceOfPie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
   // painter->drawRoundedRect(-10, -10, 20, 20, 5, 5);


    QRectF rect = boundingRect();

    double w = rect.width();
    double h =rect.height();

  //  double x0 = rect.x();
 //   double y0 = rect.y();


    QRectF smallRect = rect.adjusted(w/4.,h/4.,w/(-4.),h/(-4.));

    QPainterPath roundRectPath;
        roundRectPath.moveTo(boundingRect().center());
        roundRectPath.arcTo(boundingRect(), startAngle ,lengthAngle );
        roundRectPath.moveTo(boundingRect().center());
        roundRectPath.arcTo(smallRect, startAngle ,lengthAngle );

       roundRectPath.closeSubpath();

    //  pF= roundRectPath.boundingRect().center();
    // roundRectPath.addText(pF,QFont(),QString().setNum(lengthAngle));

       QPen pen;
       pen.setColor(Qt::white);
       painter->setPen(pen);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::HighQualityAntialiasing);

    if( isSelected())
        painter->setBrush(QBrush( alternateColor));
    else
        painter->setBrush(QBrush(baseColor));

    painter->drawPath(roundRectPath);

}
