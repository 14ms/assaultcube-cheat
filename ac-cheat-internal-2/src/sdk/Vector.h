#pragma once

template<typename Type>
class Vector
{
public:
	Type* m_Data;
	size_t m_MaxLength;
	size_t m_CurLength;

	Type* GetElement(size_t index)
	{
		return &m_Data[index];
	}

	void Print()
	{
		std::cout << "Vector<" << m_CurLength << '/' << m_MaxLength << ' ' << &m_Data << ">\n";
	}
};