#include <GamokuCommon.h>

Cell::Cell(): _value{GamokuCellValue::Empty} { }

Cell::Cell(GamokuCellValue val): _value{val} { }

Cell::Cell(int val) {
    switch (val) {
        case 1:
            _value = GamokuCellValue::Black;
            break;
        case 2:
            _value = GamokuCellValue::White;
            break;
        default:
            _value = GamokuCellValue::Empty;
            break;
    }
}

const GamokuCellValue &Cell::value() const {
    return _value;
}

GamokuCellValue &Cell::value() {
    return _value;
}

uint64_t Cell::ivalue() const {
    switch (_value) {
        case GamokuCellValue::Black:
            return 1;
        case GamokuCellValue::White:
            return 2;
        default:
            return 0;
    }
}

uint64_t Cell::ivalue() {
    return const_cast<const Cell &>(*this).ivalue();
}

void Cell::value(GamokuCellValue new_val) {
    _value = new_val;
}

void Cell::value(const Cell &c) {
    _value = c.value();
}

void Cell::value(uint64_t val) {
    switch (val) {
        case 1:
            _value = GamokuCellValue::Black;
            break;
        case 2:
            _value = GamokuCellValue::White;
            break;
        default:
            _value = GamokuCellValue::Empty;
            break;
    }
}

ostream &operator<<(ostream &os, const Cell &c) {
    switch (c._value) {
        case GamokuCellValue::White:
            os << "[☺]";
            break;
        case GamokuCellValue::Black:
            os << "[☻]";
            break;
        default:
            os << "[ ]";
            break;
    }

    return os;
}