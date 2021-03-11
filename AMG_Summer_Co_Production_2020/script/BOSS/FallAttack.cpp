/**
 * @file	AMG_Summer_Co_Production_2020\script\FallAttack.cpp.
 *
 * @brief	画面上から落ちてくる攻撃処理
 */

#include "FallAttack.h"
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"DxLib.h"
using namespace illumism;

FallAttack::FallAttack(int _num)
{
	//3種類の画像から選ぶ
	if (_num == 0)
	{
		m_graph = ResourceServer::LoadGraph("resource/object/fall_purple.png");
	}
	else if (_num == 1)
	{
		m_graph = ResourceServer::LoadGraph("resource/object/fall_green.png");
	}
	else
	{
		m_graph = ResourceServer::LoadGraph("resource/object/fall_blue.png");
	}
	Init();
}

FallAttack::~FallAttack()
{
}

void FallAttack::Init()
{
	m_width = BODY_W / 2;
	m_height = BODY_H / 2;
	m_hit_x = -m_width / 2 + 20;
	m_hit_y = -m_height / 2 + 20;
	m_hit_w = m_width - 40;
	m_hit_h = m_height - 40;
	m_speed = 8;
}

void FallAttack::Process(Game& _game)
{
	ObjectBase::Process(_game);

	m_y += m_speed;

	if (m_y > GROUND)
		_game.m_objectserver.Delete(this);
}

void FallAttack::Damage(Game& _game)
{
	_game.m_objectserver.Delete(this);
}

void FallAttack::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	DrawRotaGraph(x, m_y, 0.5, DX_PI_F / 180 * (m_frame_count % 360), m_graph, TRUE);

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