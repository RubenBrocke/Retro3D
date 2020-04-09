

typedef struct cell
{
    bool visited;
} cell;

class Maze
{
private:
    bool** _maze;
public:
    Maze(int width, int length);
};

Maze::Maze(int width, int length)
{
    //Create maze buffer
    //_maze = new bool [width][length];
}

