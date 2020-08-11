#pragma once
#include "SnakeNode.h"
#include "Food.h"

class Snake
{
public:
    std::vector<SnakeNode> snake_body;
    int playerScore;

    Snake();
    ~Snake();
    void DrawSnake();
    void UndrawSnake();
    void MoveDrawSnake();
    void MoveUndrawSnake();
    void AddBodyNode(SnakeNode sn);
    void EatFood(Food& _food);
    void MoveHead();
    void MoveHead(int _x, int _y, eDirection _direction);
    void MoveBody();
    void Move();
    void Move(int _x, int _y, eDirection _direction);
    bool CheckSelfCollision();
};