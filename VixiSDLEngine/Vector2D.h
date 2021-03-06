#pragma once
#include <iostream>

class Vector2D
{
public:
	float x;
	float y;

	Vector2D();
	Vector2D(float x, float y);

	Vector2D& Add(const Vector2D& vec);
	Vector2D& Subtract(const Vector2D& vec);
	Vector2D& Divide(const Vector2D& vec);
	Vector2D& Multiply(const Vector2D& vec);

	friend Vector2D& operator+(Vector2D& v1, Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, float f);
	friend Vector2D& operator*(Vector2D& v1, int i);


	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator*=(const float f);
	Vector2D& operator*=(const double f);
	Vector2D& operator*=(const int i);
	Vector2D& operator/=(const Vector2D& vec);
	Vector2D& operator*(const int i);
	void Zero();

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};

