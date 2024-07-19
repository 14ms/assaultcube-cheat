#include "pch.h"

#include "ESP.h"

#include "src/utils/types/Types.h"
#include "src/utils/Drawing.h"

constexpr int VIRTUAL_SCREEN_WIDTH = 800;
constexpr int GAME_UNIT_MAGIC = 400;

constexpr float PLAYER_HEIGHT = 5.25f;
constexpr float PLAYER_WIDTH = 2.0f;
constexpr float PLAYER_EYE_HEIGHT = 4.5f;

constexpr float PLAYER_ASPECT_RATIO = PLAYER_HEIGHT / PLAYER_WIDTH;

using namespace Types;

Drawing::Font font;

static void BuildFont()
{
	HDC curHDC = wglGetCurrentDC();

	if (!font.isBuilt || curHDC != font.hdc)
	{
		font.Build(9);
	}
}

static bool WorldToScreen(
	const vec3f& gamePos, vec2f& screenPos, float matrix[16], int windowWidth, int windowHeigth)
{
	vec4f clipCoords = vec4f(gamePos.GetX(), gamePos.GetZ(), gamePos.GetY(), 1.0f) * matrix;

	if (clipCoords.GetW() < 0.1f)
	{
		return false;
	}

	vec3f ndc = {
		clipCoords.GetX() / clipCoords.GetW(),
		clipCoords.GetY() / clipCoords.GetW(),
		clipCoords.GetZ() / clipCoords.GetW()
	};

	screenPos.SetX((windowWidth / 2.0f * ndc.GetX()) + (ndc.GetX() + windowWidth / 2.0f));
	screenPos.SetY(-(windowHeigth / 2.0f * ndc.GetY()) + (ndc.GetY() + windowHeigth / 2.0f));

	return true;
}

static bool GetPlayerScreenPosAndSize(Player& plr, vec2f& outPosition, vec2f& outSize)
{
	vec3f lpOriginPos = (*Cheat::game.m_LocalPlayer)->m_PositionOrigin;
	vec3f plrHeadPos = plr.m_HeadPosition;
	vec3f plrOriginPos = plr.m_PositionOrigin;

	plrHeadPos.SetY(plrHeadPos.GetY() - PLAYER_EYE_HEIGHT + PLAYER_HEIGHT / 2);

	vec2f screenPos;

	if (!WorldToScreen(plrHeadPos, screenPos, Cheat::game.m_ModelMatrix,
		Drawing::viewport.width, Drawing::viewport.height))
	{
		return false;
	}

	float dist = lpOriginPos.Distance(plrOriginPos);
	float scale = (GAME_UNIT_MAGIC / dist) * ((float)Drawing::viewport.width / VIRTUAL_SCREEN_WIDTH)
		* Cheat::game.m_ProjMatrix[0];

	outPosition.SetX(screenPos.GetX() - scale);
	outPosition.SetY(screenPos.GetY() - scale * PLAYER_ASPECT_RATIO);

	outSize.SetX(scale * 2);
	outSize.SetY(scale * PLAYER_ASPECT_RATIO * 2);

	return true;
}

ESP::ESP() : Module("ESP")
{
	m_IsEnabledByDefault = true;
}

static Drawing::Color bgColor(0, 0, 0, 100);

static void DrawBox(const Player& lp, const Player& plr, const vec2f& pos, const vec2f& size,
	const Drawing::Color& color)
{
	Drawing::OutlineRect(pos.GetX(), pos.GetY(), size.GetX(), size.GetY(), 3.0f, bgColor);
	Drawing::OutlineRect(pos.GetX(), pos.GetY(), size.GetX(), size.GetY(), 1.0f, color);
}

static void DrawHealthBar(const Player& plr, const vec2f& pos, const vec2f& size)
{
	float hpBarHeight = (float)plr.m_Health / Player::MAX_HEALTH * size.GetY();
	int hpPercent = (int)((float)plr.m_Health / Player::MAX_HEALTH * 100);

	Drawing::OutlineRect(pos.GetX() + size.GetX() + 5, pos.GetY(), 0, size.GetY(),
		3.0f, bgColor);
	Drawing::OutlineRect(pos.GetX() + size.GetX() + 5, pos.GetY() + size.GetY() - hpBarHeight,
		0, hpBarHeight, 1.0f, Drawing::Colors::GREEN);

	font.Print(pos.GetX() + size.GetX() + 5 + 5, pos.GetY() + size.GetY() - hpBarHeight,
		Drawing::Colors::WHITE, "%d%%", hpPercent);
}

static void DrawArmorBar(const Player& plr, const vec2f& pos, const vec2f& size)
{
	float amorBarWidth = (float)plr.m_Armor / Player::MAX_ARMOR * size.GetX();
	int armorPercent = (int)((float)plr.m_Armor / Player::MAX_ARMOR * 100);

	Drawing::OutlineRect(pos.GetX(), pos.GetY() + size.GetY() + 5, size.GetX(),
		0, 3.0f, bgColor);
	Drawing::OutlineRect(pos.GetX(), pos.GetY() + size.GetY() + 5, amorBarWidth,
		0, 1.0f, Drawing::Colors::LIGHT_BLUE);

	font.Print(pos.GetX(), pos.GetY() + size.GetY() + font.height + 5,
		Drawing::Colors::WHITE, "%d%%", armorPercent);
}

static void DrawTracer(const vec2f& pos, const vec2f& size, const Drawing::Color& color)
{
	glColor4ub(color.r, color.g, color.b, color.a);
	glLineWidth(1.0f);

	glBegin(GL_LINES);

	glVertex2f(Drawing::viewport.width / 2.0f, (GLfloat)Drawing::viewport.height);
	glVertex2f(pos.GetX() + size.GetX() / 2.0f, pos.GetY() + size.GetY());

	glEnd();
}

static void DrawPlayer(const Player& lp, const Player& plr, const vec2f& pos, const vec2f& size)
{
	Drawing::Color color = lp.IsTeamate(plr) ? Drawing::Colors::GREEN : Drawing::Colors::RED;

	if (!lp.IsTeamate(plr))
	{
		DrawTracer(pos, size, color);
	}

	DrawBox(lp, plr, pos, size, color);
	DrawHealthBar(plr, pos, size);

	if (plr.m_Armor > 0)
	{
		DrawArmorBar(plr, pos, size);
	}

	font.Print(pos.GetX(), pos.GetY() - 5, Drawing::Colors::WHITE, "%s", plr.m_Username);
}

void ESP::OnUpdate()
{
	BuildFont();
	Drawing::SetBasicBlend();

	Player* lpPtr = *Cheat::game.m_LocalPlayer;

	if (!lpPtr)
	{
		return;
	}

	Player& lp = *lpPtr;

	Cheat::game.m_OtherPlayers->ForEach([&](Player& otherPlr) {
		if (!otherPlr.IsAlive())
		{
			return;
		}

		vec2f size, pos;
		if (!GetPlayerScreenPosAndSize(otherPlr, pos, size))
		{
			return;
		}

		Drawing::Color color = lp.IsTeamate(otherPlr) ? Drawing::Colors::GREEN : Drawing::Colors::RED;
		DrawPlayer(lp, otherPlr, pos, size);
	});
}

void ESP::OnDisable()
{
	font.Destroy();
}