/**
 * @file	AMG_Summer_Co_Production_2020\script\Player_Respawn.cpp
 *
 * @brief	HP=0になった時のリスポーン処理
 */

#include"Player.h"
#include"../Object/PointObject.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
using namespace illumism;

void Player::Respawn(Game& _game)
{
	//初めに一度だけ実行される処理
	if (m_respawn_time == 0)
	{
		//死亡回数をカウント
		ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
		modeGame->AddDeathCount(PLAYER_NUM, 1);

		m_respawn_time = m_frame_count;
		m_ishit_flag = false;
	}

	//死亡アニメーション再生
	if (m_frame_count - m_respawn_time < 90)
		m_graph = m_death_graph[(m_frame_count - m_respawn_time) / 2 % 45];

	//100ポイント放出
	if (m_frame_count - m_respawn_time == 90)
	{
		for (int i = 0; i < 10; i++)
		{
			PointObject* point_object = new PointObject();

			point_object->SetPosition(m_x + (m_width - point_object->GetWidth()) / 2,
				m_y + (m_height - point_object->GetHeight()) / 2);

			_game.m_objectserver.Add(point_object);
		}
		PlaySE("resource/se/playerdead.wav", _game);
	}

	//3秒間リスポーン時間
	if (m_frame_count - m_respawn_time >= 90 &&
		m_frame_count - m_respawn_time < 90 + 60 * 3)
	{
		SetType(ObjectBase::OBJECT_TYPE::NOHIT);
		m_isAlive_flag = false;
	}

	if (m_frame_count - m_respawn_time == 90 + 60 * 3)
	{
		SetType(ObjectBase::OBJECT_TYPE::PLAYER);
		
		//プレイヤーごとに初期位置を設定
		if (PLAYER_NUM == 1)
		{
			m_x = 540;
			m_direction_x = RIGHT;
			m_turn_flag = false;
		}
		else if (PLAYER_NUM == 2)
		{
			m_x = 1365;
			m_direction_x = LEFT;
			m_turn_flag = true;
		}

		//フラグをリセット
		m_isAlive_flag = true;
		m_ishit_flag = true;
		m_move_flag = false;
		m_attack_flag = false;
		m_appeal_flag = false;
		m_touch_flag = false;
		m_spmove_flag = false;
		m_hit_no_count = 90;
		m_respawn_time = 0;
		m_graph = m_wait_graph[0];
		m_params.HP = 100;
		m_player_state = JUMP;
	}

	//空中で死亡した場合、そのまま落下
	if (m_y + m_height < GROUND)
	{
		m_y -= m_falling_speed;
		m_falling_speed -= 2;
	}
}