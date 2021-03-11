/**
 * @file	AMG_Summer_Co_Production_2020\script\Player_Appeal.cpp.
 *
 *	@brief	アピールアクションの処理（LB）
 */

#include"Player.h"
#include"../Effect/Particle.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
using namespace illumism;

void Player::Appeal(Game& _game)
{
	if (_game.m_trigger_key[PLAYER_NUM - 1] & PAD_INPUT_5)
	{
		ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");

		//アピール中は時間計測をしない
		if (m_appeal_flag == false)
		{
			//協力技用に押した時間を記録
			modeGame->m_coopmove_controller.SetPushTime(PLAYER_NUM, GetNowCount());
			//アニメーション開始フレームを記録
			m_appeal_frame = m_frame_count;
			m_move_flag = false;
		}

		for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
		{
			if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::SPOTLIGHT)
			{
				if (IsHit(*(*iter)) == false)
					break;

				AddPOINT(100);
				AddMP(50);
				//スポットライトの当たり判定を消す
				(*iter)->Damage(_game);

				//アピール成功エフェクトを生成
				for (int i = 0; i < 100; i++)
				{
					double vx = (GetRand(12) - 6) / 10.0;
					double vy = -GetRand(25) / 10.0;

					Particle* particle = new Particle("resource/object/fly_test_13.png",
						m_x + 50, m_y + 210, vx, 1.5 * vy, 50);
					particle->SetBright(255, 255, 0);

					_game.m_objectserver.Add(particle);
				}
			}
		}
	}

	//アニメーションを有効時間内ならば
	if (m_frame_count - m_appeal_frame < 80)
	{
		if (m_frame_count - m_appeal_frame == 0)
			PlaySE("resource/se/appeal.wav", _game);

		m_appeal_flag = true;
		m_player_state = APPEAL;
		m_animation_running_flag = true;
		m_graph = m_appeal_graph[((m_frame_count - m_appeal_frame) / 2 % 40)];
	}
	else
	{
		m_appeal_flag = false;
		m_animation_running_flag = false;	
		m_appeal_frame = 0;
		m_inertia = 0;

		//押された時間の初期化
		//時間を0にしないのは、差分計算をするときに0だと同時押し判定になってしまうため
		ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
		modeGame->m_coopmove_controller.SetPushTime(PLAYER_NUM, (PLAYER_NUM - 1) * 999);

		m_player_state = JUMP;
	}
}