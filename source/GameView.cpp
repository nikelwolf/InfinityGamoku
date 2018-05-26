#include <GamokuCommon.h>

GameView::GameView(GamokuField &field) : GameView{field, DEFAULT_VIEW_SIZE} {

}

GameView::GameView(GamokuField &field, uint64_t view_size) : _field{field}, _field_data{view_size} {
    _current_start_sector = SectorType::UpperRight;
    _view_start_x = _view_start_y = 0;
    for (uint64_t x = 0; x < _field_data.sector_size(); x++) {
        for (uint64_t y = 0; y < _field_data.sector_size(); y++) {
            _field_data.cell(x, y) = _field.cell(SectorType::UpperRight, x, y);
        }
    }
}

void GameView::move_left(uint64_t step) {
    if (step == 0) {
        return;
    }

    _insert_data();

    switch (_current_start_sector) {
        case SectorType::UpperLeft:
            _view_start_x += step;
            break;
        case SectorType::UpperRight:
            _change_position(_view_start_x, step, SectorType::UpperLeft);
            break;
        case SectorType::LowerRight:
            _change_position(_view_start_x, step, SectorType::LowerRight);
            break;
        case SectorType::LowerLeft:
            _view_start_x += step;
            break;
    }

    _update_data();
}

void GameView::move_right(uint64_t step) {
    if (step == 0) {
        return;
    }

    _insert_data();

    switch (_current_start_sector) {
        case SectorType::UpperLeft:
            _change_position(_view_start_x, step, SectorType::UpperRight);
            break;
        case SectorType::UpperRight:
            _view_start_x += step;
            break;
        case SectorType::LowerRight:
            _view_start_x += step;
            break;
        case SectorType::LowerLeft:
            _change_position(_view_start_x, step, SectorType::LowerRight);
            break;
    }

    _update_data();
}

void GameView::move_down(uint64_t step) {
    if (step == 0) {
        return;
    }

    _insert_data();

    switch (_current_start_sector) {
        case SectorType::UpperLeft:
            _change_position(_view_start_y, step, SectorType::LowerLeft);
            break;
        case SectorType::UpperRight:
            _change_position(_view_start_y, step, SectorType::LowerRight);
            break;
        case SectorType::LowerRight:
            _view_start_y += step;
            break;
        case SectorType::LowerLeft:
            _view_start_y += step;
            break;
    }

    _update_data();
}

void GameView::move_up(uint64_t step) {
    if (step == 0) {
        return;
    }

    _insert_data();

    switch (_current_start_sector) {
        case SectorType::UpperLeft:
            _view_start_y += step;
            break;
        case SectorType::UpperRight:
            _view_start_y += step;
            break;
        case SectorType::LowerRight:
            _change_position(_view_start_y, step, SectorType::UpperRight);
            break;
        case SectorType::LowerLeft:
            _change_position(_view_start_y, step, SectorType::UpperLeft);
            break;
    }

    _update_data();
}

void GameView::move(int64_t step_x, int64_t step_y) {
    if (step_x > 0) {
        move_right(static_cast<uint64_t>(step_x));
    } else {
        move_left(static_cast<uint64_t>(-step_x));
    }

    if (step_y > 0) {
        move_up(static_cast<uint64_t>(step_y));
    } else {
        move_down(static_cast<uint64_t>(-step_y));
    }

//    _debug();
}

Cell &GameView::cell(uint64_t x, uint64_t y) {
    return _field_data.cell(x, y);
}

const Cell &GameView::cell(uint64_t x, uint64_t y) const {
    return _field_data.cell(x, y);
}

void GameView::cell(uint64_t x, uint64_t y, uint64_t value) {
    _field_data.cell(x, y).value(value);
}

void GameView::cell(uint64_t x, uint64_t y, const Cell &c) {
    _field_data.cell(x, y, c);
}

void GameView::cell(uint64_t x, uint64_t y, GamokuCellValue gcv) {
    _field_data.cell(x, y, gcv);
}

void GameView::save_state() {
    _insert_data();
}

ostream &operator<<(ostream &os, const GameView &gv) {
    os << gv._field_data;
    return os;
}

void GameView::_debug() {
    cout << _view_start_x << ", " << _view_start_y << endl << _current_start_sector << endl << endl;
}


void GameView::_change_position(uint64_t &changing_arg, uint64_t step, SectorType new_sector) {
    if (changing_arg != 0) {
        if (changing_arg >= step) {
            changing_arg -= step;
        } else {
            changing_arg = step - changing_arg - 1;
            _current_start_sector = new_sector;
        }
    } else {
        changing_arg = step - 1;
        _current_start_sector = new_sector;
    }
}

