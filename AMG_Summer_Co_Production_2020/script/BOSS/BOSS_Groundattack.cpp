/**
 * @file	AMG_Summer_Co_Production_2020\script\BOSS_Groundattack.cpp.
 *
 *	@brief	BOSS‚Ì’n–Ê‚©‚ç™UŒ‚ˆ—
 */

#include"BOSS.h"
#include"GroundAttack.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
using namespace illumism;

void BOSS::GroundAttack(Game& _game)
{
	if (once_flag)
	{
		m_start_frame = m_frame_count;
		once_flag = false;
	}

	//20•bŠÔUŒ‚
	if (m_frame_count - m_start_frame < 60 * 20)
	{
		//4•b‚Éˆê“xUŒ‚
		if ((m_frame_count - m_start_frame) % 240 == 0)
		{
			GenerateGroundAttack(_game);
			PlaySE("resource/se/bossmotion.wav", _game);
		}
		return;
	}

	once_flag = true;
	m_boss_state = MOVE;
}

void BOSS::GenerateGroundAttack(Game& _game)
{
	for (int i = 0; i < 5; i++)
	{
		int _angle;

		//¶¬‚·‚é‰ÓŠ‚É‚æ‚Á‚ÄŠp“x‚ğƒ‰ƒ“ƒ_ƒ€‚ÉŒˆ‚ß‚é
		if (i == 0) { _angle = GetRand(30); }
		if (i == 1) { _angle = GetRand(60) - 30; }
		if (i == 2) { _angle = GetRand(60) - 30; }
		if (i == 3) { _angle = GetRand(60) - 30; }
		if (i == 4) { _angle = -GetRand(30); }

		//‰æ–Ê•‚Ì1/5`4/5‚Ìl“_‚©‚ç¶¬
		::GroundAttack* ground_attack = new ::GroundAttack(SCREEN_WIDTH * (i + 1) / 6,
			GROUND + m_height, _angle, GetRand(2));

		_game.m_objectserver.Add(ground_attack);
	}
}