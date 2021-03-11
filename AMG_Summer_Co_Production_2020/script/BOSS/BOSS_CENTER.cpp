/**
 * @file	AMG_Summer_Co_Production_2020\script\BOSS_CENTER.cpp.
 *
 * @brief	ボスの中央パーツを描画
 */

#include "BOSS_CENTER.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

BOSS_CENTER::BOSS_CENTER()
{
	Init();
}

BOSS_CENTER::~BOSS_CENTER()
{
}

void BOSS_CENTER::Init()
{
	m_pyram_up_graph[0] = ResourceServer::LoadGraph("resource/boss/pyram_up.png");
	m_pyram_down_graph[0] = ResourceServer::LoadGraph("resource/boss/pyram_down.png");
	m_gear_graph[0] = ResourceServer::LoadGraph("resource/boss/gear.png");
	m_scrap_graph[0] = ResourceServer::LoadGraph("resource/boss/scrap.png");
	ResourceServer::LoadDivGraph("resource/boss/facialexpression_sheet.png", 9, 9, 1, 220, 220, m_eye_graph);
	ResourceServer::LoadDivGraph("resource/boss/boss_fallattack.png", 13, 13, 1, 1499, 1060, m_fallhand_graph);
	ResourceServer::LoadDivGraph("resource/boss/boss_groundattack.png", 11, 11, 1, 1499, 1060, m_groundhand_graph);

	m_pyram_up_graph[1] = ResourceServer::LoadGraph("resource/boss/dpyram_up.png");
	m_pyram_down_graph[1] = ResourceServer::LoadGraph("resource/boss/dpyram_down.png");
	m_gear_graph[1] = ResourceServer::LoadGraph("resource/boss/dgear.png");
	m_scrap_graph[1] = ResourceServer::LoadGraph("resource/boss/dscrap.png");

	m_righthand_graph[0] = ResourceServer::LoadGraph("resource/boss/righthand.png");
	m_righthand_graph[1] = ResourceServer::LoadGraph("resource/boss/drighthand.png");
	m_lefthand_graph[0] = ResourceServer::LoadGraph("resource/boss/lefthand.png");
	m_lefthand_graph[1] = ResourceServer::LoadGraph("resource/boss/dlefthand.png");

	m_x = 0;
	m_y = 0;
	eye = 0;
	m_startanim_frame = 0;
	once_flag = true;
}

void BOSS_CENTER::Process(Game& _game)
{
	ObjectBase::Process(_game);
}

void BOSS_CENTER::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	DrawRotaGraph(x, m_y - static_cast<int>(240 + 40 * sinf(DX_PI_F / 180.0f * (m_frame_count % 360))),
		1.0, 0, m_pyram_up_graph[0], TRUE);
	DrawRotaGraph(x, m_y + static_cast<int>(200 + 20 * cosf(DX_PI_F / 180.0f * (m_frame_count % 360))),
		1.0, 0, m_pyram_down_graph[0], TRUE);
	DrawRotaGraph(x, m_y + static_cast<int>(450 + 20 * sinf(DX_PI_F / 180.0f * (m_frame_count % 360))),
		1.0, 0, m_scrap_graph[0], TRUE);
	DrawRotaGraph(x, m_y,
		1.0, M_PI / 180.0 * static_cast<double>(m_frame_count % 360), m_gear_graph[0], TRUE);

}

void BOSS_CENTER::Damage(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	DrawRotaGraph(x, m_y - static_cast<int>(240 + 40 * sinf(DX_PI_F / 180 * (m_frame_count % 360))),
		1.0, 0, m_pyram_up_graph[1], TRUE);
	DrawRotaGraph(x, m_y + static_cast<int>(200 + 20 * cosf(DX_PI_F / 180 * (m_frame_count % 360))),
		1.0, 0, m_pyram_down_graph[1], TRUE);
	DrawRotaGraph(x, m_y + static_cast<int>(450 + 20 * sinf(DX_PI_F / 180 * (m_frame_count % 360))),
		1.0, 0, m_scrap_graph[1], TRUE);
	DrawRotaGraph(x, m_y,
		1.0, M_PI / 180.0 * static_cast<double>(m_frame_count % 360), m_gear_graph[1], TRUE);
}

