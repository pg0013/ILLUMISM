/**
 * @file	AMG_Summer_Co_Production_2020\script\HPbar_UI.cpp.
 *
 * @brief	プレイヤーのHPを表示するクラス
 */

#include "HPbar_UI.h"
#include"../Server/ResourceServer.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

HPbar_UI::HPbar_UI()
{
	Init();
}

HPbar_UI::~HPbar_UI()
{
}

void HPbar_UI::Init()
{
	m_graph_up = ResourceServer::LoadGraph("resource/ingameUI/UI_HP_2.png");
	GetGraphSize(m_graph_up, &m_width, &m_height);
	m_y = GROUND + 90;
}

void HPbar_UI::Process(Game& _game)
{
	ObjectBase::Process(_game);
}

void HPbar_UI::Draw(Game& _game)
{
	//プレイヤー１のUIを描画
	m_x = SCREEN_WIDTH / 4 - m_width / 2 + 60;
	DrawRectGraph(m_x, m_y, 0, 0,
		m_width - static_cast<int>(2.88 * (100 - m_hp[0])), m_height,
		m_graph_up, TRUE, FALSE);

	//プレイヤー２のUIの描画
	m_x = SCREEN_WIDTH * 3 / 4 - m_width / 2 + 60;
	DrawRectGraph(m_x, m_y, 0, 0,
		m_width - static_cast<int>(2.88 * (100 - m_hp[1])), m_height,
		m_graph_up, TRUE, FALSE);
}

void HPbar_UI::SetHP(const int _player_num, const int _hp)
{
	m_hp[_player_num - 1] = _hp;
}