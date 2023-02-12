#include "events.hpp"


// Base class

std::optional<sf::Event> EventHandlerInterface::operator() (sf::Event event) {
    return this->stop_event(event);
}


std::optional<sf::Event> EventHandlerInterface::pass_event_to_next(sf::Event event) {
    return std::optional(event);
}


std::optional<sf::Event> EventHandlerInterface::stop_event(sf::Event event) {
    return std::optional<sf::Event>();
}


// Scene navigation

sf::Vector2f SceneNavigationHandler::_scene_position(const sf::Vector2f &canvas_point) const {
    return this->scene.view.get_scene_position(canvas_point);
}


sf::Vector2f SceneNavigationHandler::_scene_scale(const sf::Vector2f &canvas_vector) const {
    return this->scene.view.get_scene_scale(canvas_vector);
}


SceneNavigationHandler::State SceneNavigationHandler::_updated_state_after_threshold() {
    switch (this->mouse_button_pressed) {
        case settings::mouse_select: { return SceneNavigationHandler::State::SELECTING; }
        case settings::mouse_translate: {
            // start translatign from initial position
            this->previous_screen_position = this->screen_position - this->mouse_travelled;
            return SceneNavigationHandler::State::TRANSLATING; 
        }
        default: { return this->state; }
    }
}


void SceneNavigationHandler::_trigger_click() {
    switch (this->mouse_button_pressed) {
        case settings::mouse_primary: {
            this->scene.on_primary_click(
                this->_scene_position(this->screen_position)
            );
            return;
        }
        case settings::mouse_secondary: {
            this->scene.on_secondary_click(
                this->_scene_position(this->screen_position)
            );
            return;
        }
        default: { return; }
    }
}


void SceneNavigationHandler::_on_moved(sf::Event event) {
    // Update positions
    this->previous_screen_position = this->screen_position;
    this->screen_position = get_canvas_position(
        this->window, sf::Vector2f{float(event.size.width), float(event.size.height)}
    );

    // Increment mouse travel vector
    this->mouse_travelled += (this->screen_position - this->previous_screen_position);
    bool threshold_exceeded = (vector_2f_norm(this->mouse_travelled) > this->mouse_travel_threshold);
    
    if (threshold_exceeded && this->state == SceneNavigationHandler::State::PRESSED) {
        this->state = _updated_state_after_threshold();
    }

    if (this->state == SceneNavigationHandler::State::TRANSLATING) {
        this->scene.on_translate(
            this->_scene_position(this->previous_screen_position)
            - this->_scene_position(this->screen_position)
        );
    } else if (this->state == SceneNavigationHandler::State::SELECTING) {
        this->scene.on_select_hover(
            this->_scene_position(this->screen_position - this->mouse_travelled),
            this->_scene_scale(this->mouse_travelled)
        );
    }
}


void SceneNavigationHandler::_on_pressed(sf::Event event) {
    if (this->state == SceneNavigationHandler::State::IDLING) {
        this->state = SceneNavigationHandler::State::PRESSED;
        this->mouse_button_pressed = event.mouseButton.button;
        this->mouse_travelled = {.0f, .0f};
    }
}


void SceneNavigationHandler::_on_released(sf::Event event) {
    if (this->mouse_button_pressed != event.mouseButton.button) {
        return;
    }

    if (this->state == SceneNavigationHandler::State::PRESSED) {
        this->_trigger_click();
    } else if (this->state == SceneNavigationHandler::State::SELECTING) {
        this->scene.on_select_confirm(
            this->_scene_position(this->screen_position - this->mouse_travelled),
            this->_scene_scale(this->mouse_travelled)
        );
    }

    this->state = SceneNavigationHandler::State::IDLING;
}


SceneNavigationHandler::SceneNavigationHandler(
    Scene &scene, const sf::RenderWindow &window
) : scene(scene), window(window) {}


std::optional<sf::Event> SceneNavigationHandler::operator() (sf::Event event) {
    switch (event.type) {
        case sf::Event::MouseMoved: {
            this->_on_moved(event);
            break;
        }
        case sf::Event::MouseButtonPressed: {
            this->_on_pressed(event);
            break;
        }
        case sf::Event::MouseButtonReleased: {
            this->_on_released(event);
            break;
        }
        default:{ return this->pass_event_to_next(event); }
    }
    
    return this->stop_event(event);
}
