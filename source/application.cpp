#include "application.hpp"


void on_resize(sf::RenderWindow &window) {
    window.setView(sf::View(get_canvas(window)));
}


void Application::run() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "My window");
    window.setVerticalSyncEnabled(true);
    on_resize(window);

    auto scene = SceneView(window);
    scene.set_view_size(1000.0f);
    scene.set_view_center(sf::Vector2f(.0f, 500.0f));

    auto navigation_handler = SceneNavigationHandler(scene, window);

    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color(100, 250, 50));

    sf::RectangleShape rect(sf::Vector2f{1000.0f, 500.0f});

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
                        scene.zoom_view(0.8);
                    } else if (event.key.code == sf::Keyboard::S) {
                        scene.zoom_view(1.25);
                    }
                    break;

                case sf::Event::Resized:
                    std::cout << event.size.width << ' ' << event.size.height << std::endl;
                    if (event.size.width >= event.size.height) {
                        window.setSize(sf::Vector2u(event.size.width, event.size.height));
                    } else {
                        window.setSize(sf::Vector2u(event.size.height, event.size.height));
                    }

                    on_resize(window);
                    
                    break;
                
                default:
                    break;
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        rect.setFillColor(sf::Color::Red);
        rect.setPosition(sf::Vector2f{-500.0f, -500.0f});
        scene.draw(rect);

        rect.setFillColor(sf::Color::Blue);
        rect.setPosition(sf::Vector2f{-500.0f, .0f});
        scene.draw(rect);

        // shape.setPosition(scene.get_scene_position(mouse_position) - sf::Vector2f(50.f, 50.f));
        // scene.draw(shape);

        // end the current frame
        window.display();
    }
}