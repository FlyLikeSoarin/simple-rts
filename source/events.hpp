#include <cmath>
#include <optional>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "scene.hpp"
#include "scene_view.hpp"
#include "settings.hpp"
#include "utils.hpp"


#ifndef ENGINE_EVENTS
#define ENGINE_EVENTS


// Base class

class EventHandlerInterface {
public:
    virtual std::optional<sf::Event> operator() (sf::Event event);

protected:
    virtual std::optional<sf::Event> pass_event_to_next(sf::Event event);
    
    virtual std::optional<sf::Event> stop_event(sf::Event event);
};


// UI event handler

class UIHandler : public EventHandlerInterface {
public:

};


// Scene navigation

class SceneNavigationHandler : public EventHandlerInterface {
public:
    SceneNavigationHandler(Scene &scene, const sf::RenderWindow &window);

    virtual std::optional<sf::Event> operator() (sf::Event event) override;

private:
    enum State {
        TRANSLATING,
        SELECTING,
        PRESSED,
        IDLING
    };

    sf::Vector2f _scene_position(const sf::Vector2f &canvas_point) const;
    sf::Vector2f _scene_scale(const sf::Vector2f &canvas_vector) const;

    State _updated_state_after_threshold();
    void _trigger_click();

    void _on_moved(sf::Event event);
    void _on_pressed(sf::Event event);
    void _on_released(sf::Event event);

    State state = State::IDLING;
    sf::Mouse::Button mouse_button_pressed = settings::mouse_primary;
    sf::Vector2f mouse_travelled = {.0f, 0.f};
    constexpr static float mouse_travel_threshold = 10.0f;

    sf::Vector2f screen_position;
    sf::Vector2f previous_screen_position;

    Scene &scene;
    const sf::RenderWindow &window;
};

#endif