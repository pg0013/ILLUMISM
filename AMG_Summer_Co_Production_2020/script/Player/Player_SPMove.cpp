/**
 * @file	AMG_Summer_Co_Production_2020\script\Player_SPMove.cpp.
 *
 * @brief	必殺技アクションの処理
 */

#include"Player.h"
#include"SPMove.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
using namespace illumism;

void Player::SPMove(Game& _game)
{
	//必殺技ゲージ満タンでYボタンが押された
	if (_game.m_trigger_key[PLAYER_NUM - 1] & PAD_INPUT_4 &&
		m_params.MP == 100)
	{
		m_spmove_flag = true;
		m_animation_running_flag = true;
		m_spmove_frame = m_frame_count;
		SetType(ObjectBase::OBJECT_TYPE::NOHIT);	//当たり判定を無効（他プレイヤーの押し出し）
		m_ishit_flag = false;//当たり判定を無効（攻撃）
		m_move_flag = false;

		PlaySE("resource/se/spmove.wav", _game);

		m_spmove = new ::SPMove(PLAYER_NUM);
		m_spmove->SetDirection(_game, PLAYER_NUM, m_turn_flag);

		if (m_direction_x == RIGHT)
			m_spmove->SetPosition(m_x + m_hit_x + m_hit_w + 20, m_y + m_hit_y - m_spmove->GetHeight() / 2);
		else
			m_spmove->SetPosition(m_x + m_hit_x - m_spmove->GetWidth() - 20, m_y + m_hit_y - m_spmove->GetHeight() / 2);

		_game.m_objectserver.Add(m_spmove);
		m_params.MP = 0;
	}
	else
	{
		if (m_frame_count - m_spmove_frame <= 90 &&
			m_spmove_flag == true)
		{
			m_player_state = SPMOVE;
			m_falling_speed = 0;
			m_graph = m_shoot_graph[0];
			//必殺技終了時に無敵時間を設定
			if (m_frame_count - m_spmove_frame == 90)
				m_hit_no_count = 30;
		}
		else
		{
			m_spmove_flag = false;
			m_move_flag = false;
			m_inertia = 0;
			SetType(ObjectBase::OBJECT_TYPE::PLAYER);
			m_ishit_flag = true;
			m_player_state = JUMP;
		}
	}
}