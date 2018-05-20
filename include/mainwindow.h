#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include "GameView.h"
#include "GamokuField.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
     ~MainWindow();

private:
    //GamokuField* gmf;
    //GameView* gmv;
};

#endif // MAINWINDOW_H
