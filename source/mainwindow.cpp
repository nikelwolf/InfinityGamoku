#include <QtWidgets/QtWidgets>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), gmv(gmf) {


    auto *menuBar = new QMenuBar(this);
    QMenu *menu = new QMenu("&Menu", this);
    menu->setTearOffEnabled(true);
    menu->addAction("&Player vs &Player", this, SLOT( changePlayer() ), Qt::CTRL + Qt::Key_O);
    menu->addAction("Player vs &Bot", this, SLOT( changePlayer() ), Qt::CTRL + Qt::Key_S);
    menu->addSeparator();
    menu->addAction("&Exit", qApp, SLOT(quit()));


    menuBar->addMenu(menu);

    this->setMenuBar(menuBar);

    QString cellStyle = "background-color: rgb(244, 164, 96); "
                        "border: 1px solid #8a6642; "
                        "color: black";
    QString fieldColor = "background-color: rgb(255, 222, 90); "
                         "border: 1px solid #8f8f91; ";

    auto* widget = new QWidget(this);
    auto* gridLayout = new QGridLayout(widget);
    gridLayout->setSpacing(0);
    gridLayout->setMargin(0);

    widget->setStyleSheet(fieldColor);

    field = new QVector<QVector<QPushButton*>*>();

    int id = -1;
    for(int i=0; i < size; ++i){
        QVector <QPushButton*> *temp = new QVector<QPushButton*>();
        field->push_back(temp);
        for(int j=0; j < size; ++j){
            auto* cell = new QPushButton("", this);
            cell->setFixedSize(cellSize);
            cell->setStyleSheet(cellStyle);
            field->at(i)->push_back(cell);
            cell->setObjectName(QString::number(++id));

            //connect cell.clicked for getting id of cell
            auto *mapper = new QSignalMapper(this);

            connect(mapper, SIGNAL(mapped(int)), this, SLOT(cellChanged(int)));

            connect(cell, SIGNAL(clicked()), mapper, SLOT(map()));
            mapper->setMapping(cell, cell->objectName().toInt());
            //

            gridLayout->addWidget(field->at(i)->at(j), i, j, Qt::AlignCenter);
        }
    }

    this->setCentralWidget(widget);
}

void MainWindow::cellChanged(int id)
{
    field->at(id/size)->at(id%size)->setEnabled(false);
    field->at(id/size)->at(id%size)->setText(symbol);
    auto x = static_cast<uint64_t>(id % size);
    auto y = static_cast<uint64_t>(size-1 - id / size);

    gmv.cell(x, y, value);
    gmv.save_state();


    changePlayer();

    qDebug("Cell #%d", id);
    qDebug("x: %d y: %d", x, y);
}

void MainWindow::changePlayer(){
    if(value == 1) {
        symbol = "O";
        value = 2;
    } else {
        symbol = "X";
        value  = 1;
    }
}
MainWindow::~MainWindow(){

}