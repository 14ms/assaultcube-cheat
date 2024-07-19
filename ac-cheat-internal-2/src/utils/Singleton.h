#pragma once

template<typename T>
class Singleton
{
protected:
	Singleton()
	{

	}

public:
	static T& Instance()
	{
		static T INSTANCE;

		return INSTANCE;
	}
};