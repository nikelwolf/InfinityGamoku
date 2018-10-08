#include <GamokuCommon.h>

GameBoard::GameBoard() : GameBoard{DEFAULT_VIEW_SIZE} {

}

GameBoard::GameBoard(uint64_t field_size) : _gf{field_size}, _inner_view{_gf, field_size},
                                            _outer_view{_gf, field_size * 2}, _outer_offset{field_size / 2} {

    _inner_view.move(field_size / 2, field_size / 2);
}

void GameBoard::move_left() {
    _inner_view.move_left(1);
    _outer_view.move_left(1);
}

void GameBoard::move_right() {
    _inner_view.move_right(1);
    _outer_view.move_right(1);
}

void GameBoard::move_down() {
    _inner_view.move_down(1);
    _outer_view.move_down(1);
}

void GameBoard::move_up() {
    _inner_view.move_up(1);
    _outer_view.move_up(1);
}

void GameBoard::clear_board() {
    _gf.clear();
    _inner_view.update_state();
    _outer_view.update_state();
    _has_winner = false;
}

void GameBoard::set_cell(uint64_t x, uint64_t y, uint64_t value) {
    if (_has_winner)
        return;

    _inner_view.cell(x, y, value);
    _outer_view.cell(x + _outer_offset, y + _outer_offset, value);

    _set_cell_prefab_execute(x + _outer_offset, y + _outer_offset);
}

void GameBoard::set_cell(uint64_t x, uint64_t y, GamokuCellValue gcv) {
    if (_has_winner)
        return;

    _inner_view.cell(x, y, gcv);
    _outer_view.cell(x + _outer_offset, y + _outer_offset, gcv);

    _set_cell_prefab_execute(x + _outer_offset, y + _outer_offset);
}

void GameBoard::set_cell(uint64_t x, uint64_t y, const Cell &c) {
    if (_has_winner)
        return;

    _inner_view.cell(x, y, c);
    _outer_view.cell(x + _outer_offset, y + _outer_offset, c);

    _set_cell_prefab_execute(x + _outer_offset, y + _outer_offset);
}

Cell &GameBoard::get_cell(uint64_t x, uint64_t y) {
    return _inner_view.cell(x, y);
}

const Cell &GameBoard::get_cell(uint64_t x, uint64_t y) const {
    return _inner_view.cell(x, y);
}

bool GameBoard::has_winner() const {
    return _has_winner;
}

GamokuCellValue GameBoard::winner() const {
    return _winner_color;
}

ostream &operator<<(ostream &os, const GameBoard &gb) {
    os << gb._outer_view;
    return os;
}

void GameBoard::_set_cell_prefab_execute(uint64_t x, uint64_t y) {
    _last_setted_cell_index_x = x;
    _last_setted_cell_index_y = y;

    _inner_view.save_state();
    _outer_view.save_state();

    _check_and_fill_winner_info();
}


bool GameBoard::_check_and_fill_winner_info() {
    _check_line(true, false, false);
    _check_line(false, true, false);
    _check_line(true, true, false);
    _check_line(true, true, true);

    return _has_winner;
}

void GameBoard::_check_line(bool x, bool y, bool is_exception_line) {
    if (_has_winner) {
        return;
    }

    GamokuCellValue last_gcv = _outer_view.cell(_last_setted_cell_index_x,
                                                _last_setted_cell_index_y).value();
    _winner_color = last_gcv;

    int64_t x_offset, y_offset, count_of_cells;
    for (x_offset = -4, y_offset = is_exception_line ? 4 : -4, count_of_cells = 0;
         x_offset < 5; x_offset++, is_exception_line ? y_offset-- : y_offset++) {
        if (count_of_cells < 5) {
            GamokuCellValue cur_gcv = _outer_view.cell(
                    x ? _last_setted_cell_index_x + x_offset : _last_setted_cell_index_x,
                    y ? _last_setted_cell_index_y + y_offset : _last_setted_cell_index_y).value();

            if (cur_gcv == last_gcv) {
                count_of_cells++;
            } else {
                if (count_of_cells == 5) {
                    _has_winner = true;
                    return;
                } else {
                    count_of_cells = 0;
                }
            }
        } else {
            _has_winner = true;
            return;
        }
    }

    if (count_of_cells == 5) {
        _has_winner = true;
        return;
    }

    _winner_color = GamokuCellValue::Empty;
}