#include <QtWidgets/QtWidgets>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {


    auto *menuBar = new QMenuBar(this);
    QMenu *menu = new QMenu("&Menu", this);
    menu->setTearOffEnabled(true);
    menu->addAction("&Player vs &Player", this, SLOT( changePlayer() ), Qt::CTRL + Qt::Key_O);
    menu->addAction("Player vs &Bot", this, SLOT( changePlayer() ), Qt::CTRL + Qt::Key_S);
    menu->addSeparator();
    menu->addAction("&Exit", qApp, SLOT(quit()));


    menuBar->addMenu(menu);

    this->setMenuBar(menuBar);



    widget = new QWidget(this);
    gridLayout = new QGridLayout(widget);
    gridLayout->setSpacing(0);
    gridLayout->setMargin(0);

    widget->setStyleSheet(fieldColor);
    field = new QVector<QVector<QPushButton*>*>();
    createUI();

    this->setCentralWidget(widget);
}

void MainWindow::cellChanged(int id)
{
    qDebug()<<"id:"<<id;

    field->at(id/size)->at(id%size)->setEnabled(false);
    field->at(id/size)->at(id%size)->setText(symbol);
    auto x = static_cast<uint64_t>(id % size);
    auto y = static_cast<uint64_t>(size-1 - id / size);


    gameBoard.set_cell(x, y, value);
    if(gameBoard.has_winner() ){
        qDebug("WIN");
        QMessageBox::information(this, "Win", "You win!", QMessageBox::Ok);
        clearField();
    }
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

void MainWindow::moveUp() {
    gameBoard.move_up();
    updateView();
}

void MainWindow::moveDown() {
    gameBoard.move_down();
    updateView();
}

void MainWindow::moveRight() {
    gameBoard.move_right();
    updateView();
}

void MainWindow::moveLeft() {
    gameBoard.move_left();
    updateView();
}

void MainWindow::updateView() {
    for (uint64_t i = 0; i < size; ++i) {
        for (uint64_t j = 0; j < size; ++j) {
            auto cell = gameBoard.get_cell(i, size-1- j).ivalue();
            field->at(j)->at(i)->setEnabled(cell == 0);
            field->at(j)->at(i)->setText(symbols[cell]);
        }
    }
}

void MainWindow::keyPressEvent (QKeyEvent * e)
{
    qDebug()<<"Key pressed"<<e->key();
    switch(e->key()) {
        case Qt::Key_W:
            moveUp();
            break;
        case Qt::Key_S:
            moveDown();
            break;
        case Qt::Key_A:
            moveLeft();
            break;
        case Qt::Key_D:
            moveRight();
            break;
        default:break;
    }
}

MainWindow::~MainWindow() {
    field->clear();
    delete field;
}

void MainWindow::clearField() {
    gameBoard.clear_board();
    for(int i=0; i < size; ++i)
        field->removeAt(0);

    createUI();
}

void MainWindow::createUI() {
    int id = -1;
    for(int i=0; i < size; ++i){
        auto *temp = new QVector<QPushButton*>();
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
}
