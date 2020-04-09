#include <iostream>
#pragma once

enum Object { AIR, WALL, FLOOR, CEIL };

class World
{
private:
    int* _map;
    int _width;
    int _length;
    int _height;
    void create_walls();
    inline void set(int x, int y, Object value);
public:
    World(int width, int length);
    int Get(float x, float y);
};

World::World(int width, int length)
{
    _map = new int[width * length];
    _width = width;
    _length = length;
    create_walls();
}

int World::Get(float x, float y)
{
    return _map[((int)y * _width) + (int)x];
}

void World::create_walls()
{
    for (int x = 0; x < _width; x++)
    {
        for (int y = 0; y < _length; y++)
        {
            if (y == 0 || x == 0 || y == _length - 1 || x == _width - 1)
            {
                set(x, y, WALL);
            }
            else
            {
                set(x, y, AIR);
            }
        }
    }
    set(2, 2, WALL);
}

inline void World::set(int x, int y, Object value)
{
    _map[(y * _width) + x] = value;
}
