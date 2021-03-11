/**
 * @file	AMG_Summer_Co_Production_2020\script\Utility.cpp.
 *
 * @brief	Utility
 */

#include"Utility.h"
#include"DxLib.h"
using illumism::ResourceServer;

namespace utility
{
	int* GetColorHSV(float H, float S, float V)
	{
		int hi;
		float f, p, q, t;
		float r, g, b;
		int color[3] = { 0 };

		hi = (int)(H / 60.0f);
		hi = hi == 6 ? 5 : hi %= 6;
		f = H / 60.0f - (float)hi;
		p = V * (1.0f - S);
		q = V * (1.0f - f * S);
		t = V * (1.0f - (1.0f - f) * S);
		switch (hi)
		{
		case 0: r = V; g = t; b = p; break;
		case 1: r = q; g = V; b = p; break;
		case 2: r = p; g = V; b = t; break;
		case 3: r = p; g = q; b = V; break;
		case 4: r = t; g = p; b = V; break;
		case 5: r = V; g = p; b = q; break;
		}

		color[0] = (int)(r * 255.0f);
		if (color[0] > 255) color[0] = 255;
		else if (color[0] < 0) color[0] = 0;

		color[1] = (int)(g * 255.0f);
		if (color[1] > 255) color[1] = 255;
		else if (color[1] < 0) color[1] = 0;

		color[2] = (int)(b * 255.0f);
		if (color[2] > 255) color[2] = 255;
		else if (color[2] < 0) color[2] = 0;

		return color;
	}

