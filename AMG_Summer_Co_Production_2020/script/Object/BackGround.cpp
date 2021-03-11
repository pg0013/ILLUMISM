/**
 * @file	AMG_Summer_Co_Production_2020\script\BackGround.cpp.
 *
 * @brief	ゲームモードの背景オブジェクトクラス
 */

#include "BackGround.h"
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

BackGround::BackGround()
{
	m_background_graph = ResourceServer::LoadGraph("resource/background/background.png");
	GetGraphSize(m_background_graph, &m_width, &m_height);

	//多重スクロールのために、背景をパーツごとに読み込む
	m_arch_graph[0] = ResourceServer::LoadGraph("resource/background/arch_d.png");
	m_arch_graph[1] = ResourceServer::LoadGraph("resource/background/arch_c.png");
	m_arch_graph[2] = ResourceServer::LoadGraph("resource/background/arch_b.png");
	m_arch_graph[3] = ResourceServer::LoadGraph("resource/background/arch_a.png");
	m_seat_graph[0] = ResourceServer::LoadGraph("resource/background/sitting_d.png");
	m_seat_graph[1] = ResourceServer::LoadGraph("resource/background/sitting_c.png");
	m_seat_graph[2] = ResourceServer::LoadGraph("resource/background/sitting_b.png");
	m_seat_graph[3] = ResourceServer::LoadGraph("resource/background/sitting_a.png");
	m_penlight_graph[0] = ResourceServer::LoadGraph("resource/background/penlight_d2.png");
	m_penlight_graph[1] = ResourceServer::LoadGraph("resource/background/penlight_c2.png");
	m_penlight_graph[2] = ResourceServer::LoadGraph("resource/background/penlight_b2.png");
	m_penlight_graph[3] = ResourceServer::LoadGraph("resource/background/penlight_a2.png");
	m_spot_graph[0] = ResourceServer::LoadGraph("resource/background/background_spot.png");
	m_spot_graph[1] = ResourceServer::LoadGraph("resource/background/bg_spotlight_2.png");
	m_stage_graph = ResourceServer::LoadGraph("resource/background/stage.png");
	m_audience_graph = ResourceServer::LoadGraph("resource/background/standing.png");

	m_x = -m_width / 2 + SCREEN_WIDTH / 2;
	m_y = -m_height / 2 + 100 + SCREEN_HEIGHT / 2 - 100;
}

BackGround::~BackGround()
{
}

void BackGround::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();
	int y = m_y - modeGame->m_camera.GetScreenY();

	DrawGraph(m_x - modeGame->m_camera.GetScreenX(), y, m_background_graph, TRUE);

	//カメラ移動速度をレイヤーごとに変え、多重スクロールを行う
	//手前のレイヤーにつれて、カメラ速度より移動速度を大きくする
	float vx = 1.0f;
	DrawGraph(static_cast<int>(m_x - vx * modeGame->m_camera.GetScreenX()), y, m_arch_graph[0], TRUE);
	DrawGraph(static_cast<int>(m_x - vx * modeGame->m_camera.GetScreenX()), y, m_seat_graph[0], TRUE);
	DrawGraph(static_cast<int>(m_x - vx * modeGame->m_camera.GetScreenX()), static_cast<int>(y - abs(5 * sin(3.14f / 180 * 2.0f * modeGame->GetModeCount()))), m_penlight_graph[0], TRUE);
	vx = 1.02f;
	DrawGraph(static_cast<int>(m_x - vx * modeGame->m_camera.GetScreenX()), y, m_arch_graph[1], TRUE);
	DrawGraph(static_cast<int>(m_x - vx * modeGame->m_camera.GetScreenX()), y, m_seat_graph[1], TRUE);
	DrawGraph(static_cast<int>(m_x - vx * modeGame->m_camera.GetScreenX()), static_cast<int>(y - abs(8 * sin(3.14f / 180 * 2.0f * modeGame->GetModeCount()))), m_penlight_graph[1], TRUE);
	vx = 1.08f;
	DrawGraph(static_cast<int>(m_x - vx * modeGame->m_camera.GetScreenX()), y, m_arch_graph[2], TRUE);
	DrawGraph(static_cast<int>(m_x - vx * modeGame->m_camera.GetScreenX()), y, m_seat_graph[2], TRUE);
	DrawGraph(static_cast<int>(m_x - vx * modeGame->m_camera.GetScreenX()), static_cast<int>(y - abs(10 * sin(3.14f / 180 * 2.0f * modeGame->GetModeCount()))), m_penlight_graph[2], TRUE);
	vx = 1.25f;
	DrawGraph(static_cast<int>(m_x - vx * modeGame->m_camera.GetScreenX()), y, m_arch_graph[3], TRUE);
	DrawGraph(static_cast<int>(m_x - vx * modeGame->m_camera.GetScreenX()), y, m_seat_graph[3], TRUE);
	DrawGraph(static_cast<int>(m_x - vx * modeGame->m_camera.GetScreenX()), static_cast<int>(y - abs(15 * sin(3.14f / 180 * 2.0f * modeGame->GetModeCount()))), m_penlight_graph[3], TRUE);

	DrawGraph(x, y, m_stage_graph, TRUE);

	//ステージ上にかすかに見えるスポットライトを描画
	SetDrawBlendMode(DX_BLENDMODE_ADD, 35);
	DrawGraph(SCREEN_WIDTH / 2 - 1765 / 2 - 40 - modeGame->m_camera.GetScreenX(), -100 - modeGame->m_camera.GetScreenY(), m_spot_graph[0], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawGraph(x, y, m_spot_graph[1], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void BackGround::DrawAudience(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int y = m_y - modeGame->m_camera.GetScreenY();

	float vx = 2.0f;
	DrawGraph(m_x - 220 - static_cast<int>(vx * modeGame->m_camera.GetScreenX()), static_cast<int>(y - 110 - abs(100 * sin(3.14f / 180 * 2.0f * modeGame->GetModeCount()))), m_audience_graph, TRUE);
}