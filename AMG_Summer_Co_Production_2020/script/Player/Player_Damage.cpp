/**
 * @file	AMG_Summer_Co_Production_2020\script\Player_Damage.cpp.
 *
 *	@brief	ダメージを受けたときの処理
 */

#include"Player.h"
#include"../Effect/HitEffect.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
using namespace illumism;

void Player::Damage(Game& _game)
{

	if (m_damage_frame == 0)
	{
		PlaySE("resource/se/player_damage.wav", _game);
		m_combo = -1;									//2回タッチしたら1コンボになるように初期化
		m_damage_frame = m_frame_count;	//アニメーションの開始時間を記録

		//画面ブレ設定
		ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
		modeGame->m_camera.SetVibrationCount(5);

		//ヒットエフェクト生成
		HitEffect* hiteffect = new HitEffect(m_x+m_width/2, m_y, 16);
		hiteffect->SetPositionOffset(modeGame->GetPlayerCharactor(PLAYER_NUM), m_direction_x);
		_game.m_objectserver.Add(hiteffect);
	}

	if (m_frame_count - m_damage_frame < 30)
	{
		m_player_state = DAMAGE;
		m_hit_no_count = 30;
		m_animation_running_flag = true;

		m_move_flag = true;
		//空中でダメージを受けた場合、左右移動できずに落下する
		if (m_y + m_height < GROUND)
		{
			//落下処理
			m_y -= m_falling_speed;
			//落下加速度を加える
			m_falling_speed -= 2;
		}

		//ダメージを受けたときの後ずさり
		if (m_frame_count - m_damage_frame < 10)
		{
			if (m_direction_x == LEFT)
			{
				m_x += 5;
			}
			if (m_direction_x == RIGHT)
			{
				m_x -= 5;
			}
		}

		//アニメーション再生
		if (m_frame_count - m_damage_frame < 30)
			m_graph = m_damage_graph[(m_frame_count - m_damage_frame) / 2 % 15];
	}
	else
	{
		m_animation_running_flag = false;
		m_move_flag = false;

		//モーション中にダメージを受けたときのために、モーションフラグを初期化
		m_attack_flag = false;
		m_appeal_flag = false;
		m_touch_flag = false;
		m_spmove_flag = false;

		m_damage_frame = 0;
		m_inertia = 0;
		m_player_state = JUMP;
	}
}