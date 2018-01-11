#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsScene>

#include "tablemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void selectRowFromGraph(int selectedIndex);
public slots:
    void selectPieceOfPie(QModelIndex index);
    void catchPieSelectionChange();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    TableModel *model;
};

#endif // MAINWINDOW_H
