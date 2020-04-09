#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "renderer.cpp"
#include "settings.cpp"
#include "player.cpp"

int main(int argc, char *argv[])
{
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(RENDER_WIDTH, RENDER_HEIGHT), "test window");
    window->setSize(sf::Vector2u(1920, 1080));
    Renderer renderer = Renderer();
    World w = World(20, 20);
    Player p = Player(10, 10);
    sf::Clock clock = sf::Clock();

    while (window->isOpen())
    {

        sf::Event event;
        while(window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window->close(); }
        p.Update(0, window);
        renderer.Render(window, w, p.x, p.y, p.rot);
        clock.restart();
    }
    return 0;
}

