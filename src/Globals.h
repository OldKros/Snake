#pragma once
#include <Windows.h>

extern const short conWidth;
extern const short conHeight;
extern const int updateTime;
extern HANDLE hOut;

enum class eDirection
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};