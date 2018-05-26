#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    //gmf = new GamokuField();
    //gmv = new GameView(*gmf);
    int size = 3;
    QString cellColor = "background-color: rgb(244, 164, 96); "
                        "border: 2px solid #8f8f91; "
                        "border-radius: 6px;";
    QString fieldColor = "background-color: rgb(255, 218, 185); "
                         "border: 4px solid #8f8f91; ";

    QVector < QVector<QPushButton*>* >  *field = new QVector<QVector<QPushButton*>*>();

    QWidget* widget = new QWidget(this);
    auto * gridl = new QGridLayout(widget);

    widget->setStyleSheet(fieldColor);
    for(int i=0; i < size; ++i){
        QVector <QPushButton*> *temp = new QVector<QPushButton*>();
        field->push_back(temp);
        for(int j=0; j < size; ++j){
            QPushButton* btn = new QPushButton("", this);
            btn->setFixedSize(50,50);
            btn->setStyleSheet(cellColor);

            field->at(i)->push_back(btn);

            gridl->addWidget(field->at(i)->at(j), i, j, Qt::AlignCenter);
        }
    }

    this->setCentralWidget(widget);


}

MainWindow::~MainWindow() {

}
