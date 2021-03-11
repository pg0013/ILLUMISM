/**
 * @file	AMG_Summer_Co_Production_2020\script\BOSS_Destroy.cpp.
 *
 * @brief	ボス撃破時の処理
 */

#include"BOSS.h"
#include"../Object/PointObject.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
using namespace illumism;

void BOSS::Destroy(Game& _game)
{
	//一度だけ実行
	if (once_death_flag)
	{
		PlaySE("resource/se/boss_destroy.wav", _game);

		m_start_frame = m_frame_count;
		once_death_flag = false;
	}

	//8秒間点滅
	if (m_frame_count - m_start_frame < 60 * 8)
	{
		m_blinking_flag = true;
		m_damage_frame = m_frame_count;

		m_center.SetPosition(m_x + m_width / 2, m_y + m_height / 2);
		m_left.SetPosition(m_x + m_width / 2 - 220, m_y + m_height / 2);
		m_right.SetPosition(m_x + m_width / 2 + 220, m_y + m_height / 2);

		return;
	}

	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	//500ポイント放出
	for (int i = 0; i < 50; i++)
	{
		PointObject* point_object = new PointObject();

		point_object->SetPosition(x + (m_width - point_object->GetWidth()) / 2,
			m_y + (m_height - point_object->GetHeight()) / 2);

		_game.m_objectserver.Add(point_object);
	}
	_game.m_objectserver.Delete(this);
}