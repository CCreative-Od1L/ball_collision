#include "../include/Physics.h"

float GetNearestPositionFromTwoEdges(float pos, float left_edge, float right_edge) {
	if (pos >= left_edge && pos <= right_edge) {
		return pos;
	} else {
		return (fabsf(pos - left_edge) < fabsf(pos - right_edge)) ? left_edge : right_edge;
	}
}

float GetLeastDistance_PointToRect(Vector2f ball_pos, RECT rect) {
	auto pos_x = ball_pos.at(0);
	auto pos_y = ball_pos.at(1);

	decltype(pos_x) nearest_x_rect = 0.0, nearest_y_rect = 0.0;
	nearest_x_rect = GetNearestPositionFromTwoEdges(pos_x, (float)rect.left, (float)rect.right);
	nearest_y_rect = GetNearestPositionFromTwoEdges(pos_y, (float)rect.top, (float)rect.bottom);

	return sqrtf(pow(nearest_x_rect, 2) + pow(nearest_y_rect, 2));
}

bool CollisionCheck(RECT rect, Ball* ball_ins) {

}