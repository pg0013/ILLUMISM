/**
 * @file	AMG_Summer_Co_Production_2020\script\BOSS_Crosslaser.cpp.
 *
 * @brief	BOSSの複数方向レーザー攻撃処理
 *
 */

#include"BOSS.h"
#include"CrossLaser.h"
#include"../Game.h"
using namespace illumism;

void BOSS::CrossLaser(Game& _game)
{
	if (once_flag)
	{
		PlaySE("resource/se/bossmotion.wav", _game);

		m_start_frame = m_frame_count;
		once_flag = false;
	}

	//予備動作中はなにもしない
	if (m_frame_count - m_start_frame < 90)
		return;

	//20秒間攻撃
	if (m_frame_count - m_start_frame < 60 * 20)
	{
		if ((m_frame_count - m_start_frame) % 100 == 0)
			GenerateCrossLaser(_game);

		return;
	}

	once_flag = true;
	m_boss_state = MOVE;
}

void BOSS::GenerateCrossLaser(Game& _game)
{
	//上下左右からランダムに生成
	::CrossLaser* cross_laser = new ::CrossLaser(GetRand(3));
	cross_laser->SetSpeed(6 + GetRand(4));

	_game.m_objectserver.Add(cross_laser);
}