#pragma once
#include "Ball.h"
#include <graphics.h>

bool CollisionCheck(RECT rect, Ball* ball_ins);
float GetLeastDistance_PointToRect(Vector2f ball_pos, RECT rect);
float GetNearestPositionFromTwoEdges(float pos, float left_edge, float right_edge);