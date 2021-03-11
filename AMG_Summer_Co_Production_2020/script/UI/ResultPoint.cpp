/**
 * @file	AMG_Summer_Co_Production_2020\script\ResultPoint.cpp.
 *
 * @brief	リザルト画面でポイントを表示
 */

#include "ResultPoint.h"
#include"../Server/ResourceServer.h"
#include"../Game.h"
#include"../Mode/ModeResult.h"
#include"DxLib.h"
using namespace illumism;

ResultPoint::ResultPoint()
{
	ResourceServer::LoadDivGraph("resource/ingameUI/number_magenta.png", 10, 10, 1, 66, 79, m_thousand_graph);
	ResourceServer::LoadDivGraph("resource/ingameUI/number_red.png", 10, 10, 1, 66, 79, m_hundred_graph);
	ResourceServer::LoadDivGraph("resource/ingameUI/number_orange.png", 10, 10, 1, 66, 79, m_ten_graph);
	ResourceServer::LoadDivGraph("resource/ingameUI/number_yellow.png", 10, 10, 1, 66, 79, m_one_graph);

	m_width = 66;
	m_height = 79;

	//イージングのパラメータを設定
	m_move_win.SetParam(true, 0, 60, 0, 0, 0, 866, "OutCubic");
	m_move_lose.SetParam(true, 60, 60, 0, 0, 0, 866, "OutCubic");
}

ResultPoint::~ResultPoint()
{
}

void ResultPoint::SetPointRank()
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

		//2桁目を表示する必要があるか評価
		if (m_point[i] < 10 && more_than_100[i] == false)
			more_than_10[i] = false;
		else
			more_than_10[i] = true;

		ten_rank[i] = m_point[i] / 10;
		m_point[i] -= ten_rank[i] * 10;

		one_rank[i] = m_point[i] / 1;
	}
}

void ResultPoint::Draw(const int& _player1, const int& _player2, Game& _game)
{
	ModeResult* moderesult = (ModeResult*)_game.m_modeserver->Get("Result");
	//オブジェクトサーバがモードにないので、座標を更新
	m_move_win.Update(moderesult->GetModeCount());
	m_move_lose.Update(moderesult->GetModeCount());

	//勝敗によってプレイヤー1のポイント表示位置を調整
	int posx_p1;
	if (_player1 > _player2)
	{
		//WIN
		posx_p1 = 350 - 900 + static_cast<int>(m_move_win.GetValue());
		m_y = SCREEN_HEIGHT / 3 + 80;
	}
	else if (_player1 == _player2)
	{
		//DRAW
		posx_p1 = 350 - 900 + static_cast<int>(m_move_win.GetValue());
		m_y = SCREEN_HEIGHT / 3 + 80;
	}
	else
	{
		//LOSE
		posx_p1 = 350 - 900 + static_cast<int>(m_move_lose.GetValue());
		m_y = 100 + SCREEN_HEIGHT / 2 + 80;
	}

	if (more_than_1000[0])
		DrawGraph(posx_p1 + static_cast<int>(m_width * 0.75), m_y, m_thousand_graph[thousand_rank[0]], TRUE);
	if (more_than_100[0])
		DrawGraph(posx_p1 + static_cast<int>(m_width * 1.5), m_y, m_hundred_graph[hundred_rank[0]], TRUE);
	if (more_than_10[0])
		DrawGraph(posx_p1 + static_cast<int>(m_width * 2.25), m_y, m_ten_graph[ten_rank[0]], TRUE);
	DrawGraph(posx_p1 + m_width * 3, m_y, m_one_graph[one_rank[0]], TRUE);

	//勝敗によってプレイヤー2のポイント表示位置を調整
	int posx_p2;
	if (_player2 > _player1)
	{
		//WIN
		posx_p2 = 350 - 900 + static_cast<int>(m_move_win.GetValue());
		m_y = SCREEN_HEIGHT / 3 + 80;
	}
	else if (_player1 == _player2)
	{
		//DRAW
		posx_p2 = 350 - 900 + static_cast<int>(m_move_lose.GetValue());
		m_y = 100 + SCREEN_HEIGHT / 2 + 80;
	}
	else
	{
		//LOSE
		posx_p2 = 350 - 900 + static_cast<int>(m_move_lose.GetValue());
		m_y = 100 + SCREEN_HEIGHT / 2 + 80;
	}

	if (more_than_1000[1])
		DrawGraph(posx_p2 + static_cast<int>(m_width * 0.75), m_y, m_thousand_graph[thousand_rank[1]], TRUE);
	if (more_than_100[1])
		DrawGraph(posx_p2 + static_cast<int>(m_width * 1.5), m_y, m_hundred_graph[hundred_rank[1]], TRUE);
	if (more_than_10[1])
		DrawGraph(posx_p2 + static_cast<int>(m_width * 2.25), m_y, m_ten_graph[ten_rank[1]], TRUE);
	DrawGraph(posx_p2 + m_width * 3, m_y, m_one_graph[one_rank[1]], TRUE);
}

void ResultPoint::SetPoint(const int _player_num, const int _point)
{
	m_point[_player_num - 1] = _point;
}