/**
 * @file	AMG_Summer_Co_Production_2020\script\GameSign.cpp.
 *
 * @brief	ゲームカウントやREADY?などを表示するパーティクル
 * @author	Takuya Fujisawa
 */

#include "GameSign.h"
#include"../Server/ResourceServer.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

GameSign::GameSign(const char* _filename, int _x, int _y, int _cnt)
{
	m_graph = ResourceServer::LoadGraph(_filename);
	m_x = _x;
	m_y = _y;
	m_count = _cnt;
}

GameSign::~GameSign()
{
}

void GameSign::Process(Game& _game)
{
	m_count--;
	if (m_count <= 0)
		_game.m_objectserver.Delete(this);
}

void GameSign::Draw(Game& _game)
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, static_cast<int>(25.5 * m_count));
	DrawRotaGraph(m_x, m_y, 1, 0, m_graph, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}