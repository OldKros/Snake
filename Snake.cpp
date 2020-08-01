// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <Windows.h>
#include <vector>
#include <time.h>

// Global's
short width = 30;
short height = 30;
const int updateTime = 150; // updates in ms
HANDLE hOut;

/* TODO:
    Abstraction,
    Track score and print,
    Comments and code clean-up
*/

enum class eDirection
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct SnakeNode
{
    int x, y;
    int ox, oy = ox = 0;
    eDirection direction;
    eDirection odirection;

    SnakeNode()
    {
        x = 0;
        y = 0;
        odirection = direction = eDirection::RIGHT;
    }

    SnakeNode(int _x, int _y, eDirection _direction)
    {
        x = _x;
        y = _y;
        odirection = direction = _direction;
    }

    void ChangeDirection(eDirection _direction)
    {
        direction = _direction;
    }

    void Draw()
    {
        COORD p;
        p.X = x;
        p.Y = y;
        SetConsoleCursorPosition(hOut, p);
        std::cout << "#";
    }

    void Undraw()
    {
        COORD p;
        p.X = ox;
        p.Y = oy;
        SetConsoleCursorPosition(hOut, p);
        std::cout << " ";
    }

    void MoveNode(int _x, int _y, eDirection _direction)
    {
        ox = x;
        oy = y;
        odirection = direction;

        x = _x;
        y = _y;
        direction = _direction;
    }
};

struct Food
{
    int x, y;

    Food()
    {
        x = y = 0;
    }

    void Draw()
    {
        COORD p;
        p.X = x;
        p.Y = y;
        SetConsoleCursorPosition(hOut, p);
        std::cout << "@";
    }

    void Undraw()
    {
        COORD p;
        p.X = x;
        p.Y = y;
        SetConsoleCursorPosition(hOut, p);
        std::cout << " ";
    }

    // Takes a reference to the snake_body vector so we know where not to spawn
    void Respawn(const std::vector<SnakeNode> &_snake_body)
    {
        srand((UINT)time(NULL)); // cast to UINT to make the compiler happy
        bool flag = true;

        int tempX = rand() % width;
        int tempY = rand() % height;

        // Loop through the snakes body to check we are not trying to spawn the food on top of the snake
        while (flag)
        {
            for (auto a : _snake_body)
            {
                // we need to rerandomise and check again if the spawn location is occupied
                if (tempX == a.x && tempY == a.y)
                {
                    tempX = rand() % width;
                    tempY = rand() % height;
                    continue;
                }
            }

            // We checked all the nodes and are not ontop of any
            Undraw();
            x = tempX;
            y = tempY;
            Draw();
            flag = false;
        }
    }
};

struct Snake
{
    std::vector<SnakeNode> snake_body;

    Snake()
    {
        // Create the head of the snake
        AddBodyNode(SnakeNode(width / 2, height / 2, eDirection::RIGHT));
    }

    ~Snake()
    {
        UndrawSnake();
    }

    void DrawSnake()
    {
        for (auto a : snake_body)
            a.Draw();
    }

    void UndrawSnake()
    {
        for (auto a : snake_body)
            a.Undraw();
    }

    // If we are moving still we only need to redraw the head
    void MoveDrawSnake()
    {
        snake_body.front().Draw();
    }

    // If we are moving still we only need to undraw the back of the snake.
    void MoveUndrawSnake()
    {
        snake_body.back().Undraw();
    }

    void AddBodyNode(SnakeNode sn)
    {
        snake_body.push_back(sn);
    }

    void EatFood(Food &_food)
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
    }

    void MoveHead()
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

    void MoveHead(int _x, int _y, eDirection _direction)
    {
        snake_body[0].MoveNode(_x, _y, _direction);
    }

    void MoveBody()
    { // Avoiding compiler warnings size_t compare to int
        for (int i = 1, len = snake_body.size(); i < len; ++i)
        {
            snake_body[i].MoveNode(snake_body[i - 1].ox,
                                   snake_body[i - 1].oy,
                                   snake_body[i - 1].odirection);
        }
    }

    void Move()
    {
        MoveHead();
        MoveBody();
        MoveUndrawSnake();
        MoveDrawSnake();
    }

    // When we want to move the head of the snake to a specific point.
    void Move(int _x, int _y, eDirection _direction)
    {
        MoveHead(_x, _y, _direction);
        MoveBody();
        MoveUndrawSnake();
        MoveDrawSnake();
    }

    bool CheckSelfCollision()
    { // Avoiding compiler warnings size_t compare to int
        for (int i = 1, len = snake_body.size(); i < len; ++i)
        {
            if (snake_body[0].x == snake_body[i].x && snake_body[0].y == snake_body[i].y)
            {
                return true; // we hit ourselves
            }
        }
        // everythings fine :)
        return false;
    }
};

