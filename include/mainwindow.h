#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QtCore/QSignalMapper>
#include <QMenu>
#include <QMenuBar>
#include <QDebug>
#include "GameView.h"
#include "GamokuField.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
     ~MainWindow();

private:

    QString symbol = "X";
    uint16_t value = 1;
    const int size = 16;
    const QSize cellSize = {32,32};

    GamokuField gmf;
    GameView gmv;

    QVector < QVector<QPushButton*>* >  *field;

private slots:
    void cellChanged(int id);

    void changePlayer();
};

#endif // MAINWINDOW_H
