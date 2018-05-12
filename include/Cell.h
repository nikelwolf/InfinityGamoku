#pragma once

#include <GamokuCommon.h>

using namespace std;

enum class GamokuCellValue {
    Empty,
    Black,
    White
};

class Cell {
public:
    Cell();

    Cell(GamokuCellValue val);

    Cell(int val);

    const GamokuCellValue &value() const;

    GamokuCellValue &value();

    uint64_t ivalue() const;

    uint64_t ivalue();

    void value(GamokuCellValue new_val);

    void value(const Cell &c);

    void value(uint64_t val);

    friend ostream &operator<<(ostream &os, const Cell &c);

private:
    GamokuCellValue _value;
};
