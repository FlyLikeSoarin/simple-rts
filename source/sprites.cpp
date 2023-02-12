#include "sprites.hpp"


AnimatedSprite::AnimatedSprite(
    const sf::Texture &texture,
    const std::vector<sf::Vector2i> &section_positions,
    sf::Vector2i section_size,
    unsigned int current_secrion,
    unsigned int animation_speed
): 
    sprite(),
    texture(texture),
    section_positions(section_positions),
    section_size(section_size),
    current_section(current_secrion),
    animation_speed(animation_speed),
    animation_progress(0)
{
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(
        sf::IntRect(this->section_positions[this->current_section], this->section_size)
    );
}

void AnimatedSprite::set_current_section(unsigned int section) {
    this->current_section = section % this->section_positions.size();

    std::cout << this->current_section << std::endl;
    std::cout << this->section_positions.at(this->current_section).x << ' ' << this->section_positions.at(this->current_section).y << std::endl;
    this->sprite.setTextureRect(
        sf::IntRect(this->section_positions.at(this->current_section), this->section_size)
    );
}

unsigned int AnimatedSprite::get_current_section() {
    return this->current_section;
}

void AnimatedSprite::next() {
    this->animation_progress = (this->animation_progress + 1) % this->animation_speed;
    this->set_current_section(
        this->get_current_section() + (this->animation_progress ? 0 : 1)
    );
}

void AnimatedSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->sprite, states);
}