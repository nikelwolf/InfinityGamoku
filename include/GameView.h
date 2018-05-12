#pragma once

#include <GamokuCommon.h>

const uint64_t DEFAULT_VIEW_SIZE = 16;

class GameView {
public:
    explicit GameView(GamokuField &field);

    GameView(GamokuField &field, uint64_t view_size);

    void move_left(uint64_t step);

    void move_right(uint64_t step);

    void move_down(uint64_t step);

    void move_up(uint64_t step);

    void move(int64_t step_x, int64_t step_y);

    Cell &cell(uint64_t x, uint64_t y);

    const Cell &cell(uint64_t x, uint64_t y) const;

    void cell(uint64_t x, uint64_t y, uint64_t value);

    void cell(uint64_t x, uint64_t y, const Cell &c);

    void cell(uint64_t x, uint64_t y, GamokuCellValue gcv);

    void save_state();

    friend ostream &operator<<(ostream &os, const GameView &gv);

    void _debug();

private:
    uint64_t _view_start_x, _view_start_y;
    SectorType _current_start_sector;
    GamokuField &_field;
    FieldSector _field_data;

    void _change_position(uint64_t &changing_arg, uint64_t step, SectorType new_sector);

    void _update_data();

    void _insert_data();
};
