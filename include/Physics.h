#pragma once
#include "Ball.h"
#include <cassert>
#include <graphics.h>

bool CollisionCheck(const RECT rect, Ball* ball_ins);
float GetLeastDistance_PointToRect(Vector2f ball_pos, RECT rect);
float GetNearestPositionFromTwoEdges(float pos, float left_edge, float right_edge);
bool GetTangentCirclePoint(Vector2f tangency_point, Vector2f prev_point, Vector2f cur_point, float radius, Vector2f* out);