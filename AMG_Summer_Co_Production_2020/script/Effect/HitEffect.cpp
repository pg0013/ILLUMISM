/**
 * @file    HitEffect.cpp
 * @brief  ヒットエフェクト用パーティクル
 *
 * @author Takuya Fujisawa
 * @date   2020/11/05
 */

#include"HitEffect.h"
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

HitEffect::HitEffect(int _x, int _y, int _cnt)
{
	ResourceServer::LoadDivGraph("resource/player/hiteffect.png", 8, 8, 1, 120, 120, m_hiteffect_graph);
	m_x = _x;
	m_y = _y;
	m_frame_count = _cnt;
	m_all_count = _cnt;
}

HitEffect::~HitEffect(){}

void HitEffect::Process(Game& _game)
{
	m_frame_count--;
	if (m_frame_count <= 0)
		_game.m_objectserver.Delete(this);
}

void HitEffect::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	SetDrawBlendMode(DX_BLENDMODE_ADD, 180 * (m_all_count - m_frame_count));
	DrawRotaGraph(x , m_y , 1.0, 0, m_hiteffect_graph[(m_all_count - m_frame_count) / 2 % 8], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void HitEffect::SetPositionOffset(int _charactor_type, int _direction)
{
	switch (_charactor_type)
	{
	case NARI1:
	case NARI2:
		if (_direction == LEFT)
			m_x += NARI_OFFSET_LEFT;
		else if (_direction == RIGHT)
			m_x += NARI_OFFSET_RIGHT;
		break;
	case NONAME1:
	case NONAME2:
		if (_direction == LEFT)
			m_x += NONAME_OFFSET_LEFT;
		else if (_direction == RIGHT)
			m_x += NONAME_OFFSET_RIGHT;
		break;
	}
}