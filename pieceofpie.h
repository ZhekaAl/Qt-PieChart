#ifndef PIECEOFPIE_H
#define PIECEOFPIE_H

#include <QWidget>
#include <QGraphicsItem>
#include <QModelIndex>

//class PieceOfPiePathint (startAngle_, int lengthAngle_
//{


//};


class PieceOfPie : public QGraphicsItem
{
   // Q_OBJECT
public:
    PieceOfPie(double startAngle_,
               double lengthAngle_,
               QColor baseColor_,
               QGraphicsItem *parent = 0
               );
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
signals:

private:
 double startAngle,lengthAngle;
 QColor penColor,alternateColor,baseColor;
 QPainterPath shape() const override;

public slots:
};

class Pie : public QObject
{
    Q_OBJECT
public:
  // static QGraphicsRectItem *getPie(QList<double> angles);
   Pie(QList<double> angles, QObject *par=0);
   QGraphicsRectItem * rectIt;

public slots:
    void selectPiece(QModelIndex index);
signals:
    void selectedPice(int num);
  private slots:
  void catchSelection();

};

#endif // PIECEOFPIE_H

