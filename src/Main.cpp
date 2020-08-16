#include "Food.h"
#include "Snake.h"
#include "Globals.h"

#include <iostream>
#include <Windows.h>
#include <time.h>

/* 
*   TODO:
*       ?
*/

const short conWidth = 30;
const short conHeight = 30;
const int updateTime = 100; // in ms
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

Snake* ResetSnake(Snake* snake)
{
    delete snake;
    return new Snake();
}

Food* ResetFood(Food* food)
{
    delete food;
    return new Food();
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
    SMALL_RECT DisplayArea = {0, 0, conWidth, conHeight};
    SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);
    HideCursor();

    int score = 0;
    bool started = false;
    Snake* snake = new Snake();
    Food* food = new Food();

    while (true)
    {
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
            if (snake->snake_body[0].x >= conWidth && snake->snake_body[0].direction == eDirection::RIGHT)
            {
                snake->Move(0, snake->snake_body[0].y, snake->snake_body[0].direction);
                continue;
            }
            else if (snake->snake_body[0].x == 0 && snake->snake_body[0].direction == eDirection::LEFT)
            {
                snake->Move(conWidth, snake->snake_body[0].y, snake->snake_body[0].direction);
                continue;
            }
            else if (snake->snake_body[0].y >= conHeight && snake->snake_body[0].direction == eDirection::UP)
            {
                snake->Move(snake->snake_body[0].x, 0, snake->snake_body[0].direction);
                continue;
            }
            else if (snake->snake_body[0].y == 0 && snake->snake_body[0].direction == eDirection::DOWN)
            {
                snake->Move(snake->snake_body[0].x, conHeight, snake->snake_body[0].direction);
                continue;
            }

            //food->Draw();
            snake->Move();
            
            // Check if we are eating ourselves
            if (snake->CheckSelfCollision())
            {
                score = snake->playerScore;
                snake = ResetSnake(snake);
                food = ResetFood(food);
                started = false;
            }

            // quit the loop and delete snake and food
            if (GetAsyncKeyState(VK_ESCAPE))
            {
                break;
            }
        }
        else
        {
            COORD p;
            // width must be bigger than "Press enter to start..."
            p.X = int(conWidth / 2 - 12);
            p.Y = int(conHeight / 2);
            SetConsoleCursorPosition(hOut, p);

            // Wait for user to press the space bar
            if (score > 0)
                std::cout << "       Your Score: " << score << std::endl;
            else
                std::cout << "Press enter to start...";
            if (std::cin.get())
            {
                SetConsoleCursorPosition(hOut, p);
                std::cout << "                        ";
                started = true;

                food->Spawn();
            }
        }
        Sleep(updateTime);
    }
    delete snake;
    delete food;
}
