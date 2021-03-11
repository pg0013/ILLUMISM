/**
 * @file	AMG_Summer_Co_Production_2020\script\CrossLaser.cpp.
 *
 * @brief	画面端からのレーザー攻撃を行う
 */

#include "CrossLaser.h"
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

CrossLaser::CrossLaser(int _num)
{
	direction = _num;

	Init();
}

CrossLaser::~CrossLaser()
{
}

void CrossLaser::Init()
{
	if (direction == 0)//上から
	{
		m_graph = ResourceServer::LoadGraph("resource/object/crosslaser_horizon.png");
		GetGraphSize(m_graph, &m_width, &m_height);
		m_hit_x = 0;
		m_hit_y = 135;
		m_hit_w = 2400;
		m_hit_h = 20;
		m_x = -240;
		m_y = -m_height / 2 + m_hit_h;
	}
	if (direction == 1)//下から
	{
		m_graph = ResourceServer::LoadGraph("resource/object/crosslaser_horizon.png");
		GetGraphSize(m_graph, &m_width, &m_height);
		m_hit_x = 0;
		m_hit_y = 135;
		m_hit_w = 2400;
		m_hit_h = 20;
		m_x = -240;
		m_y = GROUND - m_height / 2 + 2 * m_hit_h;
	}
	if (direction == 2)//左から
	{
		m_graph = ResourceServer::LoadGraph("resource/object/crosslaser_vertical.png");
		GetGraphSize(m_graph, &m_width, &m_height);
		m_hit_x = 145;
		m_hit_y = 60;
		m_hit_w = 20;
		m_hit_h = 1940;
		m_x = -m_width + m_hit_x + m_hit_w;
		m_y = -m_hit_y;
	}
	if (direction == 3)//右から
	{
		m_graph = ResourceServer::LoadGraph("resource/object/crosslaser_vertical.png");
		GetGraphSize(m_graph, &m_width, &m_height);
		m_hit_x = 145;
		m_hit_y = 60;
		m_hit_w = 20;
		m_hit_h = 1940;
		m_x = SCREEN_WIDTH - m_hit_x - m_hit_w;
		m_y = -m_hit_y;
	}
}

void CrossLaser::Process(Game& _game)
{
	ObjectBase::Process(_game);

	//すぐに動かない
	if (m_frame_count < 30)
		return;

	if (direction == 0)//上から
		m_y += m_speed;
	if (direction == 1)//下から
		m_y -= m_speed;
	if (direction == 2)//左から
		m_x += m_speed;
	if (direction == 3)//右から
		m_x -= m_speed;

	Damage(_game);
}

void CrossLaser::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
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

void CrossLaser::Damage(Game& _game)
{
	//画面上
	if (m_y < -m_height / 2 + m_hit_h && direction == 1)
		_game.m_objectserver.Delete(this);
	//画面下
	if (m_y > GROUND - m_height / 2 + 2 * m_hit_h && direction == 0)
		_game.m_objectserver.Delete(this);
	//画面左
	if (m_x < -m_width + m_hit_x + m_hit_w - 240 && direction == 3)
		_game.m_objectserver.Delete(this);
	//画面右
	if (m_x > SCREEN_WIDTH - m_hit_x - m_hit_w + 240 && direction == 2)
		_game.m_objectserver.Delete(this);
}