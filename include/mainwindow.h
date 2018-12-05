#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QtCore/QSignalMapper>
#include <QMenu>
#include <QMenuBar>
#include <QDebug>
#include <QKeyEvent>

#include "GameBoard.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
     ~MainWindow() override;

private:
    QString cellStyle = "background-color: rgb(244, 164, 96); "
                        "border: 1px solid #8a6642; "
                        "color: black";
    QString fieldColor = "background-color: rgb(255, 222, 90); "
                         "border: 1px solid #8f8f91; ";
    QString symbol = "X";
    QStringList symbols{"", "X", "O"};
    uint16_t value = 1;
    const int size = 16;
    const QSize cellSize = {32,32};
    QWidget *widget;
    QGridLayout *gridLayout;
    int x_cur = size/2;
    int y_cur = size/2;
    int x_last;
    int y_last;

    GameBoard gameBoard;

    QVector < QVector<QPushButton*>* >  *field;

    void createUI();
private slots:
    void cellChanged(int id);
    void keyPressEvent (QKeyEvent * e) override;

    void changePlayer();
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void updateView();
    void clearField();
    void playWithBot();
};

#endif // MAINWINDOW_H
