#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


#ifndef ENGINE_UTILS
#define ENGINE_UTILS


// Mathematical funtions

float ratio_from_size(sf::Vector2f vector);

float ratio_from_size(sf::Vector2u vector);

float vector_2f_norm(const sf::Vector2f &vector);

// Coordinates convertion functions

sf::FloatRect get_canvas(const sf::RenderWindow &window);

sf::Vector2f get_canvas_position(const sf::RenderWindow &window, sf::Vector2f mouse_position);


#endif