void GameView::_update_data() {
    switch (_current_start_sector) {
        case SectorType::UpperLeft:
            if (_field_data.sector_size() - 1 <= _view_start_x) {
                for (uint64_t x = _view_start_x, dx = 0; dx < _field_data.sector_size(); x--, dx++) {
                    for (uint64_t y = _view_start_y, dy = 0; dy < _field_data.sector_size(); y++, dy++) {
                        _field_data.cell(dx, dy) = _field.cell(SectorType::UpperLeft, x, y);
                    }
                }
            } else {
                uint64_t dx = 0;
                for (uint64_t x = _view_start_x; x + 1 > 0; x--, dx++) {
                    for (uint64_t y = _view_start_y, dy = 0; dy < _field_data.sector_size(); y++, dy++) {
                        _field_data.cell(dx, dy) = _field.cell(SectorType::UpperLeft, x, y);
                    }
                }

                uint64_t x_left = _field_data.sector_size() - dx;
                for (uint64_t x = 0; x < x_left; x++, dx++) {
                    for (uint64_t y = _view_start_y, dy = 0; dy < _field_data.sector_size(); y++, dy++) {
                        _field_data.cell(dx, dy) = _field.cell(SectorType::UpperRight, x, y);
                    }
                }
            }
            break;
        case SectorType::UpperRight:
            for (uint64_t x = _view_start_x, dx = 0; dx < _field_data.sector_size(); x++, dx++) {
                for (uint64_t y = _view_start_y, dy = 0; dy < _field_data.sector_size(); y++, dy++) {
                    _field_data.cell(dx, dy) = _field.cell(SectorType::UpperRight, x, y);
                }
            }
            break;
        case SectorType::LowerRight:
            if (_field_data.sector_size() - 1 <= _view_start_y) {
                for (uint64_t x = _view_start_x, dx = 0; dx < _field_data.sector_size(); x++, dx++) {
                    for (uint64_t y = _view_start_y, dy = 0; dy < _field_data.sector_size(); y--, dy++) {
                        _field_data.cell(dx, dy) = _field.cell(SectorType::LowerRight, x, y);
                    }
                }
            } else {
                uint64_t dy = 0;
                for (uint64_t y = _view_start_y; y + 1 > 0; y--, dy++) {
                    for (uint64_t x = _view_start_x, dx = 0; dx < _field_data.sector_size(); x++, dx++) {
                        _field_data.cell(dx, dy) = _field.cell(SectorType::LowerRight, x, y);
                    }
                }

                uint64_t y_left = _field_data.sector_size() - dy;
                for (uint64_t y = 0; y < y_left; y++, dy++) {
                    for (uint64_t x = _view_start_x, dx = 0; x < _field_data.sector_size(); x++, dx++) {
                        _field_data.cell(dx, dy) = _field.cell(SectorType::UpperRight, x, y);
                    }
                }
            }
            break;
        case SectorType::LowerLeft:
            if (_field_data.sector_size() - 1 <= _view_start_x && _field_data.sector_size() - 1 <= _view_start_y) {
                for (uint64_t x = _view_start_x, dx = 0; dx < _field_data.sector_size(); x--, dx++) {
                    for (uint64_t y = _view_start_y, dy = 0; dy < _field_data.sector_size(); y--, dy++) {
                        _field_data.cell(dx, dy) = _field.cell(SectorType::LowerLeft, x, y);
                    }
                }
            } else {
                uint64_t cur_x = 0, cur_y = 0;

                for (uint64_t x = _view_start_x, dx = 0; x + 1 > 0; x--, dx++) {
                    for (uint64_t y = _view_start_y, dy = 0; y + 1 > 0; y--, dy++) {
                        cur_x = dx;
                        cur_y = dx;

                        _field_data.cell(dx, dy) = _field.cell(SectorType::LowerLeft, x, y);
                    }
                }

                for (uint64_t x = _view_start_x, dx = 0; x + 1 > 0; x--, dx++) {
                    for (uint64_t y = 0, dy = cur_y + 1; dy < _field_data.sector_size(); y++, dy++) {
                        _field_data.cell(dx, dy) = _field.cell(SectorType::UpperLeft, x, y);
                    }
                }

                for (uint64_t x = 0, dx = cur_x + 1; dx < _field_data.sector_size(); x++, dx++) {
                    for (uint64_t y = _view_start_y, dy = 0; y + 1 > 0; y--, dy++) {
                        _field_data.cell(dx, dy) = _field.cell(SectorType::LowerRight, x, y);
                    }
                }

                for (uint64_t x = 0, dx = cur_x + 1; dx < _field_data.sector_size(); x++, dx++) {
                    for (uint64_t y = 0, dy = cur_y + 1; dy < _field_data.sector_size(); y++, dy++) {
                        _field_data.cell(dx, dy) = _field.cell(SectorType::UpperRight, x, y);
                    }
                }
            }
            break;
    }
}

