/**
 * @file	AMG_Summer_Co_Production_2020\script\Player_Attack.cpp.
 *
 * @brief	ATTACK攻撃を行う処理（Bボタン）
 */

#include"Player.h"
#include"Attack.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
using namespace illumism;

void Player::Attack(Game& _game)
{
	if (_game.m_trigger_key[PLAYER_NUM - 1] & PAD_INPUT_2 &&
		m_attack_flag == false)
	{
		m_attack_flag = true;
		m_animation_running_flag = true;
		m_attack_frame = m_frame_count;

		if (m_y + m_height >= GROUND)
			m_move_flag = true;

		m_Attack = new ::Attack(PLAYER_NUM);
		m_Attack->SetDirection(_game, PLAYER_NUM, m_turn_flag);

		if (m_direction_x == RIGHT)
			m_Attack->SetPosition(m_x + m_hit_x + m_hit_w, m_y + m_hit_y + m_hit_h / 3);
		else
			m_Attack->SetPosition(m_x + m_hit_x - m_Attack->GetWidth(), m_y + m_hit_y + m_hit_h / 3);

		_game.m_objectserver.Add(m_Attack);

		PlaySE("resource/se/attack.wav", _game);
	}
	else
	{
		//指定時間内であればアニメーションの再生し、プレイヤー状態の設定
		if (m_frame_count - m_attack_frame < 27)
		{
			m_player_state = ATTACK;

			//ジャンプ中にアタックした場合当たり判定座標を更新
			if (m_direction_x == RIGHT)
				m_Attack->SetPosition(m_x + m_hit_x + m_hit_w, m_y + m_hit_y + m_hit_h / 2);
			else
				m_Attack->SetPosition(m_x + m_hit_x - m_Attack->GetWidth(), m_y + m_hit_y + m_hit_h / 2);

			//落下処理
			m_y -= m_falling_speed;
			m_falling_speed -= 1;

			if (m_y >= (GROUND - m_height))
			{
				m_y = GROUND - m_height;
				m_falling_speed = 0;
				m_animation_running_flag = false;
			}

			m_graph = m_attack_graph[((m_frame_count - m_attack_frame) / 1) % 27];
		}
		else
		{
			m_move_flag = false;
			m_inertia = 0;
			m_attack_flag = false;
			m_player_state = JUMP;
		}
	}
}