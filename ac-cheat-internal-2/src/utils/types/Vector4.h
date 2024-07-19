template<typename Type>
class Vector4
{
public:
	Vector4(Type x, Type y, Type z, Type w)
		: m_X{ x }, m_Y{ y }, m_Z{ z }, m_W{ w } {}
	Vector4() : m_X{ 0 }, m_Y{ 0 }, m_Z{ 0 }, m_W{ 0 } {}

	Vector4 Add(const Vector4& other) const
	{
		return Vector4(m_X + other.m_X, m_Y + other.m_Y,
			m_Z + other.m_Z, m_W + other.m_W);
	}

	Vector4 Sub(const Vector4& other) const
	{
		return Vector4(m_X - other.m_X, m_Y - other.m_Y,
			m_Z - other.m_Z, m_W - other.m_W);
	}

	Vector4 Mul(const Vector4& other) const
	{
		return Vector4(m_X * other.m_X, m_Y * other.m_Y,
			m_Z * other.m_Z, m_W * other.m_W);
	}

	Vector4 Mul(const Type matrix[16])
	{
		return {
			m_X * matrix[0] + m_Y * matrix[4] + m_Z * matrix[8] + m_W * matrix[12],
			m_X * matrix[1] + m_Y * matrix[5] + m_Z * matrix[9] + m_W * matrix[13],
			m_X * matrix[2] + m_Y * matrix[6] + m_Z * matrix[10] + m_W * matrix[14],
			m_X * matrix[3] + m_Y * matrix[7] + m_Z * matrix[11] + m_W * matrix[15] };
	}

	Vector4 Div(const Vector4& other) const
	{
		return Vector4(m_X / other.m_X, m_Y / other.m_Y,
			m_Z / other.m_Z, m_W / other.m_W);
	}

	Type GetX() { return m_X; } const
	void SetX(Type x) { m_X = x; }

	Type GetY() { return m_Y; } const
	void SetY(Type y) { m_Y = y; }

	Type GetZ() { return m_Z; } const
	void SetZ(Type z) { m_Z = z; }

	Type GetW() { return m_W; } const
	void SetW(Type w) { m_W = w; }

	Vector4 operator+(const Vector4& other) { return Add(other); }
	Vector4 operator-(const Vector4& other) { return Sub(other); }

	Vector4 operator*(const Vector4& other) { return Mul(other); }
	Vector4 operator*(const Type matrix[16]) { return Mul(matrix); }

	Vector4 operator/(const Vector4& other) { return Div(other); }

private:
	Type m_X, m_Y, m_Z, m_W;
};