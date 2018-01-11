#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "pieceofpie.h"
#include <QGraphicsPathItem>
#include "colors.h"
#include "tablemodel.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    model = new TableModel(this);

    QList<DataRow*>* dataRows = new QList<DataRow*>();
    dataRows->append(new DataRow("Wilson",334));
    dataRows->append(new DataRow("Water",225));
    dataRows->append(new DataRow("Lake",338));
    dataRows->append(new DataRow("Dog",512));
    dataRows->append(new DataRow("Wild",260));
    dataRows->append(new DataRow("Hunter",411));

    model->setList(dataRows);
    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

 //  connect(ui->tableView,SIGNAL(clicked(QModelIndex)),this, SLOT(selectPieceOfPie(QModelIndex)));
 //  connect(scene,SIGNAL(selectionChanged()),this, SLOT(catchPieSelectionChange()));


    QList<double> values;
    for(DataRow* row: *dataRows)  {
        values.append(row->num);
    }
    int summ = std::accumulate(values.begin(),values.end(),0);

    QList<double> angles;
    for(double val: values)   {
        val= val*1.0;
        double val2= val*360.0;
        double summ2=summ*1.0;
        double val3 = val2/summ2;
        angles.append(val3);
    }


    Pie* pie1 = new Pie(angles);
    scene->addItem(pie1->rectIt);
    connect(ui->tableView,SIGNAL(clicked(QModelIndex)),pie1, SLOT(selectPiece(QModelIndex)));
    connect(scene,SIGNAL(selectionChanged()),pie1, SLOT(catchSelection()));
    connect(pie1,SIGNAL(selectedPice(int)),ui->tableView,SLOT(selectRow(int)));

    Pie* pie2 = new Pie(angles);
    scene->addItem(pie2->rectIt);
    connect(ui->tableView,SIGNAL(clicked(QModelIndex)),pie2, SLOT(selectPiece(QModelIndex)));
    connect(scene,SIGNAL(selectionChanged()),pie2, SLOT(catchSelection()));
    connect(pie2,SIGNAL(selectedPice(int)),ui->tableView,SLOT(selectRow(int)));
    pie2->rectIt->setRect(50,50,100,100);
}


void MainWindow::selectRowFromGraph(int selectedIndex)
{
    int selectedrow =   ui->tableView->model()->index(selectedIndex,0).row();
    ui->tableView->setFocus();
    ui->tableView->selectRow(selectedrow);
}

void MainWindow::selectPieceOfPie(QModelIndex index)
{
    int row = index.row();
    QList<QGraphicsItem*> itemList =  scene->items();

    for(QGraphicsItem* it:itemList )
        it->setSelected(false);

    if(row < itemList.length()){
        itemList.at(row)->setSelected(true);
        bool b=itemList.at(row)->isSelected();
        qDebug()<<b;
    }
    scene->update();
}


void MainWindow::catchPieSelectionChange()
{
    int selectedIndex;
    QList<QGraphicsItem*> itemList =  scene->items();

    for(int i=0;i<itemList.length();i++)
    {
        if(itemList.at(i)->isSelected())
            selectedIndex = i;
    }
    ui->tableView->selectRow(selectedIndex);
}



MainWindow::~MainWindow()
{
    delete ui;
}
