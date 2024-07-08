#pragma once

#include <cmath>
#include <numbers>

struct vec4
{
	float w, x, y, z;
};

struct vec3
{
	vec3(
		const float x = 0.f,
		const float y = 0.f,
		const float z = 0.f) noexcept :
		x(x), y(y), z(z) {};


	const vec3 operator-(const vec3& v) const noexcept
	{
		return vec3{ x - v.x, y - v.y, z - v.z };
	}
	const vec3 operator+(const vec3& v) const noexcept
	{
		return vec3{ x + v.x, y + v.y, z + v.z };
	}
	const vec3 operator/(const float v) const noexcept
	{
		return vec3{ x / v, y / v, z / v };
	}

	const vec3 operator*(const float v) const noexcept
	{
		return vec3{ x * v, y * v, z * v };
	}


	const bool isZero() const noexcept
	{
		return x == 0.f && y == 0.f && z == 0.f;
	}

	float x, y, z;
};

struct vec2
{
	float x, y;
};
