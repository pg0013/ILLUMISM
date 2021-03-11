/**
 * @file	AMG_Summer_Co_Production_2020\script\Combo.cpp.
 *
 * @brief	タッチオブジェクトのコンボを表示
 */

#include "Combo.h"
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

Combo::Combo(const int _player_num, const int _combo)
{
	m_combo = _combo;
	if (m_combo > 99) { m_combo = 99; }

	if (_player_num == 1)
	{
		ResourceServer::LoadDivGraph("resource/ingameUI/number_combo_01.png", 10, 10, 1, 72, 87, m_number_graph);
		m_combo_graph = ResourceServer::LoadGraph("resource/ingameUI/combo1.png");
	}
	if (_player_num == 2)
	{
		ResourceServer::LoadDivGraph("resource/ingameUI/number_combo_02.png", 10, 10, 1, 72, 87, m_number_graph);
		m_combo_graph = ResourceServer::LoadGraph("resource/ingameUI/combo2.png");
	}
	GetGraphSize(m_number_graph[0], &m_width, &m_height);

	Init();
}

Combo::~Combo()
{
}

void Combo::Init()
{
	m_count = 110;
	SetCombo();
}

void Combo::SetCombo()
{
	tenrank = m_combo / 10;
	onerank = m_combo % 10;
}

void Combo::Process(Game& _game)
{
	m_count--;
	if (m_count < 0)
		_game.m_objectserver.Delete(this);
}

void Combo::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(5 * m_count));

	//1桁と2桁で表示位置を調整
	if (m_combo > 0 && m_combo < 10)
	{
		DrawGraph(x + 35, m_y - 50, m_number_graph[onerank], TRUE);
		DrawGraph(x, m_y + 50, m_combo_graph, TRUE);
	}
	if (m_combo >= 10)
	{
		DrawGraph(x + 10, m_y - 50, m_number_graph[tenrank], TRUE);
		DrawGraph(x + m_width, m_y - 50, m_number_graph[onerank], TRUE);
		DrawGraph(x, m_y + 50, m_combo_graph, TRUE);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}