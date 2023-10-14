#pragma once
#include <graphics.h>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include "Ball.h"

constexpr auto PI = 3.1415926535f;

constexpr auto RADIUS = 20;
constexpr auto SPEED = 10.f;

void Render(Ball* ball_ins, std::vector<RECT> block_list);
void MoveByTime(Ball* ball_ins, float time = 1.f);