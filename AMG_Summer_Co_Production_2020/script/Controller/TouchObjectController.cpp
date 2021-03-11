/**
 * @file	AMG_Summer_Co_Production_2020\script\TouchObjectController.cpp.
 *
 * @brief	タッチオブジェクトの出現を管理するクラス
 * 				45BPMと6BPMでオブジェクトを画面上に生成
 */

#include"TouchObjectController.h"
#include"../Object/TouchObject.h"
#include"../Game.h"
#include"../Mode/ModeGame.h"
#include"DxLib.h"
using namespace illumism;

TouchObjectController::TouchObjectController()
{
	m_time = 0;
	m_bpm_counter_6 = 1;
	m_bpm_counter_45 = 3;
}

TouchObjectController::~TouchObjectController()
{
}

void TouchObjectController::Process(Game& _game)
{
	//BGM再生からの経過時間を測定する
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	m_time = modeGame->GetModeCount();

	//45BPMでタッチオブジェクトを生成する
	if (m_time >= MINUTES / 45 * m_bpm_counter_45)
	{
		TouchObject* touch_object = new TouchObject(GetRand(11) + 1);

		touch_object->SetPosition(SCREEN_WIDTH * /*(GetRand(3) + 1)*/3 / 5, -220);

		//プレイヤーより前に描画されないために、インサートを使う
		_game.m_objectserver.Insert(touch_object);

		m_bpm_counter_45++;
	}

	//6BPMでタッチオブジェクトを生成する
	if (m_time >= MINUTES / 6 * m_bpm_counter_6)
	{
		TouchObject* touch_object = new TouchObject(GetRand(1) + 1);

		touch_object->SetPosition(SCREEN_WIDTH * (GetRand(1) + 1) / 3, -220);

		//プレイヤーより前に描画されないために、インサートを使う
		_game.m_objectserver.Insert(touch_object);

		m_bpm_counter_6++;
	}
}