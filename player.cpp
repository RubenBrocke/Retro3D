#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

class Player
{
private:
    float _move_speed = 0.02;
    float _rot_speed = 0.04;
    int _prev_mouse_x;
public:
    float x;
    float y;
    float rot;
    Player(int _x, int _y);
    void Update(float time, sf::RenderWindow* window);
};

Player::Player(int _x, int _y)
{
    x = _x;
    y = _y;
    rot = 0;
    _prev_mouse_x = sf::Mouse::getPosition().x;
}

void Player::Update(float time, sf::RenderWindow* window)
{
    float new_x = x;
    float new_y = y;
    float radians = rot * (M_PI / 180);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        new_x += cos(radians) * _move_speed;
        new_y += sin(radians) * _move_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        new_x += cos(radians - M_PI) * _move_speed;
        new_y += sin(radians - M_PI) * _move_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        new_x += cos(radians - M_PI_2) * _move_speed;
        new_y += sin(radians - M_PI_2) * _move_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        new_x += cos(radians + M_PI_2) * _move_speed;
        new_y += sin(radians + M_PI_2) * _move_speed;
    }
    x = new_x;
    y = new_y;

    int mouse_x = sf::Mouse::getPosition().x;
    if (mouse_x > 1920/2)
    {
        rot += _rot_speed * (mouse_x - 1920 / 2);
    }
    if (mouse_x < 1920/2);
    {
        rot -= _rot_speed * (1920 / 2 - mouse_x);
    }
    sf::Mouse::setPosition(sf::Vector2i(1920/2, 1080/2));
}

