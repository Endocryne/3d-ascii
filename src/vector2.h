#pragma once

struct vector2
{
	float x, y;

	vector2(float value) : x(value), y(value) {}
	vector2(float _x, float _y) : x(_x), y(_y) {}

	vector2 operator+(vector2 const& other) { return vector2(x + other.x, y + other.y); }
	vector2 operator-(vector2 const& other) { return vector2(x - other.x, y - other.y); }
	vector2 operator*(vector2 const& other) { return vector2(x * other.x, y * other.y); }
	vector2 operator/(vector2 const& other) { return vector2(x / other.x, y / other.y); }
};