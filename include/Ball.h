#pragma once
#include <array>

#define Vector2f std::array<float, 2>

class Ball {
public:
	Ball() = default;
	~Ball() = default;
	Ball(float x = 0.f, float y = 0.f, float x_speed = 0.f, float y_speed = 0.f);
	
	bool UpdateSpeed(float x_speed, float y_speed);
	void Move(float time = 1.f);
	void Move(float x_pos, float y_pos);

	Vector2f GetSpeed() const;
	Vector2f GetPosition() const;

private:
	Vector2f pos;
	Vector2f speed;
};