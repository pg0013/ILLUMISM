/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeCredit.cpp.
 *
 * @brief	クレジット画面を表示するモード
 */

#include "ModeCredit.h"
#include "DxLib.h"
#include "ModeMainMenu.h"
#include"ModeOverlay.h"
#include"../Server/ResourceServer.h"
#include"../Game.h"
using namespace illumism;

bool ModeCredit::Initialize(Game& _game)
{
	if (!ModeBase::Initialize(_game)) { return false; }

	m_graph = ResourceServer::LoadGraph("resource/scorebonus/background_scorebonus.png");
	m_overlay_graph = ResourceServer::LoadGraph("resource/credit/overlay.png");
	m_credit_graph = ResourceServer::LoadGraph("resource/credit/credit.png");

	_game.m_se.Load("resource/se/cancel.wav");
	_game.m_se.SetVolume(SE_VOLUME);

	m_press_count = -1;
	m_once_flag = false;

	return true;
}

bool ModeCredit::Terminate(Game& _game)
{
	ModeBase::Terminate(_game);

	return true;
}

bool ModeCredit::Process(Game& _game)
{
	ModeBase::Process(_game);

	m_press_count--;

	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		//Bボタンが押されたらメインメニューモードへ移行
		if ((_game.m_trigger_key[i] & PAD_INPUT_2) &&
			m_once_flag == false)
		{
			_game.m_se.PlayBackGround(_game.m_se);

			ModeOverlay* modeoverlay = new ModeOverlay();
			modeoverlay->Capture(60);
			_game.m_modeserver->Add(modeoverlay, 1, "Overlay");

			//ModeOverlayがModeServerに追加されるまで待つ
			m_press_count = 1;

			m_once_flag = true;
		}
	}

	if (m_press_count == 0)
	{
		//Creditを選択した状態のメインメニューモードを生成
		ModeMainMenu* modemenu = new ModeMainMenu(ModeMainMenu::CREDIT, false);
		_game.m_modeserver->Add(modemenu, 0, "MainMenu");
		_game.m_modeserver->Del(this);
	}

	return true;
}

bool ModeCredit::Draw(Game& _game)
{
	ModeBase::Draw(_game);

	DrawGraph(0, 0, m_graph, FALSE);
	DrawGraph(0, 0, m_overlay_graph, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawGraph(0, 0, m_credit_graph, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	return true;
}