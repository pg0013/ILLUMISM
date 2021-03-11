/**
 * @file	AMG_Summer_Co_Production_2020\script\ObjectBase.cpp.
 *
 * @brief	ゲーム内のオブジェクトの基底クラス
 */

#include "ObjectBase.h"
#include"DxLib.h"
#include"../Game.h"
#include"../Mode/ModeGame.h"
using namespace illumism;

ObjectBase::ObjectBase()
{
	Init();
}

ObjectBase::~ObjectBase()
{
}

void ObjectBase::Init()
{
	m_frame_count = 0;
	m_hit_no_count = 0;
	m_player_num = 0;
}

void ObjectBase::Process(Game& _game)
{
	if (m_hit_no_count > 0)
		m_hit_no_count--;

	m_frame_count++;
}

void ObjectBase::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	//画像の向きを反転する
	if (m_turn_flag == true)
		DrawTurnGraph(x, m_y, m_graph, TRUE);
	else
		DrawGraph(x, m_y, m_graph, TRUE);

#ifdef _DEBUG
	if (m_ishit_flag)
	{
		//開発用当たり判定表示
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//描画モードを半透明描画にセット
		//体の当たり判定
		DrawBox(x + m_hit_x, m_y + m_hit_y,
			x + m_hit_x + m_hit_w, m_y + m_hit_y + m_hit_h,
			GetColor(255, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//不透明描画に戻す
	}
#endif // _DEBUG
}

bool ObjectBase::IsHit(ObjectBase& _object)
{
	if (m_ishit_flag)
	{
		if (m_x + m_hit_x < _object.m_x + _object.m_hit_x + _object.m_hit_w &&		//左上x座標比較
			_object.m_x + _object.m_hit_x < m_x + m_hit_x + m_hit_w &&					//右上x座標比較
			m_y + m_hit_y < _object.m_y + _object.m_hit_y + _object.m_hit_h &&		//左上y座標比較
			_object.m_y + _object.m_hit_y < m_y + m_hit_y + m_hit_h						//右上y座標比較
			&& m_hit_no_count == 0 && _object.m_hit_no_count == 0)						//無敵時間が無効か確認
			return true;
	}
	return false;
}