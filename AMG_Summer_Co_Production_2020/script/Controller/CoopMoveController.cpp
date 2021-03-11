/**
 * @file	AMG_Summer_Co_Production_2020\script\CoopMoveController.cpp.
 *
 * @brief	協力技成功で発生するSPMoveObjectを管理するクラス
 * 				各プレイヤーがLBを押した時間の差分が500ms以内の時に協力技を生成
 */

#include"CoopMoveController.h"
#include"../Object/CoopMoveObject.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

CoopMoveController::CoopMoveController()
{
	//差分が500にならないように初期化
	for (int i = 0; i < 2; i++)
		m_pushtime[i] = 999 * i;
	m_difftime = 999;
}

CoopMoveController::~CoopMoveController()
{
}

void CoopMoveController::Process(Game& _game)
{
	int coop_count = 0;

	//生成されているCOOPオブジェクトの数を数える
	for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
	{
		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::COOP)
		{
			coop_count++;
		}
	}

	//協力技は画面に1個しか描画されない
	if (coop_count < 1)
	{
		//プレイヤーがLBを押した時間の差分を調べる
		SetDiffTime(m_pushtime);

		//500ms以内で協力技を生成
		if (m_difftime >= 0 && m_difftime <= 500)
		{
			CoopMoveObject* coop_object = new CoopMoveObject();
			_game.m_objectserver.Insert(coop_object);

			//差分が500にならないように初期化
			for (int i = 0; i < 2; i++)
				m_pushtime[i] = 999 * i;
		}
	}
}

void CoopMoveController::SetPushTime(int _num, int _frame)
{
	m_pushtime[_num - 1] = _frame;
}

void CoopMoveController::SetDiffTime(int _pushtime[2])
{
	m_difftime = abs(_pushtime[0] - _pushtime[1]);
}