void GameView::_insert_data() {
    switch (_current_start_sector) {
        case SectorType::UpperLeft:
            if (_field_data.sector_size() - 1 <= _view_start_x) {
                for (uint64_t x = _view_start_x, dx = 0; dx < _field_data.sector_size(); x--, dx++) {
                    for (uint64_t y = _view_start_y, dy = 0; dy < _field_data.sector_size(); y++, dy++) {
                        _field.cell(SectorType::UpperLeft, x, y) = _field_data.cell(dx, dy);
                    }
                }
            } else {
                uint64_t dx = 0;
                for (uint64_t x = _view_start_x; x + 1 > 0; x--, dx++) {
                    for (uint64_t y = _view_start_y, dy = 0; dy < _field_data.sector_size(); y++, dy++) {
                        _field.cell(SectorType::UpperLeft, x, y) = _field_data.cell(dx, dy);
                    }
                }

                uint64_t x_left = _field_data.sector_size() - dx;
                for (uint64_t x = 0; x < x_left; x++, dx++) {
                    for (uint64_t y = _view_start_y, dy = 0; dy < _field_data.sector_size(); y++, dy++) {
                        _field.cell(SectorType::UpperRight, x, y) = _field_data.cell(dx, dy);
                    }
                }
            }
            break;
        case SectorType::UpperRight:
            for (uint64_t x = _view_start_x, dx = 0; dx < _field_data.sector_size(); x++, dx++) {
                for (uint64_t y = _view_start_y, dy = 0; dy < _field_data.sector_size(); y++, dy++) {
                    _field.cell(SectorType::UpperRight, x, y) = _field_data.cell(dx, dy);
                }
            }
            break;
        case SectorType::LowerRight:
            if (_field_data.sector_size() - 1 <= _view_start_y) {
                for (uint64_t x = _view_start_x, dx = 0; dx < _field_data.sector_size(); x++, dx++) {
                    for (uint64_t y = _view_start_y, dy = 0; dy < _field_data.sector_size(); y--, dy++) {
                        _field.cell(SectorType::LowerRight, x, y) = _field_data.cell(dx, dy);
                    }
                }
            } else {
                uint64_t dy = 0;
                for (uint64_t y = _view_start_y; y + 1 > 0; y--, dy++) {
                    for (uint64_t x = _view_start_x, dx = 0; dx < _field_data.sector_size(); x++, dx++) {
                        _field.cell(SectorType::LowerRight, x, y) = _field_data.cell(dx, dy);
                    }
                }

                uint64_t y_left = _field_data.sector_size() - dy;
                for (uint64_t y = 0; y < y_left; y++, dy++) {
                    for (uint64_t x = _view_start_x, dx = 0; x < _field_data.sector_size(); x++, dx++) {
                        _field.cell(SectorType::UpperRight, x, y) = _field_data.cell(dx, dy);
                    }
                }
            }
            break;
        case SectorType::LowerLeft:
            if (_field_data.sector_size() - 1 <= _view_start_x && _field_data.sector_size() - 1 <= _view_start_y) {
                for (uint64_t x = _view_start_x, dx = 0; dx < _field_data.sector_size(); x--, dx++) {
                    for (uint64_t y = _view_start_y, dy = 0; dy < _field_data.sector_size(); y--, dy++) {
                        _field.cell(SectorType::LowerLeft, x, y) = _field_data.cell(dx, dy);
                    }
                }
            } else {
                uint64_t cur_x = 0, cur_y = 0;

                for (uint64_t x = _view_start_x, dx = 0; x + 1 > 0; x--, dx++) {
                    for (uint64_t y = _view_start_y, dy = 0; y + 1 > 0; y--, dy++) {
                        cur_x = dx;
                        cur_y = dy;

                        _field.cell(SectorType::LowerLeft, x, y) = _field_data.cell(dx, dy);
                    }
                }

                for (uint64_t x = _view_start_x, dx = 0; x + 1 > 0; x--, dx++) {
                    for (uint64_t y = 0, dy = cur_y + 1; dy < _field_data.sector_size(); y++, dy++) {
                        _field.cell(SectorType::UpperLeft, x, y) = _field_data.cell(dx, dy);
                    }
                }

                for (uint64_t x = 0, dx = cur_x + 1; dx < _field_data.sector_size(); x++, dx++) {
                    for (uint64_t y = _view_start_y, dy = 0; y + 1 > 0; y--, dy++) {
                        _field.cell(SectorType::LowerRight, x, y) = _field_data.cell(dx, dy);
                    }
                }

                for (uint64_t x = 0, dx = cur_x + 1; dx < _field_data.sector_size(); x++, dx++) {
                    for (uint64_t y = 0, dy = cur_y + 1; dy < _field_data.sector_size(); y++, dy++) {
                        _field.cell(SectorType::UpperRight, x, y) = _field_data.cell(dx, dy);
                    }
                }
            }
            break;
    }
}