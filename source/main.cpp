#include "mainwindow.h"
#include <QApplication>

#include <iostream>

#include <GamokuCommon.h>

int main() {
    GamokuField gf;
    gf.cell(0, 0, 0).value(1);
    gf.cell(0, 1, 1).value(2);
    gf.cell(0, 2, 2).value(1);

    gf.cell(1, 0, 0).value(1);
    gf.cell(1, 1, 1).value(2);
    gf.cell(1, 2, 2).value(1);

    gf.cell(2, 0, 0).value(1);
    gf.cell(2, 1, 1).value(2);
    gf.cell(2, 2, 2).value(1);

    gf.cell(3, 0, 0).value(1);
    gf.cell(3, 1, 1).value(2);
    gf.cell(3, 2, 2).value(1);

    GameView gv{gf};
    cout << gf;
    cout << gv;
    gv.move(-3, -3);
    gv.cell(0, 0, 0);
    gv.save_state();
    cout << gv;
    cout << gf;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
