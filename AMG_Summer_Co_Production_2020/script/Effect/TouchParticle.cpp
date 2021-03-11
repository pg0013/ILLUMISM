/**
 * @file	AMG_Summer_Co_Production_2020\script\TouchParticle.cpp.
 *
 * @brief	タッチでポイントを獲得したことを表示するエフェクト
 */

#include "TouchParticle.h"
#include"../Server/ResourceServer.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

TouchParticle::TouchParticle(const char* _filename, double x, double y, double vx, double vy, int cnt)
{
	m_graph = ResourceServer::LoadGraph(_filename);
	m_width = 100;
	m_height = 100;
	_x = x;
	_y = y;
	_vx = vx;
	_vy = vy;
	_cnt = cnt;
	_sizeratio = cnt;

	_red = 0;
	_green = 0;
	_blue = 0;
}

TouchParticle::~TouchParticle()
{
}

void TouchParticle::Process(Game& _game)
{
	_x += _vx;
	_y += _vy;

	_cnt--;
	if (_cnt <= 0)
		_game.m_objectserver.Delete(this);
}

void TouchParticle::Draw(Game& _game)
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	SetDrawBright(_red, _green, _blue);

	//徐々に小さくなるように描画
	DrawRotaGraph(static_cast<int>(_x - m_width / 2), static_cast<int>(_y - m_height / 2), 1.0 * _cnt / _sizeratio, 0, m_graph, TRUE);

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}