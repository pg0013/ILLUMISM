/**
 * @file	AMG_Summer_Co_Production_2020\script\BOSS_Simplelaser.cpp.
 *
 * @brief	一方向のみのレーザー攻撃処理
 */

#include"BOSS.h"
#include"CrossLaser.h"
#include"../Game.h"
using namespace illumism;

void BOSS::SimpleLaser(Game& _game)
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
		GenerateSimpleLaser(_game);
		return;
	}

	once_flag = true;
	m_boss_state = MOVE;
}

void BOSS::GenerateSimpleLaser(Game& _game)
{
	int laser_count = 0;

	//生成されているオブジェクトの数を数える
	for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
	{
		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::CROSSBEAM)
		{
			laser_count++;
		}
	}

	//レーザーが画面外に到達してから、次のレーザーを生成する
	if (laser_count < 1)
	{
		//上下左右からランダムに生成
		::CrossLaser* cross_laser = new ::CrossLaser(GetRand(3));
		cross_laser->SetSpeed(6 + GetRand(4));

		_game.m_objectserver.Add(cross_laser);
	}
}