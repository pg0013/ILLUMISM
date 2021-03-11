/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeTutorial.cpp.
 *
 * @brief	チュートリアル表示モード
 */

#include "ModeTutorial.h"
#include "ModeMainMenu.h"
#include"ModeOverlay.h"
#include"../Server/ResourceServer.h"
#include"../Game.h"
#include "DxLib.h"
using namespace illumism;

void ModeTutorial::Init()
{
	m_tutorial1_graph = ResourceServer::LoadGraph("resource/tutorial/tutorial_1.jpg");
	m_tutorial2_graph = ResourceServer::LoadGraph("resource/tutorial/tutorial_2.png");
	m_graph = m_tutorial1_graph;

	m_press_count = -1;
	m_once_flag = false;

	m_tutorial_mode = m_tutorial1_graph;
	m_premode = m_tutorial_mode;
}

bool ModeTutorial::Initialize(Game& _game)
{
	if (!ModeBase::Initialize(_game)) { return false; }

	Init();

	return true;
}

bool ModeTutorial::Terminate(Game& _game)
{
	ModeBase::Terminate(_game);

	return true;
}

bool ModeTutorial::Process(Game& _game)
{
	ModeBase::Process(_game);

	m_press_count--;

	//前フレームで指定したモードを設定
	m_tutorial_mode = m_premode;

	Input(_game);
	NextMode(_game);

	return true;
}

bool ModeTutorial::Draw(Game& _game)
{
	ModeBase::Draw(_game);

	if (m_tutorial_mode == m_tutorial1_graph)
		m_graph = m_tutorial1_graph;
	if (m_tutorial_mode == m_tutorial2_graph)
		m_graph = m_tutorial2_graph;

	DrawGraph(0, 0, m_graph, FALSE);
	return true;
}

void ModeTutorial::Input(Game& _game)
{
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		//Aボタン
		if (_game.m_trigger_key[i] & PAD_INPUT_1)
		{
			if (m_graph != m_tutorial1_graph)
				return;

			_game.m_se.Load("resource/se/menu_select.wav");
			_game.m_se.SetVolume(SE_VOLUME);
			_game.m_se.PlayBackGround(_game.m_se);

			ModeOverlay* modeoverlay = new ModeOverlay();
			modeoverlay->Capture(30);
			_game.m_modeserver->Add(modeoverlay, 1, "Overlay");

			//操作説明画像を表示
			m_premode = m_tutorial2_graph;
		}

		//Bボタン
		if ((_game.m_trigger_key[i] & PAD_INPUT_2) &&
			m_once_flag == false)
		{
			if (m_graph != m_tutorial2_graph)
				return;
			
			_game.m_se.Load("resource/se/cancel.wav");
			_game.m_se.PlayBackGround(_game.m_se);

			ModeOverlay* modeoverlay = new ModeOverlay();
			modeoverlay->Capture(60);
			_game.m_modeserver->Add(modeoverlay, 1, "Overlay");

			m_press_count = 1;
			m_once_flag = true;
		}
	}
}

void ModeTutorial::NextMode(Game& _game)
{
	if (m_press_count == 0)
	{
		ModeMainMenu* modemenu = new ModeMainMenu(ModeMainMenu::TUTORIAL, false);
		_game.m_modeserver->Add(modemenu, 0, "MainMenu");
		_game.m_modeserver->Del(this);
	}
}