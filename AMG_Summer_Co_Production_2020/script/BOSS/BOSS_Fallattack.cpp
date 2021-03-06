/**
 * @file	AMG_Summer_Co_Production_2020\script\BOSS_Fallattack.cpp.
 *  
 * @brief　BOSSの落ちもの攻撃処理
 */

#include"BOSS.h"
#include"FallAttack.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
using namespace illumism;

void BOSS::FallAttack(Game& _game)
{
	if (once_flag)
	{
		PlaySE("resource/se/bossmotion.wav", _game);

		m_start_frame = m_frame_count;
		once_flag = false;
	}

	//予備動作
	if (m_frame_count - m_start_frame < 90)
		return;

	//20秒間攻撃
	if (m_frame_count - m_start_frame < 60 * 20)
	{
		if (m_frame_count % 60 == 0)
			GenerateFallAttack(_game);

		return;
	}

	once_flag = true;
	m_boss_state = MOVE;
}

void BOSS::GenerateFallAttack(Game& _game)
{
	for (int i = 0; i < 2; i++)
	{
		//3種類の色からランダムで選ぶ
		::FallAttack* fall_attack = new ::FallAttack(GetRand(2));

		if (i == 0)
		{
			//画面の左半分から生成
			fall_attack->SetPosition(SCREEN_WIDTH * (GetRand(3) + 2) / 10, -220);
			fall_attack->SetSpeed(5 + GetRand(2));
		}
		else
		{
			//画面の右半分から生成
			fall_attack->SetPosition(SCREEN_WIDTH * (GetRand(2) + 6) / 10, -220);
			fall_attack->SetSpeed(5 + GetRand(2));
		}
		_game.m_objectserver.Add(fall_attack);
	}
}