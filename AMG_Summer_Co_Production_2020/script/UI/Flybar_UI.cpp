/**
 * @file	AMG_Summer_Co_Production_2020\script\Flybar_UI.cpp.
 *
 * @brief	飛行可能時間を表示するUIクラス
 */

#include "Flybar_UI.h"
#include"../Server/ResourceServer.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

Flybar_UI::Flybar_UI()
{
	Init();
}

Flybar_UI::~Flybar_UI()
{
}

void Flybar_UI::Init()
{
	m_graph_up = ResourceServer::LoadGraph("resource/ingameUI/UI_FLY_2.png");
	GetGraphSize(m_graph_up, &m_width, &m_height);
	m_y = GROUND + 116;
}

void Flybar_UI::Process(Game& _game)
{
	ObjectBase::Process(_game);
}

void Flybar_UI::Draw(Game& _game)
{
	//プレイヤー１のUIを描画
	m_x = SCREEN_WIDTH / 4 - m_width / 2 + 50;
	DrawRectGraph(m_x, m_y, 0, 0,
		m_width - static_cast<int>(6.7 * m_flytime[0]), m_height,
		m_graph_up, TRUE, FALSE);

	//プレイヤー２のUIを描画
	m_x = SCREEN_WIDTH * 3 / 4 - m_width / 2 + 50;
	DrawRectGraph(m_x, m_y, 0, 0,
		m_width - static_cast<int>(6.7 * m_flytime[1]), m_height,
		m_graph_up, TRUE, FALSE);
}

void Flybar_UI::SetFlyTime(const int _player_num, int _time)
{
	m_flytime[_player_num - 1] = _time;
}