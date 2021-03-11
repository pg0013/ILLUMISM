/**
 * @file	AMG_Summer_Co_Production_2020\script\LaserAttack.cpp.
 *
 * @brief	プレイヤーに向かうレーザー攻撃処理
 */

#include "LaserAttack.h"
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"DxLib.h"
using namespace illumism;

LaserAttack::LaserAttack(int _x, int _y, int _target_x, int _target_y, int _speed)
{
	m_x = _x;
	m_y = _y;
	position.x = static_cast<float>(m_x);
	position.y = static_cast<float>(m_y);
	target.x = static_cast<float>(_target_x);
	target.y = static_cast<float>(_target_y);
	m_speed = _speed;
	Init();
}

LaserAttack::~LaserAttack()
{
}

void LaserAttack::Init()
{
	m_graph = ResourceServer::LoadGraph("resource/object/laserattack.png");
	GetGraphSize(m_graph, &m_width, &m_height);

	m_hit_x = 0;
	m_hit_y = 0;
	m_hit_w = m_width;
	m_hit_h = m_height;

	//プレイヤーに対するベクトルを計算
	VECTOR toplayer = VSub(target, position);
	toplayer = VNorm(toplayer);

	//プレイヤーが近すぎて0が返ってきたときに例外処理を行う
	if (toplayer.x == 0.0f && toplayer.y == 0.0f)
	{
		toplayer.x = 0.0f;
		toplayer.y = 1.0f;
	}

	e_x = toplayer.x;
	e_y = toplayer.y;
	toplayer = VScale(toplayer, static_cast<float>(m_speed));

	m_speed_x =toplayer.x;
	m_speed_y = toplayer.y;

	m_angle = static_cast<double>(std::atan2(toplayer.y, toplayer.x));
}

void LaserAttack::Process(Game& _game)
{
	m_x += static_cast<int>(m_speed_x);
	m_y += static_cast<int>(m_speed_y);


	//当たり判定を配置し移動
	for (int i = 0; i < 3; i++)
	{
		hit_r[i] = 10;
		hit_cx[i] = m_x;
		hit_cy[i] = m_y;

		if (i == 1)
		{
			hit_cx[i] = static_cast<int>(m_x + (m_width / 2) * e_x);
			hit_cy[i] = static_cast<int>(m_y + (m_width / 2) * e_y);
		}
		if (i == 2)
		{
			hit_cx[i] = static_cast<int>(m_x - (m_width / 2) * e_x);
			hit_cy[i] = static_cast<int>(m_y - (m_width / 2) * e_y);
		}
	}

	Hit(_game);

	OffScreen(_game);
}

void LaserAttack::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	DrawRotaGraph2(x, m_y, m_width / 2, m_height / 2,
		1.0, m_angle, m_graph, TRUE);

#ifdef _DEBUG
	if (m_ishit_flag)
	{
		//開発用当たり判定表示
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//描画モードを半透明描画にセット
		for (int i = 0; i < 3; i++)
			DrawCircle(hit_cx[i] - modeGame->m_camera.GetScreenX(), hit_cy[i], hit_r[i], GetColor(255, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//不透明描画に戻す
	}
#endif // _DEBUG
}

void LaserAttack::Hit(Game& _game)
{
	//当たり判定
	for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
	{
		//プレイヤーの当たり判定
		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::PLAYER)
		{
			if (IsHitToCircle(*(*iter)) == true)
			{
				(*iter)->AddHP(-10);
				if(m_x < (*iter)->GetPosX() + GetPosHit_x())
					(*iter)->SetDirection(_game, (*iter)->GetPlayerNum(), TRUE);
				else
					(*iter)->SetDirection(_game, (*iter)->GetPlayerNum(), FALSE);
				(*iter)->Damage(_game);
				Damage(_game);
			}
		}
	}
}

bool LaserAttack::IsHitToCircle(ObjectBase& _object)
{
	if (_object.GetHitNoCount() != 0)
		return false;

	if (_object.GetIsHitFlag())
	{
		for (int i = 0; i < 3; i++)
		{
			//円と四角形の当たり判定
			//円の中心が四角形の上下の半径内にいる
			if (hit_cx[i] > _object.GetPosX() + _object.GetPosHit_x() &&
				hit_cx[i] < _object.GetPosX() + _object.GetPosHit_x() + _object.GetPosHit_w() &&
				hit_cy[i] > _object.GetPosY() + _object.GetPosHit_y() - hit_r[i] &&
				hit_cy[i] < _object.GetPosY() + _object.GetPosHit_y() + _object.GetPosHit_h() + hit_r[i])
				return true;

			//円の中心が四角形の左右の半径内にいる
			if (hit_cx[i] > _object.GetPosX() + _object.GetPosHit_x() - hit_r[i] &&
				hit_cx[i] < _object.GetPosX() + _object.GetPosHit_x() + _object.GetPosHit_w() + hit_r[i] &&
				hit_cy[i] > _object.GetPosY() + _object.GetPosHit_y() &&
				hit_cy[i] < _object.GetPosY() + _object.GetPosHit_y() + _object.GetPosHit_h())
				return true;

			//円の中心が四角形の角にいる
			if (pow((_object.GetPosX() + _object.GetPosHit_x() - hit_cx[i]), 2) +
				pow((_object.GetPosY() + _object.GetPosHit_y() - hit_cy[i]), 2) < pow(hit_r[i], 2) ||
				pow((_object.GetPosX() + _object.GetPosHit_x() + _object.GetPosHit_w() - hit_cx[i]), 2) +
				pow((_object.GetPosY() + _object.GetPosHit_y() - hit_cy[i]), 2) < pow(hit_r[i], 2) ||
				pow((_object.GetPosX() + _object.GetPosHit_x() + _object.GetPosHit_w() - hit_cx[i]), 2) +
				pow((_object.GetPosY() + _object.GetPosHit_y() + _object.GetPosHit_h() - hit_cy[i]), 2) < pow(hit_r[i], 2) ||
				pow((_object.GetPosX() + _object.GetPosHit_x() - hit_cx[i]), 2) +
				pow((_object.GetPosY() + _object.GetPosHit_y() + _object.GetPosHit_h() - hit_cy[i]), 2) < pow(hit_r[i], 2))
				return true;
		}

		return false;
	}
	return false;
}

void LaserAttack::Damage(Game& _game)
{
	_game.m_objectserver.Delete(this);
}

void LaserAttack::OffScreen(Game& _game)
{
	//画面外に出たら削除
	if (m_x < 0 || m_x + m_width > SCREEN_WIDTH ||
		m_y < 0 || m_y + m_height > GROUND)
	{
		_game.m_objectserver.Delete(this);
	}
}