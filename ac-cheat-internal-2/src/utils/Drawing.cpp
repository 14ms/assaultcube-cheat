#include "pch.h"

#include "Drawing.h"

void Drawing::Font::Build(int height)
{
	hdc = wglGetCurrentDC();
	base = glGenLists(96);
	this->height = height;

	HFONT font = CreateFontA(-height, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE,
		ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, FF_DONTCARE | DEFAULT_PITCH, "Lucida Console");
	HFONT oldFont = (HFONT)SelectObject(hdc, font);

	wglUseFontBitmaps(hdc, 32, 96, base);
	SelectObject(hdc, oldFont);
	DeleteObject(font);

	isBuilt = true;
}

void Drawing::Font::Destroy()
{
	glDeleteLists(base, 96);
}

void Drawing::Font::Print(float x, float y, Color color, const char* format, ...)
{
	glColor3ub(color.r, color.g, color.b);
	glRasterPos2f(x, y);

	char text[100];
	va_list args;

	va_start(args, format);
	vsprintf_s(text, 100, format, args);
	va_end(args);

	glPushAttrib(GL_LIST_BIT);
	glListBase(base - 32);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
}

void Drawing::SetupOrtho()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	glGetIntegerv(GL_VIEWPORT, viewport.values);
	glViewport(0, 0, viewport.width, viewport.height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, viewport.width, viewport.height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
}

void Drawing::RestoreGL()
{
	glPopMatrix();
	glPopAttrib();
}

void Drawing::SetBasicBlend()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Drawing::FilledRect(float x, float y, float width, float height, Color color)
{
	glColor4ub(color.r, color.g, color.b, color.a);

	glBegin(GL_QUADS);

	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);

	glEnd();
}

void Drawing::InflatedRect(float x, float y, float width, float height,
	float factor, Color color)
{
	FilledRect(x - factor, y - factor, width + factor * 2, height + factor * 2, color);
}

void Drawing::OutlineRect(float x, float y, float width, float height,
	float lineWidth, Color color)
{
	glColor4ub(color.r, color.g, color.b, color.a);
	glLineWidth(lineWidth);

	glBegin(GL_LINE_STRIP);

	glVertex2f(x - 0.5f, y - 0.5f);
	glVertex2f(x + width + 0.5f, y - 0.5f);
	glVertex2f(x + width + 0.5f, y + height + 0.5f);
	glVertex2f(x - 0.5f, y + height + 0.5f);
	glVertex2f(x - 0.5f, y - 0.5f);

	glEnd();
}