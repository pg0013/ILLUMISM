/**
 * @file	AMG_Summer_Co_Production_2020\script\Player_Move.cpp.
 *
 * @brief	移動処理（Lスティック）
 */

#include"Player.h"
#include"../Game.h"
using namespace illumism;

void Player::Move(Game& _game)
{
	//パッド入力判定をし、プレイヤーを移動(←・→)
	if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX < -ANALOG_MIN)
	{
		m_direction_x = LEFT;
		m_turn_flag = true;

		if (_game.m_gkey[PLAYER_NUM - 1] & PAD_INPUT_UP)
			m_direction_y = UP;
		else if (_game.m_gkey[PLAYER_NUM - 1] & PAD_INPUT_DOWN)
			m_direction_y = DOWN;

		//プレイヤーが動くスティックの傾き量にマージンを設けて
		// プレイヤーを動かしてからスティックを離したときに、慣性で止まるにする
		if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX < -ANALOG_MIN)
		{
			//移動制限（SHOOT固定撃ち）
			if (m_move_flag)
				return;

			//Lスティックを傾けた量だけ移動
			//FLY中はマージンをとらない処理で移動する
			if (m_fly_flag == false)
			{
				m_inertia = static_cast<int>(m_speed * _game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX);
				m_x += m_inertia;
			}
		}

		//地面でのみダッシュアニメーション
		if (m_y == (GROUND - m_height) &&
			m_animation_running_flag == false)
		{
			m_graph = m_dash_graph[(m_frame_count / 2) % 20];
		}
	}
	else if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX > ANALOG_MIN)
	{
		m_direction_x = RIGHT;
		m_turn_flag = false;

		if (_game.m_gkey[PLAYER_NUM - 1] & PAD_INPUT_UP)
			m_direction_y = UP;
		else if (_game.m_gkey[PLAYER_NUM - 1] & PAD_INPUT_DOWN)
			m_direction_y = DOWN;

		//プレイヤーが動くスティックの傾き量にマージンを設けて
		// プレイヤーを動かしてからスティックを離したときに、慣性で止まるにする
		if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX > ANALOG_MIN)
		{
			//移動制限（SHOOT固定撃ち）
			if (m_move_flag)
				return;

			//Lスティックを傾けた量だけ移動
			//FLY中はマージンをとらない処理で移動する
			if (m_fly_flag == false)
			{
				m_inertia = static_cast<int>(m_speed * _game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX);
				m_x += m_inertia;
			}
		}

		//地面でのみダッシュアニメーション
		if (m_y == (GROUND - m_height) &&
			m_animation_running_flag == false)
		{
			m_graph = m_dash_graph[(m_frame_count / 2) % 20];
		}
	}
	else
	{
		//飛行状態でなく、かつ動作中のアニメーションがない時だけ待機モーション
		if (m_fly_flag == false && m_animation_running_flag == false)
			m_graph = m_wait_graph[(m_frame_count / 2) % 30];

		//スティックを離したときに慣性で移動
		if (m_move_flag == false)
		{
			m_inertia = static_cast<int>(m_inertia * 0.8);
			m_x += m_inertia;
		}
	}
}