/**
 * @file	AMG_Summer_Co_Production_2020\script\BOSS_LEFT.cpp.
 *
 * @brief	ボスの左パーツを描画
 */

#include "BOSS_LEFT.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

BOSS_LEFT::BOSS_LEFT()
{
	Init();
}

BOSS_LEFT::~BOSS_LEFT()
{
}

void BOSS_LEFT::Init()
{
	m_leftsand_graph[0] = ResourceServer::LoadGraph("resource/boss/leftsand.png");
	m_leftclock_graph[0] = ResourceServer::LoadGraph("resource/boss/leftclock.png");
	m_leftgear1_graph[0] = ResourceServer::LoadGraph("resource/boss/leftgear1.png");
	m_leftgear2_graph[0] = ResourceServer::LoadGraph("resource/boss/leftgear2.png");
	m_leftgear3_graph[0] = ResourceServer::LoadGraph("resource/boss/leftgear3.png");

	m_leftsand_graph[1] = ResourceServer::LoadGraph("resource/boss/dleftsand.png");
	m_leftclock_graph[1] = ResourceServer::LoadGraph("resource/boss/dleftclock.png");
	m_leftgear1_graph[1] = ResourceServer::LoadGraph("resource/boss/dleftgear1.png");
	m_leftgear2_graph[1] = ResourceServer::LoadGraph("resource/boss/dleftgear2.png");
	m_leftgear3_graph[1] = ResourceServer::LoadGraph("resource/boss/dleftgear3.png");

	m_x = 0;
	m_y = 0;
}

void BOSS_LEFT::Process(Game& _game)
{
	ObjectBase::Process(_game);
}

void BOSS_LEFT::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	DrawRotaGraph(x, m_y,
		1.0, -M_PI / 180.0 * static_cast<double>(m_frame_count % 360), m_leftgear1_graph[0], TRUE);
	DrawRotaGraph(x - 50, m_y + 50,
		1.0, M_PI / 180.0 * static_cast<double>(m_frame_count % 360), m_leftgear2_graph[0], TRUE);
	DrawRotaGraph(x + 50, m_y + 160,
		1.0, M_PI / 180.0 * static_cast<double>(m_frame_count % 360), m_leftgear3_graph[0], TRUE);
	DrawRotaGraph(x - 180, m_y + static_cast<int>(100 + 10 * cosf(DX_PI_F / 180 * (m_frame_count % 360))),
		1.0, M_PI / 180.0 * static_cast<double>(m_frame_count % 360), m_leftsand_graph[0], TRUE);
	DrawRotaGraph(x - 100, m_y + static_cast<int>(200 + 20 * sinf(DX_PI_F / 180 * (m_frame_count % 360))),
		1.0, M_PI / 180.0 * static_cast<double>(m_frame_count % 360), m_leftclock_graph[0], TRUE);
}

void BOSS_LEFT::Damage(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	DrawRotaGraph(x, m_y,
		1.0, -M_PI / 180.0 * static_cast<double>(m_frame_count % 360), m_leftgear1_graph[1], TRUE);
	DrawRotaGraph(x - 50, m_y + 50,
		1.0, M_PI / 180.0 * static_cast<double>(m_frame_count % 360), m_leftgear2_graph[1], TRUE);
	DrawRotaGraph(x + 50, m_y + 160,
		1.0, M_PI / 180.0 * static_cast<double>(m_frame_count % 360), m_leftgear3_graph[1], TRUE);
	DrawRotaGraph(x - 180, m_y + static_cast<int>(100 + 10 * cosf(DX_PI_F / 180 * (m_frame_count % 360))),
		1.0, M_PI / 180.0 * static_cast<double>(m_frame_count % 360), m_leftsand_graph[1], TRUE);
	DrawRotaGraph(x - 100, m_y + static_cast<int>(200 + 20 * sinf(DX_PI_F / 180 * (m_frame_count % 360))),
		1.0, M_PI / 180.0 * static_cast<double>(m_frame_count % 360), m_leftclock_graph[1], TRUE);
}