/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeTitle.cpp.
 *
 * @brief	タイトル画面モード
 */

#include "ModeTitle.h"
#include "DxLib.h"
#include"ModeMainMenu.h"
#include"ModeOverlay.h"
#include"../Server/ResourceServer.h"
#include"../Game.h"
#define _USE_MATH_DEFINES
#include<math.h>
using namespace illumism;

void ModeTitle::Init()
{
	m_graph = ResourceServer::LoadGraph("resource/title/bg_title.png");
	m_press_graph = ResourceServer::LoadGraph("resource/title/ui_press_00.png");

	m_press_count = -1;
	m_once_flag = false;
}

bool ModeTitle::Initialize(Game& _game)
{
	if (!ModeBase::Initialize(_game)) { return false; }

	PlayBGM(_game);

	ModeOverlay* modeoverlay = new ModeOverlay();
	modeoverlay->Fade(120, FADE_IN);
	_game.m_modeserver->Add(modeoverlay, 0, "Overlay");

	Init();

	return true;
}

bool ModeTitle::Terminate(Game& _game)
{
	ModeBase::Terminate(_game);

	return true;
}

bool ModeTitle::Process(Game& _game)
{
	ModeBase::Process(_game);

	m_press_count--;

	Input(_game);
	NextMode(_game);

	return true;
}

bool ModeTitle::Draw(Game& _game)
{
	ModeBase::Draw(_game);

	DrawGraph(0, 0, m_graph, FALSE);

	//ボタンが押されたら点滅速度を上げる
	if (m_once_flag == false)
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(abs(255 * sin(DX_PI_F / 180 * 2.125 * GetModeCount()))));
	else
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(abs(255 * sin(DX_PI_F / 180 * 10 * GetModeCount()))));

	DrawRotaGraph(SCREEN_WIDTH / 2 + 5, SCREEN_HEIGHT * 4 / 5 - 105, 1.0, 0, m_press_graph, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	return true;
}

void ModeTitle::Input(Game& _game)
{
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		//Aボタンでメインメニューモードへ移行
		if ((_game.m_trigger_key[i] & PAD_INPUT_1) &&
			m_once_flag == false)
		{
			_game.m_se.Load("resource/se/title.wav");
			_game.m_se.SetVolume(SE_VOLUME);
			_game.m_se.PlayBackGround(_game.m_se);

			ModeOverlay* modeoverlay = new ModeOverlay();
			modeoverlay->Fade(120, FADE_OUT);
			_game.m_modeserver->Add(modeoverlay, 0, "Overlay");

			m_press_count = 120;
			m_once_flag = true;
		}
	}
}

void ModeTitle::NextMode(Game& _game)
{
	if (m_press_count == 0)
	{
		ModeMainMenu* modemenu = new ModeMainMenu(ModeMainMenu::BATTLE, false);
		_game.m_modeserver->Add(modemenu, 0, "MainMenu");

		_game.m_modeserver->Del(this);
	}
}

void ModeTitle::PlayBGM(Game& _game)
{
	_game.m_bgm.SetVolume(1.0f);
	_game.m_bgm.SetLoopCount(XAUDIO2_LOOP_INFINITE);
	m_freq = 100.0f;
	_game.m_bgm.LowPassFilter(m_freq);
	_game.m_bgm.PlayBackGroundWithLoop(_game.m_bgm, 24.0f, 170.823f);
}