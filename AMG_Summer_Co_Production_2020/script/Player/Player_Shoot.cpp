/**
 * @file	AMG_Summer_Co_Production_2020\script\Player_Shoot.cpp
 *
 * @brief	弾丸を発射する攻撃処理(RT)
 */

#include"Player.h"
#include"../Game.h"
#include"../Mode/ModeGame.h"
#include"../Object/Bullet.h"
using namespace illumism;

void Player::Shoot(Game& _game)
{
	//Rトリガーが押された
	if (m_RT_flag)
	{
		m_animation_running_flag = true;

		//todo
		if (m_RT_flag == true && m_oldRT_flag == false)
		{
			//2度押し時間の基準となるフレームを記録
			if (m_pushRT_count == 0)
				m_pushRT_frame = m_frame_count;
			//はじめて押されたらカウンタは1
			m_pushRT_count++;

			//2回目押されたときに
			if (m_pushRT_count == 2)
			{
				//もし経過フレームが二度押し許容範囲内かつ地面ならば
				//移動せずに撃ってカウンタをリセット
				if (m_frame_count - m_pushRT_frame < 20 &&
					m_y + m_height == GROUND)
				{
					m_move_flag = true;
					m_inertia = 0;
					m_pushRT_count = 0;
				}
				//2回目なのに2度押し許容時間を過ぎていたら、
				// ボタン回数を1度目にして、フレームを記録を記録し次回比較する
				else
				{
					m_pushRT_count = 1;
					m_pushRT_frame = m_frame_count;
				}
			}
		}

		//ボタンが押されたときに弾発射フレームをカウント
		m_bullet_frame_count++;

		int bullet_count = 0;
		//弾オブジェクトをカウント
		for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
		{
			if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::BULLET)
				bullet_count++;
		}
		clsDx();
		//数が生成範囲内であれば
		if (bullet_count < BULLET_MAX)
		{
			ObjectBase* bullet = new Bullet(PLAYER_NUM);

			bullet->SetDirection(_game, PLAYER_NUM, m_turn_flag);

			// 弾オブジェクトの開始位置をプレイヤー位置と方向から算出
			if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX < -ANALOG_MIN)
			{
				//左
				bullet->SetPosition(m_x - 180 - bullet->GetWidth() * 2 / 3, m_y - 70 + m_height / 2 - bullet->GetHeight() / 2);
			}
			else if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX > ANALOG_MIN)
			{
				//右
				bullet->SetPosition(m_x + 50 + m_width - bullet->GetWidth() / 3, m_y - 70 + m_height / 2 - bullet->GetHeight() / 2);
			}
			else
			{
				//ニュートラルの場合
				if (m_direction_x == LEFT)
				{
					bullet->SetPosition(m_x - 180 - bullet->GetWidth() * 2 / 3, m_y - 70 + m_height / 2 - bullet->GetHeight() / 2);
				}
				if (m_direction_x == RIGHT)
				{
					bullet->SetPosition(m_x + 50 + m_width - bullet->GetWidth() / 3, m_y - 70 + m_height / 2 - bullet->GetHeight() / 2);
				}
			}

			//SHOOT画像を切り替え
			// 右は左を反転するので書いていない
			if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX == 0 &&
				_game.m_xinput_state[PLAYER_NUM - 1].ThumbLY / THUMB_MAX > ANALOG_MIN)//上
			{
				m_graph = m_shoot_up_graph[m_frame_count / 2 % 5];
			}
			else if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX == 0 &&
				_game.m_xinput_state[PLAYER_NUM - 1].ThumbLY / THUMB_MAX < -ANALOG_MIN)//下
			{
				m_graph = m_shoot_downleft_graph[m_frame_count / 2 % 5];
			}
			else if (m_move_flag && _game.m_xinput_state[PLAYER_NUM - 1].ThumbLY / THUMB_MAX > ANALOG_MIN)//左上
			{
				m_graph = m_shoot_upleft_graph[m_frame_count / 2 % 5];
			}
			else if (m_move_flag && _game.m_xinput_state[PLAYER_NUM - 1].ThumbLY / THUMB_MAX < -ANALOG_MIN)//左下
			{
				m_graph = m_shoot_downleft_graph[m_frame_count / 2 % 5];
			}
			else if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX == 0 || m_move_flag)//左
			{
				m_graph = m_shoot_graph[m_frame_count / 2 % 5];
			}
			else if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX != 0 &&
				_game.m_xinput_state[PLAYER_NUM - 1].ThumbLY / THUMB_MAX > ANALOG_MIN)//走りながら左上
			{
				m_graph = m_dashshoot_upleft_graph[m_frame_count / 2 % 20];
			}
			else if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX != 0 &&
				_game.m_xinput_state[PLAYER_NUM - 1].ThumbLY / THUMB_MAX < -ANALOG_MIN)//走りながら左下
			{
				m_graph = m_dashshoot_downleft_graph[m_frame_count / 2 % 20];
			}
			else if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX != 0)//走りながら左
			{
				m_graph = m_dashshoot_graph[m_frame_count / 2 % 20];
			}

			//1秒に5回弾を発射
			if (m_bullet_frame_count % 10 == 0 || m_bullet_frame_count == 1)
			{
				PlaySE("resource/se/bullet.wav", _game);
				m_se.RandomPitch(0.1f);

				_game.m_objectserver.Add(bullet);
			}
			else
			{
				delete bullet;
			}
		}
	}
	else
	{
		//ボタンが離されたら弾発射フレームのカウンタを初期化し、移動制限の解除
		m_bullet_frame_count = 0;
		m_move_flag = false;
	}
}