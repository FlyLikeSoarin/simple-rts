#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


#include "scene_view.hpp"


#ifndef ENGINE_SCENE
#define ENGINE_SCENE


class Object {
    
};


class Scene {
public:
    // Constructor
    Scene(sf::RenderWindow &window);

    // Mouse navigation callbacks
    void on_translate(const sf::Vector2f &offset);
    void on_select_hover(const sf::Vector2f &position, const sf::Vector2f &size);
    void on_select_confirm(const sf::Vector2f & position, const sf::Vector2f &size);
    void on_primary_click(const sf::Vector2f &position);
    void on_secondary_click(const sf::Vector2f &position);
    
    // Public fields
    sf::RectangleShape select;
    sf::CircleShape primary;
    sf::CircleShape secondary;

    sf::RenderWindow &window;
    SceneView view;
private:
};


#endif