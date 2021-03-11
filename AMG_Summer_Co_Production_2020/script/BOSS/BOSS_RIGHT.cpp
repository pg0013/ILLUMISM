/**
 * @file	AMG_Summer_Co_Production_2020\script\BOSS_RIGHT.cpp.
 *
 * @brief	ボスの右パーツを描画
 */

#include "BOSS_RIGHT.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

BOSS_RIGHT::BOSS_RIGHT()
{
	Init();
}

BOSS_RIGHT::~BOSS_RIGHT()
{
}

void BOSS_RIGHT::Init()
{
	m_right_a_graph[0] = ResourceServer::LoadGraph("resource/boss/right_a.png");
	m_right_b_graph[0] = ResourceServer::LoadGraph("resource/boss/right_b.png");
	m_right_c_graph[0] = ResourceServer::LoadGraph("resource/boss/right_c.png");
	m_rightgear1_graph[0] = ResourceServer::LoadGraph("resource/boss/rightgear1.png");
	m_rightgear2_graph[0] = ResourceServer::LoadGraph("resource/boss/rightgear2.png");
	m_rightgear3_graph[0] = ResourceServer::LoadGraph("resource/boss/rightgear3.png");

	m_right_a_graph[1] = ResourceServer::LoadGraph("resource/boss/dright_a.png");
	m_right_b_graph[1] = ResourceServer::LoadGraph("resource/boss/dright_b.png");
	m_right_c_graph[1] = ResourceServer::LoadGraph("resource/boss/dright_c.png");
	m_rightgear1_graph[1] = ResourceServer::LoadGraph("resource/boss/drightgear1.png");
	m_rightgear2_graph[1] = ResourceServer::LoadGraph("resource/boss/drightgear2.png");
	m_rightgear3_graph[1] = ResourceServer::LoadGraph("resource/boss/drightgear3.png");

	m_x = 0;
	m_y = 0;
}

void BOSS_RIGHT::Process(Game& _game)
{
	ObjectBase::Process(_game);
}

void BOSS_RIGHT::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	DrawRotaGraph(x, m_y,
		1.0, -M_PI / 180.0 * static_cast<double>(m_frame_count % 360), m_rightgear1_graph[0], TRUE);
	DrawRotaGraph(x + 100, m_y + 50,
		1.0, M_PI / 180.0 * static_cast<double>(m_frame_count % 360), m_rightgear2_graph[0], TRUE);
	DrawRotaGraph(x, m_y + 150,
		1.0, M_PI / 180.0 * static_cast<double>(m_frame_count % 360), m_rightgear3_graph[0], TRUE);
	DrawRotaGraph(x + 100, m_y + static_cast<int>(180 + 10 * sinf(DX_PI_F / 180 * (m_frame_count % 360))),
		1.0, 0, m_right_a_graph[0], TRUE);
	DrawRotaGraph(x + 180, m_y + static_cast<int>(120 + 20 * cosf(DX_PI_F / 180 * (m_frame_count % 360))),
		1.0, 0, m_right_b_graph[0], TRUE);
	DrawRotaGraph(x + 250, m_y + static_cast<int>(50 + 10 * sinf(DX_PI_F / 180 * (m_frame_count % 360))),
		1.0, 0, m_right_c_graph[0], TRUE);
}

void BOSS_RIGHT::Damage(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	DrawRotaGraph(x, m_y,
		1.0, -M_PI / 180.0 * static_cast<double>(m_frame_count % 360), m_rightgear1_graph[1], TRUE);
	DrawRotaGraph(x + 100, m_y + 50,
		1.0, M_PI / 180.0 * static_cast<double>(m_frame_count % 360), m_rightgear2_graph[1], TRUE);
	DrawRotaGraph(x, m_y + 150,
		1.0, M_PI / 180.0 * static_cast<double>(m_frame_count % 360), m_rightgear3_graph[1], TRUE);
	DrawRotaGraph(x + 100, m_y + static_cast<int>(180 + 10 * sinf(DX_PI_F / 180 * (m_frame_count % 360))),
		1.0, 0, m_right_a_graph[1], TRUE);
	DrawRotaGraph(x + 180, m_y + static_cast<int>(120 + 20 * cosf(DX_PI_F / 180 * (m_frame_count % 360))),
		1.0, 0, m_right_b_graph[1], TRUE);
	DrawRotaGraph(x + 250, m_y + static_cast<int>(50 + 10 * sinf(DX_PI_F / 180 * (m_frame_count % 360))),
		1.0, 0, m_right_c_graph[1], TRUE);
}