void BOSS_CENTER::DrawHand(Game& _game, int _state, bool damage)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();
	int hand_graph = 0;
	int anim = 0;

	switch (_state)
	{
	case BOSS::BOSS_STATE::APPEAR:
	case BOSS::BOSS_STATE::DESTROY:
	case BOSS::BOSS_STATE::LASER_ATTACK:
	case BOSS::BOSS_STATE::MOVE:
		DrawRotaGraph(x + static_cast<int>(470 + 10 * cosf(DX_PI_F / 180 * (m_frame_count % 360))),
			m_y + static_cast<int>(150 + 50 * sinf(DX_PI_F / 180 * (m_frame_count % 360))),
			1.0, 0, m_righthand_graph[0], TRUE);

		DrawRotaGraph(x - static_cast<int>(470 + 10 * cosf(DX_PI_F / 180 * (m_frame_count % 360))),
			m_y + static_cast<int>(150 + 50 * sinf(DX_PI_F / 180 * (m_frame_count % 360))),
			1.0, 0, m_lefthand_graph[0], TRUE);

		once_flag = true;
		break;

	case BOSS::BOSS_STATE::FALL_ATTACK:
		if (once_flag)
		{
			m_startanim_frame = m_frame_count;
			once_flag = false;
		}

		//アニメーションを設定、指定フレーム経過したらアニメーションを止める
		if ((m_frame_count - m_startanim_frame) < 70)
			anim = (m_frame_count - m_startanim_frame) / 7 % 10;
		else
			anim = 9;

		hand_graph = m_fallhand_graph[anim];
		DrawRotaGraph(x, m_y + 200, 1.0, 0, hand_graph, TRUE);

		break;

	case BOSS::BOSS_STATE::GROUND_ATTACK:
		if (once_flag)
		{
			m_startanim_frame = m_frame_count;
			once_flag = false;
		}

		//4秒経過したら初めからアニメーションを再生
		if ((m_frame_count - m_startanim_frame) == 240)
			m_startanim_frame = m_frame_count;

		//アニメーションを設定、指定フレーム経過したらアニメーションを止める
		if ((m_frame_count - m_startanim_frame) < 49)
			anim = (m_frame_count - m_startanim_frame) / 7 % 7;
		else
			anim = 6;

		hand_graph = m_groundhand_graph[anim];
		DrawRotaGraph(x, m_y + 250, 1.0, 0, hand_graph, TRUE);

		break;

	case BOSS::BOSS_STATE::CROSS_LASER:
		if (once_flag)
		{
			m_startanim_frame = m_frame_count;
			once_flag = false;
		}

		//アニメーションを設定、指定フレーム経過したらアニメーションを止める
		if ((m_frame_count - m_startanim_frame) < 70)
			anim = (m_frame_count - m_startanim_frame) / 7 % 10;
		else
			anim = 9;

		hand_graph = m_fallhand_graph[anim];
		DrawRotaGraph(x, m_y + 200, 1.0, 0, hand_graph, TRUE);

		break;

	case BOSS::BOSS_STATE::SIMPLE_LASER:
		if (once_flag)
		{
			m_startanim_frame = m_frame_count;
			once_flag = false;
		}

		//アニメーションを設定、指定フレーム経過したらアニメーションを止める
		if ((m_frame_count - m_startanim_frame) < 70)
			anim = (m_frame_count - m_startanim_frame) / 7 % 10;
		else
			anim = 9;

		hand_graph = m_fallhand_graph[anim];
		DrawRotaGraph(x, m_y + 200, 1.0, 0, hand_graph, TRUE);

		break;
	}
}

void BOSS_CENTER::SwithEyeGraph(Game& _game, int _state, bool damage)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	int hp;
	for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
	{
		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::BOSS)
		{
			hp = (*iter)->GetHP();
			break;
		}
	}

	switch (_state)
	{
	case BOSS::BOSS_STATE::APPEAR:
	case BOSS::BOSS_STATE::DESTROY:
	case BOSS::BOSS_STATE::MOVE:
		eye = m_eye_graph[0];

		//HPが半分切ったら疲れ目画像に変更
		if (hp < 500 && hp>0)
			eye = m_eye_graph[8];

		once_flag = true;
		break;

	case BOSS::BOSS_STATE::FALL_ATTACK:
		eye = m_eye_graph[6];
		break;

	case BOSS::BOSS_STATE::GROUND_ATTACK:
		eye = m_eye_graph[6];
		break;

	case BOSS::BOSS_STATE::LASER_ATTACK:
		eye = m_eye_graph[1];
		break;

	case BOSS::BOSS_STATE::CROSS_LASER:
		eye = m_eye_graph[1];
		break;

	case BOSS::BOSS_STATE::SIMPLE_LASER:
		eye = m_eye_graph[1];
		break;
	}

	if (damage && hp > 0)
	{
		//ダメージ状態の目に変更
		eye = m_eye_graph[5];
	}
	else if (damage && hp == 0)
	{
		//撃破時の目の画像に変更
		eye = m_eye_graph[4];
	}

	int player_count = 0;
	for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
	{
		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::PLAYER ||
			(*iter)->GetType() == ObjectBase::OBJECT_TYPE::FLY)
		{
			player_count++;
		}
	}

	//プレイヤーがいなければにやり画像に変更
	if (player_count == 0)
		eye = m_eye_graph[7];

	DrawRotaGraph(static_cast<int>(x + 10 * cosf(DX_PI_F / 180 * (m_frame_count % 360))), static_cast<int>(m_y + 5 * sinf(DX_PI_F / 180 * (m_frame_count % 360))),
		1.0, 0, eye, TRUE);
}