/**
 * @file	AMG_Summer_Co_Production_2020\script\Player_Fly.cpp.
 *
 *	@brief	飛行モード処理（LT）
 */

#include"Player.h"
#include"../Effect/Particle.h"
#include"../Utility/Utility.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
using namespace illumism;

void Player::Fly(Game& _game)
{
	//Lトリガーが押されている、かつ飛行可能時間内
	if (_game.m_xinput_state[PLAYER_NUM - 1].LeftTrigger == 255 &&
		m_fly_frame < m_fly_time)
	{
		m_fly_frame++;

		m_ishit_flag = false;
		m_fly_flag = true;
		m_move_flag = false;

		m_animation_running_flag = true;	//アニメーションを有効
		m_graph = m_lightball_graph;

		m_speed = FLY_SPEED;	//飛行中は移動速度が早くなる
		m_falling_speed = 0;		//飛行解除に急落下しないために初期化

		//トリガー入力
		if (m_fly_trigger_flag == false && m_fly_flag == true)
		{
			//FLYオブジェクトとして扱い、プレイヤーの当たり判定を無効にする
			SetType(ObjectBase::OBJECT_TYPE::FLY);

			PlaySE("resource/se/fly.wav", _game);
			m_se.Fade(0.0f, 0.6f);
		}

		//プレイヤー移動
		if (_game.m_gkey[PLAYER_NUM - 1] & PAD_INPUT_UP)
			m_y -= static_cast<int>(m_speed * _game.m_xinput_state[PLAYER_NUM - 1].ThumbLY / THUMB_MAX);
		if (_game.m_gkey[PLAYER_NUM - 1] & PAD_INPUT_DOWN)
			m_y -= static_cast<int>(m_speed * _game.m_xinput_state[PLAYER_NUM - 1].ThumbLY / THUMB_MAX);
		if (_game.m_gkey[PLAYER_NUM - 1] & PAD_INPUT_LEFT)
			m_x += static_cast<int>(m_speed * _game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX);
		if (_game.m_gkey[PLAYER_NUM - 1] & PAD_INPUT_RIGHT)
			m_x += static_cast<int>(m_speed * _game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX);

		//飛行移動中もPANを設定
		ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
		m_se.Pan(m_x + m_width / 2 - modeGame->m_camera.GetScreenX());

		for (int i = 0; i < 3; i++)
			GenerateFlyParticle(_game);
	}
	else
	{
		//当たり判定をプレイヤーに戻す
		SetType(ObjectBase::OBJECT_TYPE::PLAYER);

		//飛行時間を使い切ったら、MAXまで回復するまで使えない
		if (m_fly_frame >= m_fly_time)
		{
			m_fly_time = 0;
		}

		//飛行時間を回復
		m_fly_frame--;
		//回復しきったら飛行時間をMAXに
		if (m_fly_frame < 0)
		{
			m_fly_frame = 0;
			m_fly_time = FLY_TIME;
		}

		// LT押しっぱなしだとJump関数が実行されないので、ここで落下処理を行う
		m_y -= m_falling_speed;
		m_falling_speed -= 1;

		if (m_y >= (GROUND - m_height))
		{
			m_y = GROUND - m_height;
			m_falling_speed = 0;
			m_animation_running_flag = false;
		}

		if (m_falling_speed < 0)
			m_graph = m_jump_graph[((m_frame_count - m_jump_frame) / 2) % 27];

		m_ishit_flag = true;
		m_speed = MOVE_SPEED;
		m_animation_running_flag = false;
		m_fly_flag = false;

		m_touch_flag = false;
		m_player_state = TOUCH;
	}
	//前フレームの状態を保存
	m_fly_trigger_flag = m_fly_flag;
}

void Player::GenerateFlyParticle(Game& _game)
{
	//飛行中のプレイヤー番号識別用パーティクル
	Particle* particle_player = new Particle("resource/object/fly_test_13.png", static_cast<double>(m_x + 50.0), static_cast<double>(m_y + 100.0), 0, 0, 25);
	if (PLAYER_NUM == 1)
		particle_player->SetBright(95, 3, 69);
	else
		particle_player->SetBright(24, 84, 83);
	_game.m_objectserver.Add(particle_player);

	//虹色パーティクル
	double vx = static_cast<double>(GetRand(15) - 6.0) / 10.0;
	double vy = static_cast<double>(GetRand(15) - 6.0) / 10.0;
	Particle* particle = new Particle("resource/object/fly_test_13.png", static_cast<double>(m_x + 50.0), static_cast<double>(m_y + 100.0), vx, vy, 30);

	int* rainbow;
	if (PLAYER_NUM == 1)
		rainbow = utility::GetColorHSV(static_cast<float>((6 * m_frame_count) % 360), 1.0f, 1.0f);
	else
		rainbow = utility::GetColorHSV(static_cast<float>(360 - (6 * m_frame_count) % 360), 1.0f, 1.0f);
	particle->SetBright(rainbow[0], rainbow[1], rainbow[2]);
	_game.m_objectserver.Add(particle);
}