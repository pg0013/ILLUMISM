/**
 * @file	AMG_Summer_Co_Production_2020\script\CoopMoveObject.cpp.
 *
 * @brief	アピールを同時に行うと現れる協力技クラス
 */

#include "CoopMoveObject.h"
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

CoopMoveObject::CoopMoveObject()
{
	m_graph = ResourceServer::LoadGraph("resource/object/coopmove.png");
	GetGraphSize(m_graph, &m_width, &m_height);
	Init();
}

CoopMoveObject::~CoopMoveObject()
{
}

void CoopMoveObject::Init()
{
	m_x = SCREEN_WIDTH * 1 / 2 - m_width / 2;
	m_y = -GROUND + 50;

	m_direction_x = RIGHT;
	m_hit_x = 0;
	m_hit_y = 0;
	m_hit_w = m_width;
	m_hit_h = m_height;
}

void CoopMoveObject::Process(Game& _game)
{
	ObjectBase::Process(_game);

	//一定の時間が経過すると削除
	if (m_frame_count >= 80)
		Damage(_game);
}

void CoopMoveObject::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	SetDrawBlendMode(DX_BLENDMODE_ADD, 175);
	DrawGraph(x, m_y, m_graph, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void CoopMoveObject::Damage(Game& _game)
{
	_game.m_objectserver.Delete(this);
}