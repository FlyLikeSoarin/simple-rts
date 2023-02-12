#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


#ifndef ENGINE_SPRITES
#define ENGINE_SPRITES


class AnimatedSprite: public sf::Drawable {
public:
    AnimatedSprite(
        const sf::Texture &texture,
        const std::vector<sf::Vector2i> &section_posittion,
        sf::Vector2i section_size,
        unsigned int current_secrion,
        unsigned int animation_speed = 1
    );

    void set_current_section(unsigned int section);

    unsigned int get_current_section();

    void next();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Sprite sprite;

    sf::Texture texture;
    std::vector<sf::Vector2i> section_positions;
    sf::Vector2i section_size;
    unsigned int current_section;
    unsigned int animation_speed;
    unsigned int animation_progress;
};


#endif