	void LoadGraphHandle()
	{
		ResourceServer::RegisterDivGraph("resource/player/nari_wait1.png", 30, 30, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_dash1.png", 20, 20, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_jump1.png", 27, 27, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_attack1.png", 27, 27, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_touch1.png", 15, 15, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_shoot_horizontally1.png", 5, 5, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_shoot_upward1.png", 5, 5, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_shoot_diagonallyupward1.png", 5, 5, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_shoot_diagonallydownward1.png", 5, 5, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_dashshoot_horizontally1.png", 20, 20, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_dashshoot_upward1.png", 20, 20, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_dashshoot_diagonallyupward1.png", 20, 20, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_dashshoot_diagonallydownward1.png", 20, 20, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_appeal1.png", 40, 40, 1, 500, 500);
		ResourceServer::RegisterGraph("resource/player/nari_attack1.png");
		ResourceServer::RegisterDivGraph("resource/player/nari_damage1.png", 15, 15, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_die1.png", 45, 45, 1, 500, 500);
		ResourceServer::RegisterGraph("resource/player/trans.png");

		ResourceServer::RegisterDivGraph("resource/player/nari_wait2.png", 30, 30, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_dash2.png", 20, 20, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_jump2.png", 27, 27, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_attack2.png", 27, 27, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_touch2.png", 15, 15, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_shoot_horizontally2.png", 5, 5, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_shoot_upward2.png", 5, 5, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_shoot_diagonallyupward2.png", 5, 5, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_shoot_diagonallydownward2.png", 5, 5, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_dashshoot_horizontally2.png", 20, 20, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_dashshoot_upward2.png", 20, 20, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_dashshoot_diagonallyupward2.png", 20, 20, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_dashshoot_diagonallydownward2.png", 20, 20, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_appeal2.png", 40, 40, 1, 500, 500);
		ResourceServer::RegisterGraph("resource/player/nari_attack2.png");
		ResourceServer::RegisterDivGraph("resource/player/nari_damage2.png", 15, 15, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/nari_die2.png", 45, 45, 1, 500, 500);
		ResourceServer::RegisterGraph("resource/player/trans.png");

		ResourceServer::RegisterDivGraph("resource/player/noname_wait1.png", 30, 30, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_dash1.png", 20, 20, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_jump1.png", 27, 27, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_attack1.png", 27, 27, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_touch1.png", 15, 15, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_shoot_horizontally1.png", 5, 5, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_shoot_upward1.png", 5, 5, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_shoot_diagonallyupward1.png", 5, 5, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_shoot_diagonallydownward1.png", 5, 5, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_dashshoot_horizontally1.png", 20, 20, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_dashshoot_upward1.png", 20, 20, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_dashshoot_diagonallyupward1.png", 20, 20, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_dashshoot_diagonallydownward1.png", 20, 20, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_appeal1.png", 40, 40, 1, 500, 500);
		ResourceServer::RegisterGraph("resource/player/noname_attack1.png");
		ResourceServer::RegisterDivGraph("resource/player/noname_damage1.png", 15, 15, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_die1.png", 45, 45, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_touch_effecthand.png", 7, 7, 1, 700, 700);
		ResourceServer::RegisterGraph("resource/player/trans.png");

		ResourceServer::RegisterDivGraph("resource/player/noname_wait2.png", 30, 30, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_dash2.png", 20, 20, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_jump2.png", 27, 27, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_attack2.png", 27, 27, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_touch2.png", 15, 15, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_shoot_horizontally2.png", 5, 5, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_shoot_upward2.png", 5, 5, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_shoot_diagonallyupward2.png", 5, 5, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_shoot_diagonallydownward2.png", 5, 5, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_dashshoot_horizontally2.png", 20, 20, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_dashshoot_upward2.png", 20, 20, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_dashshoot_diagonallyupward2.png", 20, 20, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_dashshoot_diagonallydownward2.png", 20, 20, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_appeal2.png", 40, 40, 1, 500, 500);
		ResourceServer::RegisterGraph("resource/player/noname_attack2.png");
		ResourceServer::RegisterDivGraph("resource/player/noname_damage2.png", 15, 15, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_die2.png", 45, 45, 1, 500, 500);
		ResourceServer::RegisterDivGraph("resource/player/noname_touch_effecthand.png", 7, 7, 1, 700, 700);
		ResourceServer::RegisterGraph("resource/player/trans.png");

		ResourceServer::RegisterGraph("resource/boss/pyram_up.png");
		ResourceServer::RegisterGraph("resource/boss/pyram_down.png");
		ResourceServer::RegisterGraph("resource/boss/gear.png");
		ResourceServer::RegisterGraph("resource/boss/scrap.png");
		ResourceServer::RegisterDivGraph("resource/boss/facialexpression_sheet.png", 9, 9, 1, 220, 220);
		ResourceServer::RegisterDivGraph("resource/boss/boss_fallattack.png", 13, 13, 1, 1499, 1060);
		ResourceServer::RegisterDivGraph("resource/boss/boss_groundattack.png", 11, 11, 1, 1499, 1060);


		ResourceServer::RegisterGraph("resource/boss/dpyram_up.png");
		ResourceServer::RegisterGraph("resource/boss/dpyram_down.png");
		ResourceServer::RegisterGraph("resource/boss/dgear.png");
		ResourceServer::RegisterGraph("resource/boss/dscrap.png");

		ResourceServer::RegisterGraph("resource/boss/righthand.png");
		ResourceServer::RegisterGraph("resource/boss/drighthand.png");
		ResourceServer::RegisterGraph("resource/boss/lefthand.png");
		ResourceServer::RegisterGraph("resource/boss/dlefthand.png");
		ResourceServer::RegisterGraph("resource/boss/leftsand.png");
		ResourceServer::RegisterGraph("resource/boss/leftclock.png");
		ResourceServer::RegisterGraph("resource/boss/leftgear1.png");
		ResourceServer::RegisterGraph("resource/boss/leftgear2.png");
		ResourceServer::RegisterGraph("resource/boss/leftgear3.png");

		ResourceServer::RegisterGraph("resource/boss/dleftsand.png");
		ResourceServer::RegisterGraph("resource/boss/dleftclock.png");
		ResourceServer::RegisterGraph("resource/boss/dleftgear1.png");
		ResourceServer::RegisterGraph("resource/boss/dleftgear2.png");
		ResourceServer::RegisterGraph("resource/boss/dleftgear3.png");

		ResourceServer::RegisterGraph("resource/boss/right_a.png");
		ResourceServer::RegisterGraph("resource/boss/right_b.png");
		ResourceServer::RegisterGraph("resource/boss/right_c.png");
		ResourceServer::RegisterGraph("resource/boss/rightgear1.png");
		ResourceServer::RegisterGraph("resource/boss/rightgear2.png");
		ResourceServer::RegisterGraph("resource/boss/rightgear3.png");

		ResourceServer::RegisterGraph("resource/boss/dright_a.png");
		ResourceServer::RegisterGraph("resource/boss/dright_b.png");
		ResourceServer::RegisterGraph("resource/boss/dright_c.png");
		ResourceServer::RegisterGraph("resource/boss/drightgear1.png");
		ResourceServer::RegisterGraph("resource/boss/drightgear2.png");
		ResourceServer::RegisterGraph("resource/boss/drightgear3.png");

		ResourceServer::RegisterGraph("resource/background/background.png");
		ResourceServer::RegisterGraph("resource/background/arch_d.png");
		ResourceServer::RegisterGraph("resource/background/arch_c.png");
		ResourceServer::RegisterGraph("resource/background/arch_b.png");
		ResourceServer::RegisterGraph("resource/background/arch_a.png");
		ResourceServer::RegisterGraph("resource/background/sitting_d.png");
		ResourceServer::RegisterGraph("resource/background/sitting_c.png");
		ResourceServer::RegisterGraph("resource/background/sitting_b.png");
		ResourceServer::RegisterGraph("resource/background/sitting_a.png");
		ResourceServer::RegisterGraph("resource/background/penlight_d2.png");
		ResourceServer::RegisterGraph("resource/background/penlight_c2.png");
		ResourceServer::RegisterGraph("resource/background/penlight_b2.png");
		ResourceServer::RegisterGraph("resource/background/penlight_a2.png");
		ResourceServer::RegisterGraph("resource/background/background_spot.png");
		ResourceServer::RegisterGraph("resource/background/stage.png");
		ResourceServer::RegisterGraph("resource/background/standing.png");
	}
}