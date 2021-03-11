/**
 * @file	AMG_Summer_Co_Production_2020\script\PlayerUIController.cpp.
 *
 * @brief	ゲームモード内のプレイヤーに関するUIを描画するクラス
 */

#include"PlayerUIController.h"
#include"../Server/ResourceServer.h"
#include"../Game.h"
#include"../Mode/ModeGame.h"
#include"DxLib.h"
using namespace illumism;

PlayerUIController::PlayerUIController()
{
	m_graph_1 = ResourceServer::LoadGraph("resource/ingameUI/UI_1.png");
	GetGraphSize(m_graph_1, &m_width, &m_height);
	m_graph_2 = ResourceServer::LoadGraph("resource/ingameUI/UI_3_2.png");
	m_graph_4 = ResourceServer::LoadGraph("resource/ingameUI/UI_5_2.png");
	m_graph_5_1 = ResourceServer::LoadGraph("resource/ingameUI/UI_P1_6.png");
	m_graph_5_2 = ResourceServer::LoadGraph("resource/ingameUI/UI_P2_6.png");
	m_graph_6 = ResourceServer::LoadGraph("resource/ingameUI/UI_Point_8_2.png");
	m_graph_7 = ResourceServer::LoadGraph("resource/ingameUI/UI_7.png");
	m_graph_8 = ResourceServer::LoadGraph("resource/ingameUI/UI_heart_8.png");
	m_graph_9 = ResourceServer::LoadGraph("resource/ingameUI/UI_star_8.png");

	m_x = 0;
	m_y = 0;
	m_once_flag = true;
}

PlayerUIController::~PlayerUIController()
{
}

void PlayerUIController::Process(Game& _game)
{
	m_pointUI.Process(_game);
	m_hpbarUI.Process(_game);
	m_flybarUI.Process(_game);
	m_spmoveUI.Process(_game);

	if (m_once_flag)
	{
		ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
		SetPlayerIcon(modeGame->GetPlayerCharactor(1), modeGame->GetPlayerCharactor(2));
		m_once_flag = false;
	}
}

void PlayerUIController::Draw(Game& _game)
{
	m_x = SCREEN_WIDTH / 4 - m_width / 2;
	m_y = GROUND + 35;

	for (int i = 0; i < 2; i++)
	{
		if (i == 1) { m_x = SCREEN_WIDTH * 3 / 4 - m_width / 2; }

		DrawGraph(m_x, m_y - 3, m_graph_1, TRUE);
	}

	m_spmoveUI.Draw(_game);
	m_hpbarUI.Draw(_game);
	m_flybarUI.Draw(_game);

	m_x = SCREEN_WIDTH / 4 - m_width / 2;

	for (int i = 0; i < 2; i++)
	{
		if (i == 1) { m_x = SCREEN_WIDTH * 3 / 4 - m_width / 2; }

		DrawGraph(m_x + 22, m_y + 16, m_graph_2, TRUE);
		DrawGraph(m_x, m_y, m_graph_4, TRUE);
		DrawGraph(m_x + 3, m_y + 1, m_graph_7, TRUE);
		DrawGraph(m_x + 106, m_y + 58, m_graph_8, TRUE);
		DrawGraph(m_x + 104, m_y + 75, m_graph_9, TRUE);

		if (i == 0)
			DrawGraph(m_x + 110, m_y + 26, m_graph_5_1, TRUE);
		else
			DrawGraph(m_x + 110, m_y + 26, m_graph_5_2, TRUE);
	}

	m_x = SCREEN_WIDTH / 4 - m_width / 2 -25;
	m_y = GROUND + 80;

	for (int i = 0; i < 2; i++)
	{
		if (i == 1) { m_x = SCREEN_WIDTH * 3 / 4 - m_width / 2 -25; }

		DrawGraph(m_x + 50, m_y - 25, m_graph_10[i], TRUE);
	}

	m_spmoveUI.DrawAura();

	m_x = SCREEN_WIDTH / 4 - m_width / 2 + 400;
	m_y = GROUND + 100;

	for (int i = 0; i < 2; i++)
	{
		if (i == 1) { m_x = SCREEN_WIDTH * 3 / 4 - m_width / 2 + 400; }

		DrawGraph(m_x + 50, m_y - 25, m_graph_6, TRUE);
	}

	m_pointUI.Draw(_game);
}

void PlayerUIController::SetPlayerIcon(const int _p1chara, const int _p2chara)
{
	switch (_p1chara)
	{
	case NARI1:
		m_graph_10[0] = ResourceServer::LoadGraph("resource/ingameUI/sicon_nari_1.png");
		break;
	case NARI2:
		m_graph_10[0] = ResourceServer::LoadGraph("resource/ingameUI/sicon_nari_2.png");
		break;
	case NONAME1:
		m_graph_10[0] = ResourceServer::LoadGraph("resource/ingameUI/sicon_unknown_1.png");
		break;
	case NONAME2:
		m_graph_10[0] = ResourceServer::LoadGraph("resource/ingameUI/sicon_unknown_2.png");
		break;
	}

	switch (_p2chara)
	{
	case NARI1:
		m_graph_10[1] = ResourceServer::LoadGraph("resource/ingameUI/sicon_nari_1.png");
		break;
	case NARI2:
		m_graph_10[1] = ResourceServer::LoadGraph("resource/ingameUI/sicon_nari_2.png");
		break;
	case NONAME1:
		m_graph_10[1] = ResourceServer::LoadGraph("resource/ingameUI/sicon_unknown_1.png");
		break;
	case NONAME2:
		m_graph_10[1] = ResourceServer::LoadGraph("resource/ingameUI/sicon_unknown_2.png");
		break;
	}
}