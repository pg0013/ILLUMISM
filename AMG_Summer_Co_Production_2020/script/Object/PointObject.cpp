/**
 * @file	AMG_Summer_Co_Production_2020\script\PointObject.cpp
 *
 * @brief	プレイヤーがHP<0になった時に放出するポイントオブジェクトのクラス
 */

#include "PointObject.h"
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#define USE_MATH_DEFINES
#include<math.h>
#include<time.h>
#include"DxLib.h"
using namespace illumism;

PointObject::PointObject()
{
	m_graph = ResourceServer::LoadGraph("resource/object/pointobject.png");
	Init();
}

PointObject::~PointObject()
{
}

void PointObject::Init()
{
	m_width = 15;
	m_height = 15;

	m_diffusion_height = 15;
	m_vibration_height = 23;

	m_speed = 10;
	m_falling_speed_x = rand() % 35;
	m_falling_speed_y = 0;

	m_hit_x = 0;							//当たり判定
	m_hit_y = 0;
	m_hit_w = m_width;
	m_hit_h = m_height;

	m_object_state = DIFFUSION;
}

void PointObject::Process(Game& _game)
{
	ObjectBase::Process(_game);

	switch (m_object_state)
	{
	case DIFFUSION:
		Diffusion(_game);
		break;
	case VIBRATION:
		SimpleVibration(_game);
		break;
	}

	OffScreen();

	if (m_frame_count > 60 * 15)
		Damage(_game);
}

void PointObject::Diffusion(Game& _game)
{
	//拡散する高さを乱数で決める
	if (m_frame_count == 1)
		m_falling_speed_y = rand() % m_diffusion_height;

	m_y -= m_falling_speed_y;
	m_falling_speed_y -= 2;

	//左右どちらに拡散するかを決定
	if (m_falling_speed_y % 2 == 0)
		m_x += m_falling_speed_x;
	else
		m_x -= m_falling_speed_x;

	//地面より下に行かない
	if (m_y >= (GROUND - m_height))
	{
		m_y = GROUND - m_height;
		m_falling_speed_x = 0;
		m_object_state = VIBRATION;
	}
}

void PointObject::SimpleVibration(Game& _game)
{
	//落下処理
	m_y -= m_falling_speed_y;
	m_falling_speed_y -= 1;

	//最初は地面からジャンプ
	if (m_y >= (GROUND - m_height))
		m_falling_speed_y = m_vibration_height;

	//2回目以降は空中を単振動
	if (m_y >= (GROUND - 2 * m_height))
		m_falling_speed_y = m_vibration_height;

	ApproachToPlayer(_game);
}

void PointObject::ApproachToPlayer(Game& _game)
{
	for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
	{
		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::PLAYER)
		{
			//左にいるプレイヤーに近づく
			if (m_x - (*iter)->GetPosX() - 25 < 100 &&
				m_x - (*iter)->GetPosX() > 0)
			{
				m_x -= 13;

				if (m_y < (*iter)->GetPosY() + 50)
					m_y += 13;
				else
					m_y -= 13;
			}
			//右にいるプレイヤーに近づく
			if ((*iter)->GetPosX() - m_x < 100 &&
				(*iter)->GetPosX() - m_x > 0)
			{
				m_x += 13;

				if (m_y < (*iter)->GetPosY() + 50)
					m_y += 13;
				else
					m_y -= 13;
			}
		}
	}
}

void PointObject::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	if (m_turn_flag == true)
		DrawTurnGraph(x, m_y, m_graph, TRUE);
	else
		DrawGraph(x, m_y, m_graph, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

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

void PointObject::Damage(Game& _game)
{
	_game.m_objectserver.Delete(this);
}

void PointObject::OffScreen()
{
	if (m_x < STAGE_WIDTH_LEFT) { m_x = STAGE_WIDTH_LEFT + m_width; }
	if (m_x + m_width > STAGE_WIDTH_RIGHT) { m_x = STAGE_WIDTH_RIGHT - m_width; }
	if (m_y < 0) { m_y = 0; }
	if (m_y + m_height > GROUND) { m_y = GROUND - m_height; }
}