#pragma once

#include <GamokuCommon.h>

using namespace std;

const uint64_t DEFAULT_SECTOR_SIZE = 5;

enum class SectorType {
    UpperLeft,
    UpperRight,
    LowerRight,
    LowerLeft
};

ostream &operator<<(ostream &os, SectorType s);

class FieldSector {
public:
    FieldSector();

    explicit FieldSector(SectorType type);

    explicit FieldSector(uint64_t s);

    FieldSector(uint64_t s, SectorType type);

    void increase(uint64_t size_to_add);

    Cell &cell(uint64_t x, uint64_t y);

    const Cell &cell(uint64_t x, uint64_t y) const;

    void cell(uint64_t x, uint64_t y, const Cell &c);

    void cell(uint64_t x, uint64_t y, GamokuCellValue gcv);

    void restore_defaults();

    void clear();

    uint64_t sector_size() const;

    SectorType sector_type() const;

    friend ostream &operator<<(ostream &os, const FieldSector &fs);

private:
    uint64_t _sector_size{};
    vector<vector<Cell>> _sector_data;
    SectorType _sector_type;
};

