#include <SFML/Window.hpp>
#include <math.h>
#include <iostream>

class Player
{
private:
    float _move_speed = 0.02;
    float _rot_speed = 0.2;
    int _prev_mouse_x;
public:
    float x;
    float y;
    float rot;
    Player(int _x, int _y);
    void Update(float time);
};

Player::Player(int _x, int _y)
{
    x = _x;
    y = _y;
    rot = 0;
    _prev_mouse_x = sf::Mouse::getPosition().x;
}

void Player::Update(float time)
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
    if (mouse_x > _prev_mouse_x)
    {
        rot += _rot_speed * (mouse_x - _prev_mouse_x);
    }
    if (mouse_x < _prev_mouse_x)
    {
        rot -= _rot_speed * (_prev_mouse_x - mouse_x);
    }
    _prev_mouse_x = mouse_x;
}

