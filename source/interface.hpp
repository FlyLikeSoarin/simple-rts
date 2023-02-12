#include <unordered_map>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


#ifndef ENGINE_INTERFACE
#define ENGINE_INTERFACE


enum UIElementLocation {
    GLOBAL,
    MIDDLE,
    BOTTOM,
    TOP,
    LEFT,
    RIGHT,
};


class UIElementInterface {
public:
    UIElementInterface(
        UIElementLocation location = UIElementLocation::GLOBAL,
        sf::Vector2i position = {0, 0},
        sf::Vector2i size = {0, 0}
    );    

protected:
    UIElementLocation location;
    sf::Vector2i position;
    sf::Vector2i size;
};


class Button {

};


class UIConfiguration {
    
};


#endif