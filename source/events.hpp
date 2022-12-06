#include <cmath>
#include <optional>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "scene_view.hpp"
#include "utils.hpp"


#ifndef ENGINE_EVENTS
#define ENGINE_EVENTS


// Base class

class EventHandler {
public:
    virtual std::optional<sf::Event> operator() (sf::Event event);

protected:
    virtual std::optional<sf::Event> pass_event_to_next(sf::Event event);
    
    virtual std::optional<sf::Event> stop_event(sf::Event event);
};


// Scene navigation

class SceneNavigationHandler : public EventHandler {
public:
    SceneNavigationHandler(SceneView &scene_view, const sf::RenderWindow &window);

    virtual std::optional<sf::Event> operator() (sf::Event event) override;

private:
    bool is_scene_grabbed = false;
    sf::Vector2f travelled = {.0f, 0.f};
    constexpr static float travel_threshold = 10.0f;

    sf::Vector2f screen_position;
    sf::Vector2f previous_screen_position;

    SceneView &scene_view;
    const sf::RenderWindow &window;
};

#endif