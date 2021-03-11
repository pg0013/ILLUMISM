/**
 * @file	AMG_Summer_Co_Production_2020\script\GroundParticle.cpp.
 *
 * @brief	ボスの棘が地面から突き出す攻撃のcation表示エフェクト
 */

#include"GroundParticle.h"
#include"../Server/ResourceServer.h"
#include"../Game.h"
#include"../Mode/ModeGame.h"
#include"DxLib.h"
using namespace illumism;

GroundParticle::GroundParticle(const char* _filename, double x, double y, double vx, double vy, int cnt)
{
	m_graph = ResourceServer::LoadGraph(_filename);
	GetGraphSize(m_graph, &m_width, &m_height);

	_x = x;
	_y = y;
	_vx = vx;
	_vy = vy;
	_cnt = cnt;
}

GroundParticle::~GroundParticle()
{
}

void GroundParticle::Process(Game& _game)
{
	_x += 0.1 * _vx;
	_y += 0.1 * _vy;

	_cnt--;
	if (_cnt <= 0)
		_game.m_objectserver.Delete(this);
}

void GroundParticle::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = static_cast<int>(_x - modeGame->m_camera.GetScreenX());

	SetDrawBlendMode(DX_BLENDMODE_ADD, static_cast<int>(25.5 * _cnt));
	DrawRotaGraph(x - m_width / 2, static_cast<int>(_y - m_height / 2), 1, 0, m_graph, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}