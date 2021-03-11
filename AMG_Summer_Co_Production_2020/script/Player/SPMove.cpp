/**
 * @file	AMG_Summer_Co_Production_2020\script\SPMove.cpp
 *
 * @brief	必殺技オブジェクトの処理
 */

#include "SPMove.h"
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

SPMove::SPMove(int _num)
{
	m_player_num = _num;

	//プレイヤーごとに異なる色の画像を選択
	if (_num == 1)
		m_graph = ResourceServer::LoadGraph("resource/object/spmove1.png");
	if (_num == 2)
		m_graph = ResourceServer::LoadGraph("resource/object/spmove2.png");
	GetGraphSize(m_graph, &m_width, &m_height);

	Init();
}

SPMove::~SPMove()
{
}

void SPMove::Init()
{
	m_x = 0;
	m_y = 0;

	m_hit_x = 95;
	m_hit_y = 75;
	m_hit_w = 0;
	m_hit_h = 0;
}

void SPMove::Process(Game& _game)
{
	ObjectBase::Process(_game);

	SPMoveActivate(_game, 0, 80);
}

void SPMove::SetDirection(Game& _game, int _num, bool _turn_flag)
{
	//方向の設定
	if (_game.m_xinput_state[_num - 1].ThumbLX < 0)
	{
		m_direction_x = LEFT;
		m_turn_flag = true;
	}
	else if (_game.m_xinput_state[_num - 1].ThumbLX > 0)
	{
		m_direction_x = RIGHT;
		m_turn_flag = false;
	}

	//ニュートラル状態の時は画像の向きに合わせて向きを決める
	if (_game.m_xinput_state[_num - 1].ThumbLX == 0 &&
		_game.m_xinput_state[_num - 1].ThumbLY == 0)
	{
		if (_turn_flag == true)
		{
			m_direction_x = LEFT;
			m_turn_flag = true;
		}
		else
		{
			m_direction_x = RIGHT;
			m_turn_flag = false;
		}
	}
}

void SPMove::SPMoveActivate(Game& _game, const int _startframe, const int _activetime)
{
	auto elapsed_time = m_frame_count - _startframe;	//経過時間

	if (elapsed_time < 0)//遅延時間中は何もしない
	{
		return;
	}
	else if (elapsed_time < _activetime)
	{
		//判定出現中
		m_hit_w = m_width - m_hit_x * 2;
		m_hit_h = m_height - m_hit_y * 2;
	}
	else
	{
		//有効時間を過ぎたら破棄
		Damage(_game);
	}
}

void SPMove::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	SetDrawBlendMode(DX_BLENDMODE_ADD, 175);
	//画像の向きを反転する
	if (m_turn_flag == true)
		DrawTurnGraph(x, m_y, m_graph, TRUE);
	else
		DrawGraph(x, m_y, m_graph, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#ifdef _DEBUG
	if (m_ishit_flag)
	{
		//開発用当たり判定表示
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//描画モードを半透明描画にセット
		//攻撃の当たり判定
		DrawBox(x + m_hit_x, m_y + m_hit_y,
			x + m_hit_x + m_hit_w, m_y + m_hit_y + m_hit_h,
			GetColor(255, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//不透明描画に戻す
	}
#endif // _DEBUG
}

void SPMove::Damage(Game& _game)
{
	_game.m_objectserver.Delete(this);
}