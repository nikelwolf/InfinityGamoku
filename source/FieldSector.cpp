#include <GamokuCommon.h>

ostream &operator<<(ostream &os, SectorType s) {
    switch (s) {
        case SectorType::UpperLeft:
            os << "UpperLeft";
            break;
        case SectorType::UpperRight:
            os << "UpperRight";
            break;
        case SectorType::LowerRight:
            os << "LowerRight";
            break;
        case SectorType::LowerLeft:
            os << "LowerLeft";
            break;
    }

    return os;
}

FieldSector::FieldSector() : FieldSector(DEFAULT_SECTOR_SIZE, SectorType::UpperLeft) {}

FieldSector::FieldSector(SectorType type) : FieldSector(DEFAULT_SECTOR_SIZE, type) {}

FieldSector::FieldSector(uint64_t s) : FieldSector(s, SectorType::UpperRight) {}

FieldSector::FieldSector(uint64_t s, SectorType type) : _sector_size{s}, _sector_type{type},
                                                        _sector_data{_sector_size} {
    for (uint64_t i = 0; i < _sector_size; i++) {
        _sector_data.at(i).resize(s);
    }
}

void FieldSector::increase(uint64_t size_to_add) {
    _sector_size += size_to_add;
    _sector_data.resize(_sector_size);
    for (uint64_t i = 0; i < _sector_size; i++) {
        _sector_data.at(i).resize(_sector_size);
    }
}

Cell &FieldSector::cell(uint64_t x, uint64_t y) {
    return _sector_data.at(y).at(x);
}

const Cell &FieldSector::cell(uint64_t x, uint64_t y) const {
    return _sector_data.at(y).at(x);
}

void FieldSector::cell(uint64_t x, uint64_t y, const Cell &c) {
    _sector_data.at(y).at(x) = c;
}

void FieldSector::cell(uint64_t x, uint64_t y, GamokuCellValue gcv) {
    _sector_data.at(y).at(x).value(gcv);
}

void FieldSector::restore_defaults() {
    _sector_size = DEFAULT_SECTOR_SIZE;
    _sector_data.clear();
    _sector_data.resize(_sector_size);
    for (uint64_t i = 0; i < _sector_size; i++) {
        _sector_data.at(i).resize(_sector_size);
    }
}

void FieldSector::clear() {
    uint64_t cur_s = _sector_size;
    restore_defaults();
    increase(cur_s - _sector_size);
}

uint64_t FieldSector::sector_size() const {
    return _sector_size;
}

SectorType FieldSector::sector_type() const {
    return _sector_type;
}

ostream &operator<<(ostream &os, const FieldSector &fs) {
    switch (fs._sector_type) {
        case SectorType::UpperLeft:
            for (uint64_t y = fs._sector_size; y > 0; y--) {
                for (uint64_t x = fs._sector_size; x > 0; x--) {
                    os << fs._sector_data.at(y - 1).at(x - 1);
                }
                os << endl;
            }

            break;
        case SectorType::UpperRight:
            for (uint64_t y = fs._sector_size; y > 0; y--) {
                for (uint64_t x = 0; x < fs._sector_size; x++) {
                    os << fs._sector_data.at(y - 1).at(x);
                }
                os << endl;
            }

            break;
        case SectorType::LowerRight:
            for (uint64_t y = 0; y < fs._sector_size; y++) {
                for (uint64_t x = 0; x < fs._sector_size; x++) {
                    os << fs._sector_data.at(y).at(x);
                }
                os << endl;
            }

            break;
        case SectorType::LowerLeft:
            for (uint64_t y = 0; y < fs._sector_size; y++) {
                for (uint64_t x = fs._sector_size; x > 0; x--) {
                    os << fs._sector_data.at(y).at(x - 1);
                }
                os << endl;
            }

            break;
    }

    return os;
}

