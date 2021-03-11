/**
 * @file	AMG_Summer_Co_Production_2020\script\Bullet.cpp.
 *
 * @brief	プレイヤーが発射する弾丸オブジェクトのクラス
 */

#include "Bullet.h"
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"DxLib.h"
using namespace illumism;

Bullet::Bullet(int _num)
{
	//各プレイヤーで色違いの画像を読み込み
	if (_num == 1)
		m_graph = ResourceServer::LoadGraph("resource/object/bullet_player1.png");
	if (_num == 2)
		m_graph = ResourceServer::LoadGraph("resource/object/bullet_player2.png");
	m_player_num = _num;
	Init();
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	m_width = 100;
	m_height = 84;
	m_speed = BULLET_SPEED;
	m_direction_x = 0;
	m_direction_y = 0;
}

void Bullet::Process(Game& _game)
{
	ObjectBase::Process(_game);

	//斜め方向でも速度を一定にする
	if (m_direction_x != 0 && m_direction_y != 0)
		m_speed = BULLET_SPEED / static_cast<int>(sqrt(2));
	else
		m_speed = BULLET_SPEED;

	//弾を移動
	m_x += m_speed * m_direction_x;
	m_y += m_speed * m_direction_y;


	//画面外に出たら削除
	if (m_x < 0 || m_x + m_width > SCREEN_WIDTH ||
		m_y < 0 || m_y + m_height > GROUND)
	{
		_game.m_objectserver.Delete(this);
	}

	Hit(_game);
}

//毎フレーム呼ばれる描画処理
void Bullet::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	//8方向に向けるための回転、反転、描画処理
	if (m_direction_x == RIGHT && m_direction_y == UP)
	{
		//右上
		DrawRotaGraph3(x - 35, m_y + m_height / 2 - 80, 0, m_height / 2, 1.0f, 1.0f,
			DX_PI_F * 7 / 4, m_graph, TRUE, FALSE);
	}
	else if (m_direction_x == LEFT && m_direction_y == UP)
	{
		//左上
		DrawRotaGraph3(x + 35 + m_width, m_y + m_height / 2 - 80, m_width, m_height / 2, 1.0f, 1.0f,
			DX_PI_F * 1 / 4, m_graph, TRUE, TRUE);
	}
	else if (m_direction_x == RIGHT && m_direction_y == DOWN)
	{
		//右下
		DrawRotaGraph3(x - 35, m_y + m_height / 2 + 80, 0, m_height / 2, 1.0f, 1.0f,
			DX_PI_F * 1 / 4, m_graph, TRUE, FALSE);
	}
	else if (m_direction_x == LEFT && m_direction_y == DOWN)
	{
		//左下
		DrawRotaGraph3(x + 35 + m_width, m_y + m_height / 2 + 80, m_width, m_height / 2, 1.0f, 1.0f,
			DX_PI_F * 7 / 4, m_graph, TRUE, TRUE);
	}
	else if (m_direction_x == LEFT)
	{
		//左
		DrawRotaGraph3(x, m_y + 5, 0, 0, 1.0f, 1.0f,
			0, m_graph, TRUE, TRUE);
	}
	else if (m_direction_x == RIGHT)
	{
		//右
		DrawRotaGraph3(x, m_y + 5, 0, 0, 1.0f, 1.0f,
			0, m_graph, TRUE, FALSE);
	}
	else if (m_direction_y == UP)
	{
		if (m_turn_flag == true)
		{
			//上向きながら左
			DrawRotaGraph3(x + 195, m_y + m_height - 170, 0, 0, 1.0f, 1.0f,
				DX_PI_F * 3 / 2, m_graph, TRUE, FALSE);
		}
		else
		{
			//上向きながら右
			DrawRotaGraph3(x - 165, m_y + m_height - 170, 0, 0, 1.0f, 1.0f,
				DX_PI_F * 3 / 2, m_graph, TRUE, FALSE);
		}
	}
	else if (m_direction_y == DOWN)
	{
		if (m_turn_flag == true)
		{
			//下向きながら左
			DrawRotaGraph3(x + 35 + m_width, m_y + m_height / 2 + 80, m_width, m_height / 2, 1.0f, 1.0f,
				DX_PI_F * 7 / 4, m_graph, TRUE, TRUE);
		}
		else
		{
			//下向きながら右
			DrawRotaGraph3(x - 35, m_y + m_height / 2 + 80, 0, m_height / 2, 1.0f, 1.0f,
				DX_PI_F * 1 / 4, m_graph, TRUE, FALSE);
		}
	}

