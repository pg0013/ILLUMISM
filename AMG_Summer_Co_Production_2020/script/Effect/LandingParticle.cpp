/**
 * @file    LandingParticle.cpp
 * @brief   着地エフェクト用パーティクル
 *
 * @author Takuya Fujisawa
 * @date   2020/10/26
 */

#include "LandingParticle.h"
#include"../Server/ResourceServer.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

LandingParticle::LandingParticle(int _x, int _y, int _cnt)
{
	ResourceServer::LoadDivGraph("resource/player/landing.png", 10, 10, 1, 250, 250, m_landing_graph);
	m_x = _x;
	m_y = _y;
	m_frame_count = _cnt;
	m_all_count = _cnt;
}

LandingParticle::~LandingParticle() {}

void LandingParticle::Process(Game& _game)
{
	m_frame_count--;
	if (m_frame_count <= 0)
		_game.m_objectserver.Delete(this);
}

void LandingParticle::Draw(Game& _game)
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * (m_all_count - m_frame_count));
	DrawRotaGraph(m_x - 60, m_y + 25, 1.0, 0, m_landing_graph[(m_all_count - m_frame_count) / 3 % 10], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}