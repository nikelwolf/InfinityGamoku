#pragma once

#include <GamokuCommon.h>

class GameBoard {
public:
    GameBoard();

    explicit GameBoard(uint64_t field_size);

    void move_left();

    void move_right();

    void move_down();

    void move_up();

    void set_cell(uint64_t x, uint64_t y, uint64_t value);

    void set_cell(uint64_t x, uint64_t y, GamokuCellValue gcv);

    void set_cell(uint64_t x, uint64_t y, const Cell &c);

    Cell &get_cell(uint64_t x, uint64_t y);

    const Cell &get_cell(uint64_t x, uint64_t y) const;

    bool has_winner() const;

    GamokuCellValue winner() const;

private:
    GamokuField _gf;
    GameView _inner_view;
    GameView _outer_view;

    uint64_t _outer_offset;

    bool _has_winner = false;
    GamokuCellValue _winner_color{};

    uint64_t _last_setted_cell_index_x{};
    uint64_t _last_setted_cell_index_y{};

    void _set_cell_prefab_execute(uint64_t x, uint64_t y);

    bool _check_and_fill_winner_info();

    void _check_line(bool x, bool y, bool is_exception_line);
};