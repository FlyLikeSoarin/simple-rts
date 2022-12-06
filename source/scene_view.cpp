#include "scene_view.hpp"



SceneView::SceneView(sf::RenderWindow &window): window(window), view_center(.0f, .0f), view_size(500.0f) {}

void SceneView::draw(sf::Drawable &drawable) {
    this->window.draw(drawable, sf::RenderStates(this->view_transform));
}

sf::Vector2f SceneView::get_view_center() const {
    return this->view_center;
}

void SceneView::set_view_center(const sf::Vector2f &view_center) {
    this->view_center = view_center;
    this->_update_view_transform();
}

void SceneView::translate_view(const sf::Vector2f &offset) {
    this->set_view_center(this->get_view_center() + offset);
}

float SceneView::get_view_size() const {
    return this->view_size;
}

void SceneView::set_view_size(float view_size) {
    this->view_size = view_size;
    this->_update_view_transform();
}

void SceneView::zoom_view(float multiplier) {
    this->set_view_size(this->get_view_size() * multiplier);
}

sf::Vector2f SceneView::get_scene_position(const sf::Vector2f &position) const {
    return this->view_transform.getInverse().transformPoint(position);
}

void SceneView::_update_view_transform() {
    float scale_factor = 500.0f / this->view_size;

    view_transform = (
        sf::Transform()
        .translate(-this->view_center *  scale_factor)
        .scale(scale_factor, scale_factor)
    );
}
