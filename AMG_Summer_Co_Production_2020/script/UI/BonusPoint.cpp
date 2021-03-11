/**
 * @file	AMG_Summer_Co_Production_2020\script\BonusPoint.cpp.
 *
 * @brief	スコアボーナスモードでボーナスポイントを描画する
 */

#include "BonusPoint.h"
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

BonusPoint::BonusPoint()
{
	m_graph = 0;
	_x = 0;
	_y = 0;
	_vx = 0;
	_vy = 0;
	_cnt = 0;
}


BonusPoint::~BonusPoint()
{
}

void BonusPoint::SetParam(const char* _filename, double x, double y, double vx, double vy, int cnt)
{
	m_graph = ResourceServer::LoadGraph(_filename);

	_x = x;
	_y = y;
	_vx = vx;
	_vy = vy;
	_cnt = cnt;
}

void BonusPoint::Process(Game& _game)
{
	_x += 0.1 * _vx;
	_y -= 0.1 * _vy;

	_cnt--;

	if (_cnt <= 0)
		_cnt = 0;
}

void BonusPoint::Draw(Game& _game)
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, static_cast<int>(25.5 * _cnt));

	int width, height;
	GetGraphSize(m_graph, &width, &height);
	DrawRotaGraph(static_cast<int>(_x) , static_cast<int>(_y - height / 2 -120), 1, 0, m_graph, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}