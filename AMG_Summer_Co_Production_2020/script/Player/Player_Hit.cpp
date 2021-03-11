/**
 * @file	AMG_Summer_Co_Production_2020\script\Player_Hit.cpp.
 *
 * @brief	プレイヤーに対する当たり判定処理
 */

#include"Player.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
using namespace illumism;

void Player::Hit(Game& _game)
{
	for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
	{
		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::PLAYER)
		{
			//自分自身と当たっているを除外
			if ((*iter) == this) { continue; }

			//他プレイヤーと当たり判定
			if (IsHit(*(*iter)) == true)
			{
				//相手にのめりこまないように処理
				if (m_x <= (*iter)->GetPosX())
				{
					//ステージ右端でのすり抜け防止
					if ((*iter)->GetPosX() >= STAGE_WIDTH_RIGHT - m_width)
					{
						m_x = (*iter)->GetPosX() + (*iter)->GetPosHit_x() - m_hit_x - m_hit_w;
						return;
					}
					//相手を押し出し、自分の座標を更新
					(*iter)->SetPosition(m_x - (*iter)->GetPosHit_x() + m_hit_x + m_hit_w, (*iter)->GetPosY());
					m_x = (*iter)->GetPosX() + (*iter)->GetPosHit_x() - m_hit_x - m_hit_w;
				}
				if (m_x > (*iter)->GetPosX())
				{
					//ステージ左端でのすり抜け防止
					if ((*iter)->GetPosX() <= STAGE_WIDTH_LEFT)
					{
						m_x = (*iter)->GetPosX() - (*iter)->GetPosHit_x() + m_hit_x + m_hit_w;
						return;
					}
					//相手を押し出し、自分の座標を更新
					(*iter)->SetPosition(m_x + (*iter)->GetPosHit_x() - m_hit_x - m_hit_w, (*iter)->GetPosY());
					m_x = (*iter)->GetPosX() - (*iter)->GetPosHit_x() + m_hit_x + m_hit_w;
				}
			}

			//ATTACKされたら相手にポイントを加算し、加算ポイントをリセット
			(*iter)->AddPOINT(-m_attacked_point);
			m_attacked_point = 0;
		}

		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::ATTACK)
		{
			if (IsHit(*(*iter)) == true)
			{
				//ダメージを受けているときは無効
				if (m_player_state != DAMAGE)
				{
					if (GetPOINT() >= -ATTACK_DAMAGE)//取れるポイントがあったらポイントを設定
						m_attacked_point = ATTACK_DAMAGE;
					else
						m_attacked_point = 0;//なかったらポイントをとらない
					AddPOINT(m_attacked_point);//自分のポイントを減算
					SetDamagedDirection(_game);
					Damage(_game);
					//相手のATTACK当たり判定を消去
					(*iter)->Damage(_game);
				}
			}
		}

		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::BULLET)
		{
			if (IsHit(*(*iter)) == true)
			{
				AddHP(BULLET_DAMAGE);
				SetDamagedDirection(_game);
				Damage(_game);
				//弾丸を消去
				(*iter)->Damage(_game);
			}
		}

		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::POINT)
		{
			if (IsHit(*(*iter)) == true)
			{
				AddPOINT(10);
				PlaySE("resource/se/getpoint.wav", _game);
				//タッチオブジェクトを消去
				(*iter)->Damage(_game);
			}
		}

		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::SPMOVE)
		{
			if (IsHit(*(*iter)) == true)
			{
				AddHP(SPMOVE_DAMAGE);
				if ((*iter)->GetDirection_x() == LEFT)
				{
					m_turn_flag = FALSE;
					m_direction_x = RIGHT;
				}
				else
				{
					m_turn_flag = TRUE;
					m_direction_x = LEFT;
				}
				Damage(_game);
			}
		}

		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::FALLATTACK)
		{
			if (IsHit(*(*iter)) == true)
			{
				AddHP(BOSS_ATTACK_DAMAGE);
				if (m_x <= (*iter)->GetPosX() + (*iter)->GetPosHit_x() + (*iter)->GetPosHit_w() / 2)
				{
					m_turn_flag = FALSE;
					m_direction_x = RIGHT;
				}
				else
				{
					m_turn_flag = TRUE;
					m_direction_x = LEFT;
				}
				Damage(_game);
				(*iter)->Damage(_game);
			}
		}

		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::CROSSBEAM)
		{
			if (IsHit(*(*iter)) == true)
			{
				AddHP(BOSS_ATTACK_DAMAGE);
				if ((*iter)->GetPosX() > 0 && m_x + m_hit_x + m_hit_w / 2 <= (*iter)->GetPosX() + (*iter)->GetPosHit_x())
				{
					m_turn_flag = FALSE;
					m_direction_x = RIGHT;
				}
				else if ((*iter)->GetPosX() > 0 && m_x + m_hit_x + m_hit_w / 2 > (*iter)->GetPosX() + (*iter)->GetPosHit_x())
				{
					m_turn_flag = TRUE;
					m_direction_x = LEFT;
				}
				Damage(_game);
			}
		}
	}
}

void Player::SetDamagedDirection(Game& _game)
{
	for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
	{
		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::PLAYER)
		{
			//自分自身と当たっているを除外
			if ((*iter) == this) { continue; }

			//←から攻撃を受けたら右を向く
			if (m_x <= (*iter)->GetPosX())
			{
				m_turn_flag = FALSE;
				m_direction_x = RIGHT;
			}
			//→から攻撃を受けたら左を向く
			if (m_x > (*iter)->GetPosX())
			{
				m_turn_flag = TRUE;
				m_direction_x = LEFT;
			}
		}
	}
}