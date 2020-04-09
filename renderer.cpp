#include "raycast.cpp"
#include "world.cpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "settings.cpp"
#include <stdlib.h>

const int FOV = 90;

sf::Image textures[10];

class Renderer
{
private:
    sf::Uint8* _buffer;
    sf::Texture _tex;
    inline void set_buffer_pixel(int x, int y, int r, int g, int b, int a);
    inline int get_buffer_pixel(int x, int y, int selector);
    void clear_buffer();
    void create_line(int x, float distance, int hitobject, float offset);
public:
    Renderer();
    void Render(sf::RenderWindow *window, World w, float x, float y, float rot_x);
};

Renderer::Renderer()
{
    _buffer = new sf::Uint8[RENDER_WIDTH * RENDER_HEIGHT * 4];
    _tex = sf::Texture();
    _tex.create(RENDER_WIDTH, RENDER_WIDTH);
    textures[1].loadFromFile("assets/wall_bricks_small.png");
}

void Renderer::clear_buffer()
{
    for (int x = 0; x < RENDER_WIDTH * RENDER_HEIGHT * 4; x++)
    {
        _buffer[x] = 0;
    }
    
}

inline void Renderer::set_buffer_pixel(int x, int y, int r, int g, int b, int a)
{
    _buffer[((y * RENDER_WIDTH) + x) * 4] = r;
    _buffer[((y * RENDER_WIDTH) + x) * 4 + 1] = g;
    _buffer[((y * RENDER_WIDTH) + x) * 4 + 2] = b;
    _buffer[((y * RENDER_WIDTH) + x) * 4 + 3] = a;
}

inline int Renderer::get_buffer_pixel(int x, int y, int selector)
{
    return _buffer[((y * RENDER_WIDTH) + x) * 4 + selector];
}

void Renderer::Render(sf::RenderWindow *window, World w, float x, float y, float rot_x)
{
    clear_buffer();
    Raycast raycast(&w);
    for (int x_angle = 0; x_angle < RENDER_WIDTH; x_angle++)
    {
        float x_degrees = (-FOV / 2) + rot_x + (((float)FOV / RENDER_WIDTH) * x_angle);
        float x_radians = x_degrees * (M_PI / 180);
        raycast_result res = raycast.Cast(x, y, x_radians, 0.01, x_radians - (rot_x * (M_PI / 180)));
        create_line(x_angle, res.distance, res.hit_object, res.offset);
    }   
    _tex.update(_buffer);
    window->clear();
    window->draw(sf::Sprite(_tex));
    window->display();
}

void Renderer::create_line(int x, float distance, int hitobject, float offset)
{
    float wall_height = RENDER_HEIGHT / distance;
    float draw_start = std::max(-wall_height / 2 + RENDER_HEIGHT / 2, 0.0f);
    float draw_end = std::min(wall_height / 2 + RENDER_HEIGHT / 2, (float)RENDER_HEIGHT - 1);
    sf::Vector2u tex_size = textures[hitobject].getSize();
    int tex_offset = tex_size.x * offset;

    
    double step = 1.0 * tex_size.y / wall_height;
    double texPos = (draw_start - RENDER_HEIGHT / 2 + wall_height / 2) * step;
    for (int y = draw_start; y < draw_end; y++)
    {
        int texY = (int)texPos & (tex_size.y - 1);
        texPos += step;
        sf::Color pixel = textures[hitobject].getPixel(tex_offset,texY);
        set_buffer_pixel(x, y, pixel.r, pixel.g, pixel.b, pixel.a);
    }
}


