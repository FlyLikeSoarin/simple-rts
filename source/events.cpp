#include "events.hpp"


// Base class

std::optional<sf::Event> EventHandler::operator() (sf::Event event) {
    return this->stop_event(event);
}


std::optional<sf::Event> EventHandler::pass_event_to_next(sf::Event event) {
    return std::optional(event);
}


std::optional<sf::Event> EventHandler::stop_event(sf::Event event) {
    return std::optional<sf::Event>();
}


// Scene navigation

SceneNavigationHandler::SceneNavigationHandler(SceneView &scene_view, const sf::RenderWindow &window) : scene_view(scene_view), window(window) {}

std::optional<sf::Event> SceneNavigationHandler::operator() (sf::Event event) {
    switch (event.type) {
        case sf::Event::MouseMoved:
            this->previous_screen_position = this->screen_position;

            this->screen_position = get_canvas_position(
                this->window, sf::Vector2f{float(event.size.width), float(event.size.height)}
            );

            if (this->is_scene_grabbed) {
                this->scene_view.translate_view(
                    this->scene_view.get_scene_position(this->previous_screen_position)
                    - this->scene_view.get_scene_position(this->screen_position)
                );

                this->travelled += (this->previous_screen_position - this->screen_position);
            }
            break;
        
        case sf::Event::MouseButtonPressed:
            this->is_scene_grabbed = true;
            this->travelled = {.0f, 0.f};
            break;
        
        case sf::Event::MouseButtonReleased:
            this->is_scene_grabbed = false;

            if (vector_2f_norm(this->travelled) < this->travel_threshold) {
                // This means that user hasn't actually tryed to navigate scene_view
                // scene_view.translate_view(-this->travelled);
            }
            break;
        
        default:
            return this->pass_event_to_next(event);
    }
    
    return this->stop_event(event);
}