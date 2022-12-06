#include <SFML/Graphics.hpp>


#ifndef SCENE_VIEW
#define SCENE_VIEW

class SceneView {
public:
// Methods
    SceneView(sf::RenderWindow &window);

    void draw(sf::Drawable &drawable);

    sf::Vector2f get_view_center() const;

    void set_view_center(const sf::Vector2f &view_center);

    void translate_view(const sf::Vector2f &offset);

    float get_view_size() const;

    void set_view_size(float view_size);

    void zoom_view(float multiplier);

    sf::Vector2f get_scene_position(const sf::Vector2f &position) const;

// Variables
    sf::RenderWindow &window;

private:
// Methods
    void _update_view_transform();

//Variables
    sf::Vector2f view_center;
    float view_size;
    sf::Transform view_transform;
};

#endif