/**
 * @file	AMG_Summer_Co_Production_2020\script\Player_Touch.cpp
 *
 * @brief	タッチアクションの処理（Xボタン）
 */

#include"Player.h"
#include"../UI/Combo.h"
#include"../Effect/TouchParticle.h"
#include"../Effect/TouchSuccessEffect.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
using namespace illumism;

void Player::Touch(Game& _game)
{
	if (_game.m_trigger_key[PLAYER_NUM - 1] & PAD_INPUT_3 &&
		m_touch_flag == false)
	{
		m_animation_running_flag = true;
		m_touch_frame = m_frame_count;
		m_move_flag = false;

		for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
		{
			if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::TOUCH_S ||
				(*iter)->GetType() == ObjectBase::OBJECT_TYPE::TOUCH_C)
			{
				if (IsHit(*(*iter)) == false)
					continue;

				AddPOINT((*iter)->GetPOINT());
				AddMP((*iter)->GetMP());

				m_combo++;
				GenerateComboEffect(_game);
				GenerateTouchParticle(_game, *iter);

				//コンボ効果を付与
				if (m_combo >= 2)
				{
					if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::TOUCH_S)
						AddPOINT(5);
					if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::TOUCH_C)
						AddHP(10);
				}

				(*iter)->Damage(_game);

				auto checkCombo = [](float _combo)->float
				{
					float pitch = static_cast<float>(pow(1.02, _combo));
					if (pitch > 16.0f) { pitch = 16.0f; }
					return pitch;
				};
				float combo_pitch = checkCombo(static_cast<float>(m_combo));

				PlaySE("resource/se/touch.wav", _game);
				m_se.Pitch(combo_pitch);
			}
		}
		//コンボ最大値を記録
		if (m_max_combo < m_combo)
		{
			m_max_combo = m_combo;
			ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
			modeGame->AddMaxCombo(PLAYER_NUM, m_max_combo);
		}
		m_touch_flag = true;
	}
	else
	{
		//指定時間内はアニメーションを再生
		if (m_frame_count - m_touch_frame < 30)
		{
			m_player_state = TOUCH;
			m_graph = m_touch_graph[((m_frame_count - m_touch_frame) / 2) % 15];
		}
		else
		{
			m_touch_flag = false;
			m_player_state = JUMP;
		}
	}
}

void Player::GenerateComboEffect(Game& _game)
{
	Combo* combo = new Combo(PLAYER_NUM, m_combo);
	combo->SetPosition(m_x + 100, m_y + 50);
	_game.m_objectserver.Add(combo);

	TouchSuccessEffect* toucheffect = new TouchSuccessEffect(PLAYER_NUM, 30);
	_game.m_objectserver.Add(toucheffect);
}

void Player::GenerateTouchParticle(Game& _game, ObjectBase* iter)
{
	int x;

	if (PLAYER_NUM == 1)
		x = SCREEN_WIDTH / 4 - m_width / 2 + 250;
	if (PLAYER_NUM == 2)
		x = SCREEN_WIDTH * 3 / 4 - m_width / 2 + 250;

	for (int i = 0; i < 5 * iter->GetPOINT(); i++)
	{
		double vx = static_cast<double>(GetRand(50) - 20) / 10.0;
		double vy = static_cast<double>(GetRand(50) - 20) / 10.0;

		TouchParticle* touchparticle = new TouchParticle("resource/object/fly_test_10.png", x, static_cast<double>(GROUND + 80), vx, vy, 50);
		touchparticle->SetBright(100, 91, 18);
		_game.m_objectserver.Add(touchparticle);
	}

}