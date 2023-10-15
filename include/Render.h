#pragma once
#include <graphics.h>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <ctime>
#include "Ball.h"

constexpr auto PI = 3.1415926535f;

void Render(Ball* ball_ins, std::vector<RECT> block_list);
void MoveByTime(Ball* ball_ins, float time = 1.f);
bool FrameCollisionCheck(Ball* ball_ins, std::vector<RECT> block_list);