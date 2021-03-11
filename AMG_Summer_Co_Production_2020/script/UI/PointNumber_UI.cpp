/**
 * @file	AMG_Summer_Co_Production_2020\script\PointNumber_UI.cpp.
 *
 * @brief	プレイヤー所持ポイントを表示するクラス
 */

#include "PointNumber_UI.h"
#include"../Server/ResourceServer.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

PointNumber_UI::PointNumber_UI()
{
	Init();
}

PointNumber_UI::~PointNumber_UI()
{
}

void PointNumber_UI::Init()
{
	ResourceServer::LoadDivGraph("resource/ingameUI/number_magenta.png", 10, 10, 1, 66, 79, m_thousand_graph);
	ResourceServer::LoadDivGraph("resource/ingameUI/number_red.png", 10, 10, 1, 66, 79, m_hundred_graph);
	ResourceServer::LoadDivGraph("resource/ingameUI/number_orange.png", 10, 10, 1, 66, 79, m_ten_graph);
	ResourceServer::LoadDivGraph("resource/ingameUI/number_yellow.png", 10, 10, 1, 66, 79, m_one_graph);

	m_width = 66;
	m_height = 79;

	m_x = 540;
	m_y = GROUND;
}

void PointNumber_UI::Process(Game& _game)
{
	ObjectBase::Process(_game);

	SetPointRank();
}

void PointNumber_UI::SetPointRank()
{
	for (int i = 0; i < 2; i++)
	{
		//4桁目を表示する必要があるか評価
		if (m_point[i] < 1000)
			more_than_1000[i] = false;
		else
			more_than_1000[i] = true;

		thousand_rank[i] = m_point[i] / 1000;
		m_point[i] -= thousand_rank[i] * 1000;

		//3桁目を表示する必要があるか評価
		if (m_point[i] < 100 && more_than_1000[i] == false)
			more_than_100[i] = false;
		else
			more_than_100[i] = true;

		hundred_rank[i] = m_point[i] / 100;
		m_point[i] -= hundred_rank[i] * 100;

		//2桁目を表示する必要が評価
		if (m_point[i] < 10 && more_than_100[i] == false)
			more_than_10[i] = false;
		else
			more_than_10[i] = true;

		ten_rank[i] = m_point[i] / 10;
		m_point[i] -= ten_rank[i] * 10;

		one_rank[i] = m_point[i] / 1;
	}
}

void PointNumber_UI::Draw(Game& _game)
{
	m_y = GROUND + 10;

	//プレイヤー1の所持ポイントを表示
	m_x = SCREEN_WIDTH / 4 - m_width / 2;
	if (more_than_1000[0])
		DrawGraph(m_x + static_cast<int>(m_width * 0.75), m_y, m_thousand_graph[thousand_rank[0]], TRUE);
	if (more_than_100[0])
		DrawGraph(m_x + static_cast<int>(m_width * 1.5), m_y, m_hundred_graph[hundred_rank[0]], TRUE);
	if (more_than_10[0])
		DrawGraph(m_x + static_cast<int>(m_width * 2.25), m_y, m_ten_graph[ten_rank[0]], TRUE);

	DrawGraph(m_x + m_width * 3, m_y, m_one_graph[one_rank[0]], TRUE);

	//プレイヤー2の所持ポイントを表示
	m_x = SCREEN_WIDTH * 3 / 4 - m_width / 2;
	if (more_than_1000[1])
		DrawGraph(m_x + static_cast<int>(m_width * 0.75), m_y, m_thousand_graph[thousand_rank[1]], TRUE);
	if (more_than_100[1])
		DrawGraph(m_x + static_cast<int>(m_width * 1.5), m_y, m_hundred_graph[hundred_rank[1]], TRUE);
	if (more_than_10[1])
		DrawGraph(m_x + static_cast<int>(m_width * 2.25), m_y, m_ten_graph[ten_rank[1]], TRUE);

	DrawGraph(m_x + m_width * 3, m_y, m_one_graph[one_rank[1]], TRUE);
}

void PointNumber_UI::SetPoint(const int _player_num, const int _point)
{
	m_point[_player_num - 1] = _point;
}