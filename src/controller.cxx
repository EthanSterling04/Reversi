#include "controller.hxx"

Controller::Controller(int size)
        : Controller(size, size)
{ }

Controller::Controller(int width, int height)
        : model_(width, height),
          view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& sprites)
{
    // TODO this code should give the most recently updated mouse
    //  position to the draw() function when calling it.
    view_.draw(sprites, mouse_pos);
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

void
Controller::on_mouse_up(ge211::Mouse_button, ge211::Posn<int> mouse)
{
    if (model_.find_move(view_.screen_to_board(mouse)) != nullptr) {
        model_.play_move(view_.screen_to_board(mouse));
    }
}

void
Controller::on_mouse_move(ge211::Posn<int> pos)
{
    mouse_pos = pos;
}

