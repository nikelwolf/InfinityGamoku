#include <GamokuCommon.h>

GamokuField::GamokuField() : GamokuField{DEFAULT_SECTOR_SIZE * 2} {}

GamokuField::GamokuField(uint64_t field_size) {
    uint64_t sector_size = field_size / 2;
    FieldSector ul{sector_size, SectorType::UpperLeft};
    FieldSector ur{sector_size, SectorType::UpperRight};
    FieldSector lr{sector_size, SectorType::LowerRight};
    FieldSector ll{sector_size, SectorType::LowerLeft};

    _sectors.push_back(ul);
    _sectors.push_back(ur);
    _sectors.push_back(lr);
    _sectors.push_back(ll);
}

Cell &GamokuField::cell(uint64_t sector_type, uint64_t x, uint64_t y) {
    _increase_sectors_if_need(x, y);

    switch (sector_type) {
        case 0:
        case 1:
        case 2:
        case 3:
            return _sectors.at(sector_type).cell(x, y);
        default:
            throw runtime_error{"wrong sector"};
    }
}

const Cell &GamokuField::cell(uint64_t sector_type, uint64_t x, uint64_t y) const {
    return const_cast<const GamokuField &>(*this).cell(sector_type, x, y);
}

Cell &GamokuField::cell(SectorType sector_type, uint64_t x, uint64_t y) {
    _increase_sectors_if_need(x, y);

    switch (sector_type) {
        case SectorType::UpperLeft:
            return _sectors.at(0).cell(x, y);
        case SectorType::UpperRight:
            return _sectors.at(1).cell(x, y);
        case SectorType::LowerRight:
            return _sectors.at(2).cell(x, y);
        case SectorType::LowerLeft:
            return _sectors.at(3).cell(x, y);
    }

    throw runtime_error{"unexcpected error"};
}

Cell &GamokuField::cell(SectorType sector_type, uint64_t x, uint64_t y) const {
    return const_cast<const GamokuField &>(*this).cell(sector_type, x, y);
}

uint64_t GamokuField::field_size() const {
    return _sectors.at(0).sector_size() * 2;
}

void GamokuField::restore_defaults() {
    for (auto &s: _sectors) {
        s.restore_defaults();
    }
}

void GamokuField::clear() {
    for (auto &s: _sectors) {
        s.clear();
    }
}

ostream &operator<<(ostream &os, const GamokuField &gf) {
    const FieldSector &ul = gf._sectors.at(0),
            &ur = gf._sectors.at(1),
            &lr = gf._sectors.at(2),
            &ll = gf._sectors.at(3);

    for (uint64_t y = ul.sector_size(); y > 0; y--) {
        for (uint64_t x = ul.sector_size(); x > 0; x--) {
            os << ul.cell(y - 1, x - 1);
        }
        for (uint64_t x = 0; x < ur.sector_size(); x++) {
            os << ur.cell(y - 1, x);
        }
        os << endl;
    }

    for (uint64_t y = 0; y < ll.sector_size(); y++) {
        for (uint64_t x = ll.sector_size(); x > 0; x--) {
            os << ll.cell(y, x - 1);
        }
        for (uint64_t x = 0; x < lr.sector_size(); x++) {
            os << lr.cell(y, x);
        }
        os << endl;
    }

    return os;
}

void GamokuField::_increase_sectors_if_need(uint64_t i, uint64_t j) {
    uint64_t sector_size = _sectors.at(0).sector_size();
    if (i >= sector_size || j >= sector_size) {
        uint64_t max_p = max(i, j);
        for (auto &s: _sectors) {
            uint64_t factor_val =
                    (max_p / SECTOR_MULTIPLY_FACTOR + 1) * SECTOR_MULTIPLY_FACTOR ?: SECTOR_MULTIPLY_FACTOR;
            uint64_t inc_val = max(sector_size, factor_val) - min(sector_size, factor_val);
            s.increase(inc_val);
        }
    }
}
