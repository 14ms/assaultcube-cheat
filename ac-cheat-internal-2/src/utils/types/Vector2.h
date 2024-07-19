#pragma once

template<typename Type>
class Vector2
{
public:
	Vector2(Type x, Type y) : m_X{ x }, m_Y{ y } {}
	Vector2() : m_X{ 0 }, m_Y{ 0 } {}

	Vector2(Vector2&&) = delete;

	Vector2 Add(const Vector2& other) const
	{
		return Vector2(m_X + other.m_X, m_Y + other.m_Y);
	}

	Vector2 Sub(const Vector2& other) const
	{
		return Vector2(m_X - other.m_X, m_Y - other.m_Y);
	}

	Vector2 Mul(const Vector2& other) const
	{
		return Vector2(m_X * other.m_X, m_Y * other.m_Y);
	}

	Vector2 Div(const Vector2& other) const
	{
		return Vector2(m_X / other.m_X, m_Y / other.m_Y);
	}

	Type GetX() const { return m_X; }
	void SetX(Type x) { m_X = x; }

	Type GetY() const { return m_Y; }
	void SetY(Type y) { m_Y = y; }

	Vector2 operator+(const Vector2& other) { return Add(other); }
	Vector2 operator-(const Vector2& other) { return Sub(other); }
	Vector2 operator*(const Vector2& other) { return Mul(other); }
	Vector2 operator/(const Vector2& other) { return Div(other); }

private:
	Type m_X, m_Y;
};