Snake *ResetSnake(Snake *snake)
{
    delete snake;
    snake = new Snake();
    return snake;
}

Food *ResetFood(Food *food)
{
    food->Undraw();
    delete food;
    food = new Food();
    return food;
}

void HideCursor()
{
    CONSOLE_CURSOR_INFO ConCurInf;
    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = false;
    SetConsoleCursorInfo(hOut, &ConCurInf);
}

int main()
{
    // Width cannot be less than 25
    if (width < 25)
        width = 25;

    // Set Output handle
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT DisplayArea = {0, 0, width, height};
    SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);

    // Hide Cursor
    HideCursor();

    bool started = false;
    Snake *snake = new Snake();
    Food *food = new Food();

    while (true)
    {
        //Rehide the cursor cus its annoying if you click in the console
        HideCursor();

        if (started)
        {
            // Check if any directional key is pressed and we are not already goin the opposite way
            // KeyUp is down, KeyDown is up for some reason
            if (GetAsyncKeyState(VK_LEFT) && snake->snake_body[0].direction != eDirection::RIGHT)
            {
                snake->snake_body[0].ChangeDirection(eDirection::LEFT);
            }
            else if (GetAsyncKeyState(VK_RIGHT) && snake->snake_body[0].direction != eDirection::LEFT)
            {
                snake->snake_body[0].ChangeDirection(eDirection::RIGHT);
            }
            else if (GetAsyncKeyState(VK_UP) && snake->snake_body[0].direction != eDirection::UP)
            {
                snake->snake_body[0].ChangeDirection(eDirection::DOWN);
            }
            else if (GetAsyncKeyState(VK_DOWN) && snake->snake_body[0].direction != eDirection::DOWN)
            {
                snake->snake_body[0].ChangeDirection(eDirection::UP);
            }

            // We need to check if the snake is eating the food before checking the boundaries
            // because if the food is at the boundaries we will move the snake before eating.
            // Check if the snake is eating the food
            if (snake->snake_body[0].x == food->x && snake->snake_body[0].y == food->y)
            {
                snake->EatFood(*food);
            }

            // Check if the snake_body[0] is at the boundaries and going through the boundary
            // to make sure we don't move the head twice we move the rest of the body and continue the loop
            if (snake->snake_body[0].x >= width && snake->snake_body[0].direction == eDirection::RIGHT)
            {
                snake->Move(0, snake->snake_body[0].y, snake->snake_body[0].direction);
                continue;
            }
            else if (snake->snake_body[0].x == 0 && snake->snake_body[0].direction == eDirection::LEFT)
            {
                snake->Move(width, snake->snake_body[0].y, snake->snake_body[0].direction);
                continue;
            }
            else if (snake->snake_body[0].y >= height && snake->snake_body[0].direction == eDirection::UP)
            {
                snake->Move(snake->snake_body[0].x, 0, snake->snake_body[0].direction);
                continue;
            }
            else if (snake->snake_body[0].y == 0 && snake->snake_body[0].direction == eDirection::DOWN)
            {
                snake->Move(snake->snake_body[0].x, height, snake->snake_body[0].direction);
                continue;
            }

            // Update the snake
            snake->Move();

            // Check if we are eating ourselves
            if (snake->CheckSelfCollision())
            {
                snake = ResetSnake(snake);
                food = ResetFood(food);
                started = false;
            }

            // Esc closes the program
            // quit the loop and delete snake and food
            if (GetAsyncKeyState(VK_ESCAPE))
            {

                break;
            }
        }
        else
        {
            COORD p;
            p.X = int(width / 2 - 12); // width must be more than the size of the string literal below
            p.Y = int(height / 1.5f);
            SetConsoleCursorPosition(hOut, p);

            // Wait for user to press the space bar
            std::cout << "Press space to start...";
            if (GetAsyncKeyState(VK_SPACE))
            {
                SetConsoleCursorPosition(hOut, p);
                std::cout << "                        ";
                started = true;

                food->Respawn(snake->snake_body);
            }
        }

        Sleep(updateTime);
    }
    delete snake;
    delete food;
}
