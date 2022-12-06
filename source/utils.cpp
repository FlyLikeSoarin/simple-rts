#include "utils.hpp"


// Mathematical functions

float ratio_from_size(sf::Vector2f vector) {
    return vector.x / vector.y;
}


float ratio_from_size(sf::Vector2u vector) {
    return float(vector.x) / float(vector.y);
}


float vector_2f_norm(const sf::Vector2f &vector) {
    return std::sqrtf(vector.x * vector.x + vector.y * vector.y);
}


// Coordinates convertion functions

sf::FloatRect get_canvas(const sf::RenderWindow &window) {
    float window_ratio = ratio_from_size(window.getSize());
    float half_height = 500.0f;
    return sf::FloatRect(
        -half_height * window_ratio,
        -half_height,
        2 * half_height * window_ratio,
        2 * half_height
    );
}


sf::Vector2f get_canvas_position(const sf::RenderWindow &window, sf::Vector2f mouse_position) {
    auto canvas_coordinates = get_canvas(window);
    auto canvas_position = canvas_coordinates.getPosition();
    auto canvas_size = canvas_coordinates.getSize();
    auto window_size = window.getSize();

    return sf::Vector2f{
        (mouse_position.x / window_size.x) * canvas_size.x + canvas_position.x,
        (mouse_position.y / window_size.y) * canvas_size.y + canvas_position.y,
    };
}