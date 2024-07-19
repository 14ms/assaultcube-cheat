template<typename Type>
class Vector3
{
public:
	Vector3(Type x, Type y, Type z) : m_X{ x }, m_Y{ y }, m_Z{ z } {}
	Vector3() : m_X{ 0 }, m_Y{ 0 }, m_Z{ 0 } {}

	Vector3 Add(const Vector3& other) const
	{
		return Vector3(m_X + other.m_X, m_Y + other.m_Y, m_Z + other.m_Z);
	}

	Vector3 Sub(const Vector3& other) const
	{
		return Vector3(m_X - other.m_X, m_Y - other.m_Y, m_Z - other.m_Z);
	}

	Vector3 Mul(const Vector3& other) const
	{
		return Vector3(m_X * other.m_X, m_Y * other.m_Y, m_Z * other.m_Z);
	}

	Vector3 Div(const Vector3& other) const
	{
		return Vector3(m_X / other.m_X, m_Y / other.m_Y, m_Z / other.m_Z);
	}

	Type GetX() const { return m_X; }
	void SetX(Type x) { m_X = x; }

	Type GetY() const { return m_Y; }
	void SetY(Type y) { m_Y = y; }

	Type GetZ() const { return m_Z; }
	void SetZ(Type z) { m_Z = z; }

	Vector3 operator+(const Vector3& other) const { return Add(other); }
	Vector3 operator-(const Vector3& other) const { return Sub(other); }
	Vector3 operator*(const Vector3& other) const { return Mul(other); }
	Vector3 operator/(const Vector3& other) const { return Div(other); }

	Type Length() const
	{
		return sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z);
	}

	Type Distance(const Vector3& other) const
	{
		return (other - *this).Length();
	}

private:
	Type m_X, m_Z, m_Y;
};