/**
 * @file	AMG_Summer_Co_Production_2020\script\Player_Appear.cpp.
 *
 * @brief	プレイヤー登場時の処理
 */

#include"Player.h"
#include"../Game.h"
using namespace illumism;

void Player::Appear(Game& _game)
{
	//落下処理
	m_y -= m_falling_speed;
	m_falling_speed -= 1;

	//地面に接地している場合は、Y座標をリセット・加速度を０にしアニメーションを終了
	if (m_y >= (GROUND - m_height))
	{
		m_y = GROUND - m_height;
		m_falling_speed = 0;
		m_animation_running_flag = false;
	}

	m_graph = m_wait_graph[(m_frame_count / 2) % 30];

	if (m_frame_count > START_TIME)
		m_player_state = JUMP;
}