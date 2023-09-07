#pragma once

#include "model.hxx"

#include <string>

class View
{
public:
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// View rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    /// Constructs a view that knows about the given model.
    explicit View(Model const&);

    // We added an argument here so that the
    // controller can communicate UI state (such as a mouse or
    // cursor position):
    void draw(ge211::Sprite_set& set, Position mouse_posn);

    Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

    // TODO: Add any public member functions you need.
    View::Position board_to_screen(Model::Position logical) const;

    Model::Position screen_to_board(View::Position physical) const;

    void place(ge211::Sprite_set& sprites, Player player, Position physical) const;

private:
    Model const& model_;

    // TODO: Add any additional private members you need, such as helper
    // functions or sprites.
    ge211::Rectangle_sprite const square;
    ge211::Circle_sprite const dark;
    ge211::Circle_sprite const light;
    ge211::Rectangle_sprite const options;
    ge211::Circle_sprite const moves;
    ge211::Circle_sprite const gray;
    ge211::Circle_sprite const small_dark;
    ge211::Circle_sprite const small_light;

};
