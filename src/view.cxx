#include "view.hxx"

// Convenient type aliases:
using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

// You can change this or even determine it some other way:
static int const grid_size = 36;

View::View(Model const& model)
        : model_(model),
        // You may want to add sprite initialization here
        square({33, 33}, {0, 100, 0}),
        dark(square.dimensions().height / 2, {0, 0, 0}),
        light(square.dimensions().height / 2, {255, 255, 255}),
        options({33, 33}, {100, 0, 0}),
        moves(10, {0, 0, 50}),
        gray(square.dimensions().height / 2, {128, 128, 128}),
        small_dark(7, {0, 0, 0}),
        small_light(7, {255, 255, 255})
{ }

void View::draw(Sprite_set& set, Position mouse_posn)
{
    Position board_pos = screen_to_board(mouse_posn);

    for (Position pos : model_.all_positions()) {
        const Move* move = model_.find_move(pos);

        set.add_sprite(square, board_to_screen(pos), -1);

        if (model_[pos] == Player::dark) {
            place(set, Player::dark, board_to_screen(pos));
        }

        if (model_[pos] == Player::light) {
            place(set, Player::light, board_to_screen(pos));
        }

        if(move != nullptr) {
            set.add_sprite(moves, board_to_screen(move->first).down_right_by({7, 7}), 1);
        }
    }

    const Move* move = model_.find_move(board_pos);
    if(move != nullptr) {
        for (const Position& x : move->second) {
            set.add_sprite(options, board_to_screen(x), 5);
        }
    }


    if (model_.turn() == Player::dark) {
        set.add_sprite(small_dark,{board_to_screen(board_pos).x + 10, board_to_screen(board_pos).y + 10}, 9);
    }
    else if (model_.turn() == Player::light) {
        set.add_sprite(small_light, {board_to_screen(board_pos).x + 10, board_to_screen(board_pos).y + 10}, 9);
    }
}

View::Position
View::board_to_screen(Model::Position logical) const {
    return {logical.x * grid_size, logical.y * grid_size};
}

Model::Position
View::screen_to_board(View::Position physical) const {
    return {physical.x / grid_size, physical.y / grid_size};
}

void
View::place(Sprite_set& sprites, Player player, Position physical) const {
    if (model_.turn() != Player::neither) {
        if (player == Player::dark) {
            sprites.add_sprite(dark, physical, 10);
        }
        else if (player == Player::light) {
            sprites.add_sprite(light, physical, 10);
        }
    }

    //GAME OVER
    else {
        if (model_.winner() == Player::dark) {
            for (Position pos : model_.all_positions()) {
                if (model_[pos] == Player::light) {
                    sprites.add_sprite(gray, board_to_screen(pos), 11);
                }
                else {
                    sprites.add_sprite(dark, board_to_screen(pos), 11);
                }
            }
        }
        else if (model_.winner() == Player::light) {
            for (Position pos : model_.all_positions()) {
                if (model_[pos] == Player::dark) {
                    sprites.add_sprite(gray, board_to_screen(pos), 11);
                }
                else {
                    sprites.add_sprite(light, board_to_screen(pos), 11);
                }
            }
        }
        else {
            for (Position pos : model_.all_positions()) {
                sprites.add_sprite(gray, board_to_screen(pos), 11);
            }
        }
    }
}


View::Dimensions
View::initial_window_dimensions() const
{
    // You can change this if you want:
    return grid_size * model_.all_positions().dimensions();
}

std::string
View::initial_window_title() const
{
    // You can change this if you want:
    return "Reversi";
}

