#include "scene.hpp"


// Scene

Scene::Scene(sf::RenderWindow &window): window(window), view(window) {
    select.setFillColor(sf::Color::Transparent);
    primary.setFillColor(sf::Color::Red);
    primary.setRadius(10.f);
    secondary.setFillColor(sf::Color::Blue);
    secondary.setRadius(10.f);
}

void Scene::on_translate(const sf::Vector2f &offset) {
    this->view.translate_view(offset);
}


void Scene::on_select_hover(const sf::Vector2f &position, const sf::Vector2f &size) {
    select.setFillColor(sf::Color::Cyan);
    select.setPosition(position);
    select.setSize(size);
}


void Scene::on_select_confirm(const sf::Vector2f & position, const sf::Vector2f &size) {
    select.setFillColor(sf::Color::Transparent);
}


void Scene::on_primary_click(const sf::Vector2f &position) {
    primary.setPosition(position - sf::Vector2f{10.f, 10.f});
}


void Scene::on_secondary_click(const sf::Vector2f &position) {
    secondary.setPosition(position - sf::Vector2f{10.f, 10.f});
}