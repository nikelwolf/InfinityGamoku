#pragma once

#include <iostream>
#include <array>

#include <GamokuCommon.h>

const uint64_t SECTOR_MULTIPLY_FACTOR = 10;

class GamokuField {
public:
    GamokuField();

    explicit GamokuField(uint64_t field_size);

    Cell &cell(uint64_t sector_type, uint64_t x, uint64_t y);

    const Cell &cell(uint64_t sector_type, uint64_t x, uint64_t y) const;

    Cell &cell(SectorType sector_type, uint64_t x, uint64_t y);

    Cell &cell(SectorType sector_type, uint64_t x, uint64_t y) const;

    uint64_t field_size() const;

    void restore_defaults();

    void clear();

    friend ostream &operator<<(ostream &os, const GamokuField &gf);

private:
    vector<FieldSector> _sectors;

    void _increase_sectors_if_need(uint64_t i, uint64_t j);
};