#ifdef _DEBUG
	if (m_ishit_flag)
	{
		//開発用当たり判定表示
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//描画モードを半透明描画にセット
		//体の当たり判定
		DrawBox(x + m_hit_x, m_y + m_hit_y,
			x + m_hit_x + m_hit_w, m_y + m_hit_y + m_hit_h,
			GetColor(255, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//不透明描画に戻す
	}
#endif // _DEBUG
}

void Bullet::Hit(Game& _game)
{
	for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
	{
		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::BULLET)
		{
			//自分自身と当たっているを除外
			if ((*iter) == this) { continue; }

			if (IsHit(*(*iter)) == true)
			{
				//弾のダメージ処理
				Damage(_game);
				(*iter)->Damage(_game);
			}
		}
	}
}

void Bullet::SetDirection(Game& _game, int _num, bool _turn_flag)
{
	if (_game.m_xinput_state[_num - 1].ThumbLY / THUMB_MAX > ANALOG_MIN)//上
	{
		m_direction_y = UP;
		m_turn_flag = _turn_flag;
		if (m_turn_flag == true)//左
		{
			m_hit_x = 33 + 195;
			m_hit_y = -(m_width - m_height - 10) - 170;
		}
		else
		{
			m_hit_x = 33 - 165;
			m_hit_y = -(m_width - m_height - 10) - 170;
		}
		m_hit_w = 15;
		m_hit_h = 20;
	}
	else if (_game.m_xinput_state[_num - 1].ThumbLY / THUMB_MAX < -ANALOG_MIN)//下
	{
		m_direction_y = DOWN;
		if (_turn_flag == true)
		{
			m_direction_x = LEFT;
			m_hit_x = m_width / 2 - 15 + 35;
			m_hit_y = m_height + 5 + 80;
		}
		else
		{
			m_direction_x = RIGHT;
			m_hit_x = m_width / 2 - 35;
			m_hit_y = m_height + 5 + 80;
		}
		m_hit_w = 15;
		m_hit_h = 20;
	}
	if (_game.m_xinput_state[_num - 1].ThumbLX / THUMB_MAX < -ANALOG_MIN)//左
	{
		m_direction_x = LEFT;
		m_turn_flag = _turn_flag;

		m_hit_x = 11;
		m_hit_y = 33 + 5;
		m_hit_w = 20;
		m_hit_h = 15;
	}
	else if (_game.m_xinput_state[_num - 1].ThumbLX / THUMB_MAX > ANALOG_MIN)//右
	{
		m_direction_x = RIGHT;
		m_turn_flag = _turn_flag;

		m_hit_x = 68;
		m_hit_y = 33 + 5;
		m_hit_w = 20;
		m_hit_h = 15;
	}

	//ニュートラル状態の時は画像の向きに合わせて弾の向きを決める
	if (_game.m_xinput_state[_num - 1].ThumbLX / THUMB_MAX == 0 &&
		_game.m_xinput_state[_num - 1].ThumbLY / THUMB_MAX == 0)
	{
		if (_turn_flag == true)//ニュートラル左
		{
			m_direction_x = LEFT;
			m_turn_flag = _turn_flag;

			m_hit_x = 11;
			m_hit_y = 33 + 5;
			m_hit_w = 20;
			m_hit_h = 15;
		}
		else//ニュートラル右
		{
			m_direction_x = RIGHT;
			m_turn_flag = _turn_flag;

			m_hit_x = 68;
			m_hit_y = 33 + 5;
			m_hit_w = 20;
			m_hit_h = 15;
		}
	}

	if (m_direction_x == RIGHT && m_direction_y == UP)//右上
	{
		m_hit_x = m_width / 2 - 3 - 35;
		m_hit_y = -m_height / 2 + 18 - 80;
		m_hit_w = 15;
		m_hit_h = 15;
	}
	else if (m_direction_x == LEFT && m_direction_y == UP)//左上
	{
		m_hit_x = m_width / 2 - 13 + 35;
		m_hit_y = -m_height / 2 + 18 - 80;
		m_hit_w = 15;
		m_hit_h = 15;
	}
	else if (m_direction_x == RIGHT && m_direction_y == DOWN)//右下
	{
		m_hit_x = m_width / 2 - 35;
		m_hit_y = m_height + 5 + 80;
		m_hit_w = 15;
		m_hit_h = 15;
	}
	else if (m_direction_x == LEFT && m_direction_y == DOWN)//左下
	{
		m_hit_x = m_width / 2 - 15 + 35;
		m_hit_y = m_height + 5 + 80;
		m_hit_w = 15;
		m_hit_h = 15;
	}
}

void Bullet::Damage(Game& _game)
{
	_game.m_objectserver.Delete(this);
}