#include "application.hpp"


void on_resize(sf::RenderWindow &window) {
    window.setView(sf::View(get_canvas(window)));
}


void Application::run() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "My window");
    // Initializing window
    window.setVerticalSyncEnabled(true);
    on_resize(window);

    // Initializing scene
    auto scene = Scene(window);
    scene.view.set_view_size(1000.0f);
    scene.view.set_view_center(sf::Vector2f(100.0f, 100.0f));

    // Navigation handler
    auto navigation_handler = SceneNavigationHandler(scene, window);

    sf::RectangleShape rect(sf::Vector2f{1000.0f, 1000.0f});

    sf::Texture caco_tx;

    caco_tx.loadFromFile("./assets/caco.png");

    std::vector<sf::Vector2i> pos = {
        sf::Vector2i{0, 0}, sf::Vector2i{64, 0}, sf::Vector2i{128, 0}, sf::Vector2i{192, 0}, sf::Vector2i{256, 0}, sf::Vector2i{320, 0}
    };
    AnimatedSprite caco_sprite(caco_tx, pos, sf::Vector2i{64, 64}, 0, 10);
    unsigned long long tick = 0;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            navigation_handler(event);

            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::A) {
                        scene.view.zoom_view(0.8);
                    } else if (event.key.code == sf::Keyboard::S) {
                        scene.view.zoom_view(1.25);
                    }
                    break;

                case sf::Event::Resized: {
                    if (event.size.width >= event.size.height) {
                        window.setSize(sf::Vector2u(event.size.width, event.size.height));
                    } else {
                        window.setSize(sf::Vector2u(event.size.height, event.size.height));
                    }
                    on_resize(window);
                    break;
                }
                    
                
                default:
                    break;
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        rect.setFillColor(sf::Color::White);
        rect.setPosition(sf::Vector2f{-500.0f, -500.0f});
        scene.view.draw(rect);
        scene.view.draw(caco_sprite);
        scene.view.draw(scene.select);
        scene.view.draw(scene.primary);
        scene.view.draw(scene.secondary);
        caco_sprite.next();

        // shape.setPosition(scene.get_scene_position(mouse_position) - sf::Vector2f(50.f, 50.f));
        // scene.draw(shape);

        // end the current frame
        window.display();
    }
}