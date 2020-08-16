#include "Food.h"
#include "SnakeNode.h"

#include <Windows.h>
#include <iostream>
#include <time.h>

Food::Food()
    : x(0), y(0)
{
}

Food::~Food()
{
    Undraw();
}

void Food::Draw()
{
    COORD p;
    p.X = x;
    p.Y = y;
    SetConsoleCursorPosition(hOut, p);
    std::cout << '@';
}

void Food::Undraw()
{
    COORD p;
    p.X = x;
    p.Y = y;
    SetConsoleCursorPosition(hOut, p);
    std::cout << ' ';
}

void Food::Spawn()
{
    srand((UINT)time(NULL)); // cast to UINT to make the compiler happy
    x = rand() % conWidth;
    y = rand() % conHeight;
    Draw();
}

// Takes a reference to the snake_body vector so we know where not to spawn
void Food::Respawn(const std::vector<SnakeNode> &snake_body)
{
    srand((UINT)time(NULL)); // cast to UINT to make the compiler happy
    bool goodToGo = false;
    int tempX;
    int tempY;

    // Loop through the snakes body to check we are not trying to spawn the food on top of the snake
    while (!goodToGo)
    {
        tempX = rand() % conWidth;
        tempY = rand() % conHeight;
        goodToGo = true;
        for (const auto &a : snake_body)
        {
            // if we are trying to spawn ontop of the snake
            // we need to restart and check again
            if (tempX == a.x && tempY == a.y)
            {
                goodToGo = false;
                break;
            }
        }
    }
    Undraw();
    x = tempX;
    y = tempY;
    Draw();
}
