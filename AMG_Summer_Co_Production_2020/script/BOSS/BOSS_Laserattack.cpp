/**
 * @file	AMG_Summer_Co_Production_2020\script\BOSS_Laserattack.cpp.
 *
 * @brief	BOSSのプレイヤーに向かうレーザー攻撃処理
 */

#include"BOSS.h"
#include"LaserAttack.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
using namespace illumism;

void BOSS::LaserAttack(Game& _game)
{
	if (once_flag)
	{
		m_start_frame = m_frame_count;
		once_flag = false;
	}

	//予備動作
	if (m_frame_count - m_start_frame < 90)
		return;

	//18秒間攻撃
	if (m_frame_count - m_start_frame < 60 * 18)
	{
		if ((m_frame_count - m_start_frame) % 60 == 0)
		{
			GenerateLaserAttack(_game);
		}

		//9秒後からは移動しながらレーザー攻撃を行う
		if (m_frame_count - m_start_frame > 60 * 9)
		{
			m_y = -200 + static_cast<int>(150 * sinf(DX_PI_F / 180 * ((m_frame_count - m_start_frame) % 360)));

			m_x += m_speed_x;
			if (m_x + m_hit_x < STAGE_WIDTH_LEFT)
				m_speed_x = 5;
			if (m_x + m_hit_x + m_hit_w >= STAGE_WIDTH_RIGHT)
				m_speed_x = -5;

			m_center.SetPosition(m_x + m_width / 2, m_y + m_height / 2);
			m_left.SetPosition(m_x + m_width / 2 - 220, m_y + m_height / 2);
			m_right.SetPosition(m_x + m_width / 2 + 220, m_y + m_height / 2);
		}
		return;
	}

	once_flag = true;
	m_boss_state = MOVE;
}

void BOSS::GenerateLaserAttack(Game& _game)
{
	int player_count = 0;
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");

	for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
	{
		//プレイヤーに向けてレーザーを撃つ
		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::PLAYER ||
			(*iter)->GetType() == ObjectBase::OBJECT_TYPE::FLY)
		{
			player_count++;

			::LaserAttack* laserattack = new ::LaserAttack(m_x + m_width / 2 + 25, m_y + m_height / 2 + 25,
				(*iter)->GetPosX() + (*iter)->GetWidth() / 2, (*iter)->GetPosY() + (*iter)->GetHeight() / 2 - 50, 15);

			_game.m_objectserver.Add(laserattack);

			//2発発射されるが、SEは一度だけ再生するかつ
			//プレイヤーがいないときにSEを流さない
			if (player_count == 1)
				PlaySE("resource/se/laser.wav", _game);
		}
	}
}