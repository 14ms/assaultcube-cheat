#pragma once

namespace Drawing
{
	union Viewport
	{
		struct
		{ GLint x, y, width, height; };

		GLint values[4];
	};

	union Color
	{
		struct
		{ GLubyte r, g, b, a; };

		Color(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
			: r{ r }, g{ g }, b{ b }, a{ a }
		{
		}

		Color(GLubyte r, GLubyte g, GLubyte b)
			: r{ r }, g{ g }, b{ b }, a{ 255 }
		{
		}

		GLubyte values[3];
	};

	class Font
	{
	public:
		bool isBuilt = false;
		unsigned int base = 0;
		HDC hdc = nullptr;

		int height = 0;
		int width = 0;

		void Build(int height);
		void Destroy();
		void Print(float x, float y, Color color, const char* format, ...);
	};

	inline Viewport viewport{};

	namespace Colors
	{
		inline Color RED = { 255, 0, 0 };
		inline Color GREEN = { 0, 255, 0 };
		inline Color BLUE = { 0, 0, 255 };
		inline Color BLACK = { 0, 0, 0 };
		inline Color WHITE = { 255, 255, 255 };
		inline Color GRAY = { 127, 127, 127 };
		inline Color LIGHT_BLUE = { 97, 94, 252 };
	}

	void SetupOrtho();
	void RestoreGL();

	void SetBasicBlend();
	
	void FilledRect(float x, float y, float width, float height,
		Color color);

	void InflatedRect(float x, float y, float width, float height,
		float factor, Color color);

	void OutlineRect(float x, float y, float width, float height,
		float lineWidth, Color color);
}