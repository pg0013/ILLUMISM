/**
 * @file	AMG_Summer_Co_Production_2020\script\SPmove_UI.cpp.
 *
 * @brief	�K�E�Z�Q�[�W��UI��\������N���X
 */

#include "SPmove_UI.h"
#include"../Server/ResourceServer.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

SPmove_UI::SPmove_UI()
{
	Init();
}

SPmove_UI::~SPmove_UI()
{
}

void SPmove_UI::Init()
{
	m_graph = ResourceServer::LoadGraph("resource/ingameUI/UI_SP_2.png");
	m_graph_aura = ResourceServer::LoadGraph("resource/ingameUI/UI_3_d.png");
	GetGraphSize(m_graph, &m_width, &m_height);
	m_y = GROUND + 37;
}

void SPmove_UI::Process(Game& _game)
{
	ObjectBase::Process(_game);
}

void SPmove_UI::Draw(Game& _game)
{
	//�v���C���[1��UI��`��
	m_x = SCREEN_WIDTH / 4 - m_width / 2 - 150;
	DrawCircleGauge(m_x + m_width / 2, m_y + m_height / 2, 0.85 * (m_mp[0]) - 10.0, m_graph, -10.0, 1.0, TRUE, TRUE);

	//�v���C���[2��UI��`��
	m_x = SCREEN_WIDTH * 3 / 4 - m_width / 2 - 150;
	DrawCircleGauge(m_x + m_width / 2, m_y + m_height / 2, 0.85 * (m_mp[1]) - 10.0, m_graph, -10.0, 1.0, TRUE, TRUE);

}

void SPmove_UI::SetMP(const int _player_num, const int _mp)
{
	m_mp[_player_num - 1] = _mp;
}

void SPmove_UI::DrawAura()
{
	//�v���C���[1��UI��`��
	if (m_mp[0] == 100)
	{
		m_x = SCREEN_WIDTH / 4 - m_width / 2 - 155;

		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		DrawGraph(m_x - 30, m_y - 45, m_graph_aura, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	//�v���C���[2��UI��`��
	if (m_mp[1] == 100)
	{
		m_x = SCREEN_WIDTH * 3 / 4 - m_width / 2 - 150;

		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		DrawGraph(m_x - 30, m_y - 45, m_graph_aura, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}