/**
 * @file    TouchSuccessEffect.cpp
 * @brief   着地エフェクト用パーティクル
 *
 * @author Takuya Fujisawa
 * @date   2020/10/26
 */

#include "TouchSuccessEffect.h"
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

TouchSuccessEffect::TouchSuccessEffect(int _num, int _cnt)
{
	if (_num == 1)
		ResourceServer::LoadDivGraph("resource/player/touchsuccess_1.png", 10, 10, 1, 300, 300, m_touchsuccess_graph);
	if (_num == 2)
		ResourceServer::LoadDivGraph("resource/player/touchsuccess_2.png", 10, 10, 1, 300, 300, m_touchsuccess_graph);

	m_player_num = _num;
	m_frame_count = _cnt;
	m_all_count = _cnt;
}

TouchSuccessEffect::~TouchSuccessEffect() {}

void TouchSuccessEffect::Process(Game& _game)
{
	m_frame_count--;

	//座標更新
	for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
	{
		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::PLAYER)
		{
			if ((*iter)->GetPlayerNum() == m_player_num)
			{
				m_x = (*iter)->GetPosX() + (*iter)->GetWidth() / 2;
				m_y = (*iter)->GetPosY() + (*iter)->GetHeight() / 2;
			}
		}

		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::FLY)
		{
			if ((*iter)->GetPlayerNum() == m_player_num)
			{
				_game.m_objectserver.Delete(this);
			}
		}
	}

	if (m_frame_count <= 0)
		_game.m_objectserver.Delete(this);
}

void TouchSuccessEffect::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * (m_all_count - m_frame_count));
	if (modeGame->GetPlayerCharactor(m_player_num) == NARI1 ||
		modeGame->GetPlayerCharactor(m_player_num) == NARI2)
		DrawRotaGraph(x + 70, m_y - 70, 1.0, 0, m_touchsuccess_graph[(m_all_count - m_frame_count) / 3 % 10], TRUE);
	if (modeGame->GetPlayerCharactor(m_player_num) == NONAME1 ||
		modeGame->GetPlayerCharactor(m_player_num) == NONAME2)
		DrawRotaGraph(x + 70, m_y - 110, 1.0, 0, m_touchsuccess_graph[(m_all_count - m_frame_count) / 3 % 10], TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}