#include "../include/Ball.h"
using namespace std;

constexpr size_t X = 0;
constexpr size_t Y = 1;

Ball::Ball(float x, float y, float x_speed, float y_speed, float radius) : 
	pos({x, y}),
	speed({x_speed, y_speed}),
    radius(radius) {}

bool Ball::UpdateSpeed(float x_speed, float y_speed) {
	// not check;
	speed.at(X) = x_speed;
	speed.at(Y) = y_speed;
	return true;
}

Vector2f Ball::GetPosition() const {
	return pos;
}

float Ball::GetRadius() const {
	return radius;
}

Vector2f Ball::GetSpeed() const {
	return speed;
}

void Ball::Move(float time) {
	// default: time = 1.0f
	pos.at(X) += speed.at(X) * time;
	pos.at(Y) += speed.at(Y) * time;
}

void Ball::Move(float x_pos, float y_pos) {
	// not check.
	pos.at(X) = x_pos;
	pos.at(Y) = y_pos;
}