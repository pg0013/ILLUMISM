/**
 * @file	AMG_Summer_Co_Production_2020\script\Particle.cpp.
 *
 * @brief	エフェクト用パーティクル
 */

#include "Particle.h"
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

Particle::Particle(const char* _filename, double x, double y, double vx, double vy, int cnt)
{
	ResourceServer::LoadDivGraph(_filename, 2, 2, 1, 100, 100, m_graph);
	m_width = 100;
	m_height = 100;

	_x = x;
	_y = y;
	_vx = vx;
	_vy = vy;
	_cnt = cnt;
	_sizeratio = cnt;

	//虹色に変化させるためにSetBrightでRGBを指定
	_red = 0;
	_green = 0;
	_blue = 0;
}

Particle::~Particle()
{
}

void Particle::Process(Game& _game)
{
	_x += 6 * _vx;
	_y += 2 * _vy;

	_cnt--;
	if (_cnt <= 0)
		_game.m_objectserver.Delete(this);
}

void Particle::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = static_cast<int>(_x - modeGame->m_camera.GetScreenX());

	SetDrawBlendMode(DX_BLENDMODE_ADD, static_cast<int>(25.5 * _cnt));
	SetDrawBright(_red, _green, _blue);

	//徐々に小さくなるように描画
	DrawRotaGraph(x - m_width / 2, static_cast<int>(_y - m_height / 2), 0.5 * _cnt / _sizeratio, 0, m_graph[_cnt / 5 % 2], TRUE);

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}