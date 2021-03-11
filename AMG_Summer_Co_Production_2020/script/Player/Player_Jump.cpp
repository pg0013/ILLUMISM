/**
 * @file	AMG_Summer_Co_Production_2020\script\Player_Jump.cpp
 *
 * @brief	ジャンプ処理（Aボタン）
 */

#include"Player.h"
#include"../Effect/LandingParticle.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
using namespace illumism;

void Player::Jump(Game& _game)
{
	//飛行中はジャンプ禁止
	if (m_fly_flag)
		return;

	int pre_falling = m_falling_speed;

	//落下処理
	m_y -= m_falling_speed;
	m_falling_speed -= 1;

	//地面に接地している場合は、Y座標をリセット・加速度を０にしアニメーションを終了
	if (m_y >= (GROUND - m_height))
	{
		m_y = GROUND - m_height;
		m_falling_speed = 0;
		m_animation_running_flag = false;

		if (pre_falling != 0 && m_falling_speed == 0)
		{
			ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
			int x = m_x + m_width / 2 - modeGame->m_camera.GetScreenX();
			LandingParticle* landing_effect = new LandingParticle(x, m_y + m_height / 2, 30);
			_game.m_objectserver.Add(landing_effect);
		}
	}

	//地面でAボタンが押されたらジャンプ
	if ((_game.m_trigger_key[PLAYER_NUM - 1] & PAD_INPUT_1) &&
		m_y == (GROUND - m_height))
	{
		m_falling_speed = JUMP_HEIGHT;
		m_animation_running_flag = true;
		m_jump_frame = m_frame_count;

		PlaySE("resource/se/jump.wav", _game);
	}

	//ジャンプ中にSHOOTを行ったときに画像をSHOOT画像にする
	if (_game.m_xinput_state[PLAYER_NUM - 1].RightTrigger == 255 &&
		m_player_state == SHOOT &&
		((m_y < (GROUND - m_height)) || m_falling_speed != 0))
	{
		if (floor((_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX) * 10) / 10 == 0 &&
			_game.m_xinput_state[PLAYER_NUM - 1].ThumbLY/THUMB_MAX > ANALOG_MIN)//上
			m_graph = m_shoot_up_graph[m_frame_count / 2 % 5];
		if (floor((_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX) * 10) / 10 == 0 &&
			_game.m_xinput_state[PLAYER_NUM - 1].ThumbLY/THUMB_MAX < -ANALOG_MIN)//下
			m_graph = m_shoot_downleft_graph[m_frame_count / 2 % 5];
		else if (floor((_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX) * 10) / 10 != 0 &&
			_game.m_xinput_state[PLAYER_NUM - 1].ThumbLY/THUMB_MAX > ANALOG_MIN)//左上
			m_graph = m_shoot_upleft_graph[m_frame_count / 2 % 5];
		else if (floor((_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX) * 10) / 10 != 0 &&
			_game.m_xinput_state[PLAYER_NUM - 1].ThumbLY/THUMB_MAX < -ANALOG_MIN)//左下
			m_graph = m_shoot_downleft_graph[m_frame_count / 2 % 5];

		return;
	}

	//ジャンプ中はジャンプ画像に設定
	// 踏み切ってから頂点まで
	if (m_falling_speed > 0)
		m_graph = m_jump_graph[((m_frame_count - m_jump_frame) / 2) % 14];
	//頂点から落下
	if (m_falling_speed < 0)
		m_graph = m_jump_graph[13 + ((m_frame_count - m_jump_frame) / 2) % 13];
}