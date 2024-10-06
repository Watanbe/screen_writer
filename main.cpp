#include <SFML/Graphics.hpp>
#include <vector>

int main() {
    
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    sf::RenderWindow window(desktop, "Janela Preta", sf::Style::Fullscreen);
    
    std::vector<sf::Vertex> lines;

    bool isMousePressed = false;
    
    while (window.isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            window.close(); 
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                isMousePressed = true;
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                isMousePressed = false;
            }
        }

        if (isMousePressed) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vertex point(sf::Vector2f(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)), sf::Color::Cyan);
            lines.push_back(point);
        }

        window.clear(sf::Color::Black);

        if (!lines.empty()) {
            window.draw(&lines[0], lines.size(), sf::LinesStrip);
        }

        window.display(); 
    }

    return 0;
}
