#include "Snake.h"

#include <vector>

Snake::Snake()
    :playerScore(0)
{ // Create the head of the snake
    AddBodyNode(SnakeNode(conWidth / 2, conHeight / 2, eDirection::RIGHT));
}

Snake::~Snake()
{
    UndrawSnake();
}

void Snake::DrawSnake()
{
    for (auto a : snake_body)
        a.Draw();
}

void Snake::UndrawSnake()
{
    for (auto a : snake_body)
        a.Undraw();
}

// If we are moving we only need to redraw the head
void Snake::MoveDrawSnake()
{
    snake_body.front().Draw();
}

// If we are moving we only need to undraw the back of the snake.
void Snake::MoveUndrawSnake()
{
    snake_body.back().Undraw();
}

void Snake::AddBodyNode(SnakeNode sn)
{
    snake_body.push_back(sn);
}

void Snake::EatFood(Food& _food)
{
    switch (snake_body.back().direction)
    {
    case eDirection::RIGHT:
        AddBodyNode(SnakeNode(snake_body.back().x - 1, snake_body.back().y, eDirection::RIGHT));
        break;

    case eDirection::LEFT:
        AddBodyNode(SnakeNode(snake_body.back().x + 1, snake_body.back().y, eDirection::LEFT));
        break;

    case eDirection::UP:
        AddBodyNode(SnakeNode(snake_body.back().x, snake_body.back().y - 1, eDirection::UP));
        break;

    case eDirection::DOWN:
        AddBodyNode(SnakeNode(snake_body.back().x, snake_body.back().y + 1, eDirection::DOWN));
        break;

    default:
        break;
    }
    // Send a reference to our body back so the food doesnt spawn inside us
    _food.Respawn(snake_body);
    // This is undrawing the point where the head is now leaving a gap in the snake so we need to
    // redraw the snake
    DrawSnake();
    ++playerScore;
}

void Snake::MoveHead()
{
    switch (snake_body[0].direction)
    {
    case eDirection::RIGHT:
        snake_body[0].MoveNode(snake_body[0].x + 1, snake_body[0].y, eDirection::RIGHT);
        break;

    case eDirection::LEFT:
        snake_body[0].MoveNode(snake_body[0].x - 1, snake_body[0].y, eDirection::LEFT);
        break;

    case eDirection::UP:
        snake_body[0].MoveNode(snake_body[0].x, snake_body[0].y + 1, eDirection::UP);
        break;

    case eDirection::DOWN:
        snake_body[0].MoveNode(snake_body[0].x, snake_body[0].y - 1, eDirection::DOWN);
        break;

    default:
        break;
    }
}

void Snake::MoveHead(int _x, int _y, eDirection _direction)
{
    snake_body[0].MoveNode(_x, _y, _direction);
}

void Snake::MoveBody()
{
    for (size_t i = 1, len = snake_body.size(); i < len; ++i)
    {
        snake_body[i].MoveNode(snake_body[i - 1].ox,
            snake_body[i - 1].oy,
            snake_body[i - 1].odirection);
    }
}

void Snake::Move()
{
    MoveHead();
    MoveBody();
    MoveUndrawSnake();
    MoveDrawSnake();
}

// When we want to move the head of the snake to a specific point.
void Snake::Move(int _x, int _y, eDirection _direction)
{
    MoveHead(_x, _y, _direction);
    MoveBody();
    MoveUndrawSnake();
    MoveDrawSnake();
}

bool Snake::CheckSelfCollision()
{
    for (size_t i = 1, len = snake_body.size(); i < len; ++i)
    {
        if (snake_body[0].x == snake_body[i].x && snake_body[0].y == snake_body[i].y)
        {
            return true; // we hit ourselves
        }
    }
    return false;
}
