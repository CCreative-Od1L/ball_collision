#include "../include/Physics.h"

constexpr unsigned int X = 0;
constexpr unsigned int Y = 1;

float GetNearestPositionFromTwoEdges(float pos, float left_edge, float right_edge) {
	if (pos >= left_edge && pos <= right_edge) {
		return pos;
	} else {
		return (fabsf(pos - left_edge) < fabsf(pos - right_edge)) ? left_edge : right_edge;
	}
}

bool GetTangentCirclePoint(Vector2f tangency_point,Vector2f prev_point,Vector2f cur_point, float radius,Vector2f *out) {
	// 斜率不存在的情况需要特殊处理
	if (fabsf(prev_point.at(X) - cur_point.at(X)) < 0.0001f) {
		auto value_0 = pow(radius, 2) - pow((tangency_point.at(X) - prev_point.at(X)), 2);
		if (value_0 <= 0.f) {
			return false;
		}
		assert(value_0 > 0.f);
		auto value_1 = sqrtf(static_cast<float>(value_0));
		out->at(X) = tangency_point.at(X);

		auto res_y_0 = tangency_point.at(Y) + value_1, res_y_1 = tangency_point.at(Y) - value_1;
		out->at(Y) = (fabsf(prev_point.at(Y) - res_y_0) < fabsf(prev_point.at(Y) - res_y_1) ? res_y_0 : res_y_1);
	} else {
		auto k_circle_move_line = (prev_point.at(Y) - cur_point.at(Y)) / (prev_point.at(X) - cur_point.at(X));
		auto b_circle_move_line = prev_point.at(Y) - k_circle_move_line * prev_point.at(X);
		
		auto value_a = 1 + pow(k_circle_move_line, 2);
		auto value_b = 2 * ((b_circle_move_line - tangency_point.at(Y) - tangency_point.at(X)) * k_circle_move_line);
		auto value_c = pow(tangency_point.at(X), 2) + pow(b_circle_move_line - tangency_point.at(Y), 2) - pow(radius, 2);
		auto delta = pow(value_b, 2) - 4 * value_a * value_c;
		if (delta < 0.f) {
			return false;
		}
		assert(delta > 0.f);
		auto sqrt_delta = sqrtf(static_cast<float>(delta));
		auto res_x_0 = (-value_b + sqrt_delta) / (2 * value_a), res_x_1 = (-value_b - sqrt_delta) / (2 * value_a);
		out->at(X) = fabsf(static_cast<float>(res_x_0) - prev_point.at(X)) - fabsf(static_cast<float>(res_x_1) - prev_point.at(X) < 0.f) ? res_x_0 : res_x_1;
		out->at(Y) = k_circle_move_line * out->at(X) + b_circle_move_line;	
	}
	return true;
}

float GetLeastDistance_PointToRect(Vector2f ball_pos, RECT rect) {
	auto pos_x = ball_pos.at(0);
	auto pos_y = ball_pos.at(1);

	decltype(pos_x) nearest_x_rect = 0.0, nearest_y_rect = 0.0;
	nearest_x_rect = GetNearestPositionFromTwoEdges(pos_x, (float)rect.left, (float)rect.right);
	nearest_y_rect = GetNearestPositionFromTwoEdges(pos_y, (float)rect.top, (float)rect.bottom);

	return sqrtf(static_cast<float>(pow(nearest_x_rect - pos_x, 2)) + static_cast<float>(pow(nearest_y_rect - pos_y, 2)));
}

bool IsBallCrossingRectangleEdge(float ball_pos, float edge_pos, float ball_radius) {
	return fabsf(ball_pos - edge_pos) < ball_radius;
}

bool CollisionCheck(const RECT rect, Ball* ball_ins) {
	// 简单方法：只使用前后两帧的球位置进行碰撞检测
	// 缺陷： 非连续检测，速度过快会直接穿过
	auto cur_ball_x = ball_ins->GetPosition().at(X);
	auto cur_ball_y = ball_ins->GetPosition().at(Y);
	auto prev_ball_x = (cur_ball_x - ball_ins->GetSpeed().at(X));
	auto prev_ball_y = (cur_ball_y - ball_ins->GetSpeed().at(Y));
	auto ball_radius = ball_ins->GetRadius();
	bool collision_status = false;

	if (GetLeastDistance_PointToRect(ball_ins->GetPosition(), rect) - ball_radius > 0.f) {
		return collision_status;
	}
	// 暂时不考虑顶点碰撞
	
	// 判断实体球创到的边
	bool cross_left_edge = IsBallCrossingRectangleEdge(cur_ball_x, static_cast<float>(rect.left), ball_radius);
	bool cross_right_edge = IsBallCrossingRectangleEdge(cur_ball_x, static_cast<float>(rect.right), ball_radius);
	bool cross_top_edge = IsBallCrossingRectangleEdge(cur_ball_y, static_cast<float>(rect.top), ball_radius);
	bool cross_bottom_edge = IsBallCrossingRectangleEdge(cur_ball_y, static_cast<float>(rect.bottom), ball_radius);

	if (cross_left_edge || cross_right_edge) {
		ball_ins->UpdateSpeed(-ball_ins->GetSpeed().at(X), ball_ins->GetSpeed().at(Y));
		collision_status = true;
	}
	if (cross_bottom_edge || cross_top_edge) {
		ball_ins->UpdateSpeed(ball_ins->GetSpeed().at(X), -ball_ins->GetSpeed().at(Y));
		collision_status = true;
	}

	if (collision_status) {
		ball_ins->Move(prev_ball_x, prev_ball_y);
	}
	return collision_status;
}