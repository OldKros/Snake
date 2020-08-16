#pragma once
#include "Globals.h"
#include "SnakeNode.h"

#include <vector>

class Food;


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
    void AddBodyNode(const SnakeNode& sn);
    void EatFood(Food& food);
    void MoveHead();
    void MoveHead(int x, int y, eDirection direction);
    void MoveBody();
    void Move();
    void Move(int x, int y, eDirection direction);
    bool CheckSelfCollision();
};