#include "model.hxx"

using namespace ge211;

Model::Model(int size)
        : Model(size, size)
{ }

Model::Model(int width, int height)
        : board_({width, height})
{
    // TODO: initialize `next_moves_` to `turn_`'s available moves
    compute_next_moves_();
}

Model::Rectangle
Model::all_positions() const
{
    return board_.all_positions();
}

Player
Model::operator[](Position pos) const
{
    return board_[pos];
}

const Move*
Model::find_move(Position pos) const
{
    auto i = next_moves_.find(pos);

    if (i == next_moves_.end()) {
        // Nothing was found, so return NULL (nullptr in C++)
        return nullptr;
    } else {
        // Dereferences the iterator to get the value then returns a pointer
        // to that value. This is safe as the pointer is to a value living
        // within the `next_moves_` structure.
        return &(*i);
    }
}

void
Model::play_move(Position pos)
{
    if (is_game_over()) {
        throw Client_logic_error("Model::play_move: game over");
    }

    const Move* movep = find_move(pos);
    if (movep == nullptr) { // check if there was no such move
        throw Client_logic_error("Model::play_move: no such move");
    }

    // TODO: actually execute the move, advance the turn, refill
    // `next_moves_`, etc.
    really_play_move_(*movep);
}

//
// BELOW ARE HELPER FUNCTIONS
// Our tests will run on the public functions, not the helper functions
// However, these will be extremely useful in writing the above functions
//

Position_set
Model::find_flips_(Position current, Dimensions dir) const
{
    Position_set p_set = {};

    if (board_[current] != Player::neither) {
        return {};
    }
    else {
        current += dir;
    }

    while (board_.good_position(current) && board_[current] != Player::neither) {
        if (board_[current] == other_player(turn_)) {
            p_set |= {current};
            current += dir;
        } else {
            return p_set;
        }
    }
    return {};
}

Position_set
Model::evaluate_position_(Position pos) const
{
    Position_set p = {};
    if (board_[pos] != Player::neither) {
        return  p;
    }

    for (Dimensions dir : board_.all_directions()) {
        p |= find_flips_(pos, dir);
    }

    if (p.empty()) {
        return  {};
    }
    else {
        p |= {pos};
        return  p;
    }
}

void
Model::compute_next_moves_()
{
    next_moves_.clear();
    for (Position pos : board_.center_positions()) {
        if (board_[pos] == Player::neither) {
            next_moves_[pos] = {pos};
        }
    }

    if(!next_moves_.empty()) {
        return;
    }
        for (Position pos : board_.all_positions()) {
            Position_set ps = evaluate_position_(pos);
            if (!ps.empty()) {
                next_moves_[pos] = ps;
            }
        }


}

bool
Model::advance_turn_()
{
    turn_ = other_player(turn_);
    compute_next_moves_();
    return (!next_moves_.empty());
}

void
Model::set_game_over_()
{
    turn_ = Player::neither;
    size_t dark = board_.count_player(Player::dark);
    size_t light = board_.count_player(Player::light);
    if (dark > light) {
        winner_ = Player::dark;
    }
    else if (light > dark) {
        winner_ = Player::light;
    }
    else {
        winner_ = Player::neither;
    }
}

void
Model::really_play_move_(Move move)
{
    for (Position pos : move.second) {
        board_[pos] = turn_;
    }
    if (!advance_turn_() and !advance_turn_()) {
        set_game_over_();
    }
}
