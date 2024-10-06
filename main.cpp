#include <SFML/Graphics.hpp>
#include <vector>
#include <X11/Xatom.h>
#include <X11/extensions/shape.h>

void setTransparency(Window wnd, unsigned char alpha) {
    Display* display = XOpenDisplay(NULL);
    unsigned long opacity = (0xffffffff/0xff) * alpha;
    Atom property = XInternAtom(display, "_NET_WM_WINDOW_OPACITY", false);
    if (property != None) {
        XChangeProperty(display, wnd, property, XA_CARDINAL, 32, PropModeReplace, (unsigned char*)&opacity, 1);
    }

    XCloseDisplay(display);
}

int main() {
    int currentLine = 0;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    sf::RenderWindow window(desktop, "Janela Preta", sf::Style::Fullscreen);

    const unsigned char opacity = 50;
    setTransparency(window.getSystemHandle(), opacity);
    
    std::vector<sf::Vertex> word;
    std::vector<std::vector<sf::Vertex>> lines;

    lines.push_back(word);

    bool isMousePressed = false;
    
    while (window.isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            window.close(); 
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
            lines.clear();
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                isMousePressed = true;
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                isMousePressed = false;
                currentLine++;
                lines.push_back(word);
            }
        }

        if (isMousePressed) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vertex point(sf::Vector2f(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y - 15)), sf::Color(0, 255, 255, 255));
            lines[currentLine].push_back(point);
        }

        window.clear(sf::Color::Black);

        if (!lines.empty()) {
            for (int i = 0; i < lines.size(); i++) {
                window.draw(&lines[i][0], lines[i].size(), sf::LinesStrip);
            }
        }

        window.display(); 
    }

    return 0;
}
