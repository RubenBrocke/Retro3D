#include <math.h>
#include "world.cpp"

typedef struct raycast_result 
{
    int hit_object;
    float distance;
    float offset;
} raycast_result;

class Raycast
{
private:
    World* _world;
public:
    Raycast(World* w);
    raycast_result Cast(float x, float y, float x_angle, float step_size, float cast_angle);
};

Raycast::Raycast(World* w)
{
    _world = w;
}

raycast_result Raycast::Cast(float x, float y, float x_angle, float step_size, float cast_angle)
{
    float x_delta = cos(x_angle) * step_size;
    float y_delta = sin(x_angle) * step_size;
    float x_distance = 0;
    float y_distance = 0;
    raycast_result result;
    while (true)
    {

        x += x_delta;
        x_distance += x_delta;
        if (_world->Get(x, y) != 0)
        {
            result.offset = fmod(y, 1);
            break;
        }
        y += y_delta;
        y_distance += y_delta;
        if (_world->Get(x, y) != 0)
        {
            result.offset = fmod(x, 1);
            break;
        }
    }
    result.hit_object = _world->Get(x, y);
    result.distance = cos(cast_angle) * sqrt(pow(x_distance, 2) + pow(y_distance, 2));
    //result.distance = sqrt(pow(x_distance, 2) + pow(y_distance, 2));
    return result;
}


