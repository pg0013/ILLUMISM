/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeLogo.cpp.
 *
 * @brief	AMGとチームロゴ表示モード
 * 				コンストラクタで描画するロゴを指定する
 * 				2秒フェードイン → 2秒ロゴ画像 → 2秒フェードアウト
 * 				Aボタンが押されたら1秒で次のモードに移行
 */

#include "ModeLogo.h"
#include"ModeTitle.h"
#include"ModeOverlay.h"
#include"../Server/ResourceServer.h"
#include"../Game.h"
#include "DxLib.h"
using namespace illumism;

ModeLogo::ModeLogo(int _num)
{
	//描画するロゴ画像を選択
	if (_num == AMG_LOGO)
	{
		m_graph = ResourceServer::LoadGraph("resource/logo/logo_amg.jpg");
		logonum = AMG_LOGO;
	}
	else
	{
		m_graph = ResourceServer::LoadGraph("resource/logo/teamlogo.png");
		logonum = TEAM_LOGO;
	}
	m_once_flag = false;
	m_press_count = -1;
}

bool ModeLogo::Initialize(Game& _game)
{
	if (!ModeBase::Initialize(_game)) { return false; }

	//フェードイン
	ModeOverlay* modeoverlay = new ModeOverlay();
	modeoverlay->Fade(120, FADE_IN);
	_game.m_modeserver->Add(modeoverlay, 0, "Overlay");

	return true;
}

bool ModeLogo::Terminate(Game& _game)
{
	ModeBase::Terminate(_game);
	return true;
}

bool ModeLogo::Process(Game& _game)
{
	ModeBase::Process(_game);

	m_press_count--;

	Input(_game);

	Transition(_game);

	SkipLogoMode(_game);

	return true;
}

void ModeLogo::Input(Game& _game)
{
	//Aボタンが押されたらスキップ
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		if ((_game.m_trigger_key[i] & PAD_INPUT_1) &&
			m_once_flag == false &&
			GetModeCount() < 240)
		{
			//フェードアウト
			ModeOverlay* modeoverlay = new ModeOverlay();
			modeoverlay->Fade(61, FADE_OUT);
			_game.m_modeserver->Add(modeoverlay, 99, "Overlay");
			m_press_count = 60;

			m_once_flag = true;
		}
	}
}

void ModeLogo::Transition(Game& _game)
{
	//モード開始から4秒後にフェードアウト
	if (GetModeCount() == 240 && m_once_flag == false)
	{
		ModeOverlay* modeoverlay = new ModeOverlay();
		modeoverlay->Fade(121, FADE_OUT);
		_game.m_modeserver->Add(modeoverlay, 1, "Overlay");
	}

	//モード開始から6秒後にモード遷移
	if (GetModeCount() == 360 && logonum == TEAM_LOGO)
	{
		//タイトルモードへ移行
		ModeTitle* modetitle = new ModeTitle();
		_game.m_modeserver->Add(modetitle, 0, "Title");
		_game.m_modeserver->Del(this);
	}
	else if (GetModeCount() == 360)
	{
		//チームロゴへ移行
		ModeLogo* modelogo = new ModeLogo(TEAM_LOGO);
		_game.m_modeserver->Add(modelogo, 0, "Logo");
		_game.m_modeserver->Del(this);
	}
}

void ModeLogo::SkipLogoMode(Game& _game)
{
	//チームロゴ画像へすぐ移行
	if (logonum == AMG_LOGO && m_press_count == 0)
	{
		ModeLogo* modelogo = new ModeLogo(TEAM_LOGO);
		_game.m_modeserver->Add(modelogo, 0, "Logo");
		_game.m_modeserver->Del(this);
	}

	//タイトルモードへすぐ移行
	if (logonum == TEAM_LOGO && m_press_count == 0)
	{
		ModeTitle* modetitle = new ModeTitle();
		_game.m_modeserver->Add(modetitle, 0, "Title");
		_game.m_modeserver->Del(this);
	}
}

bool ModeLogo::Draw(Game& _game)
{
	ModeBase::Draw(_game);

	DrawGraph(0, 0, m_graph, FALSE);

	return true;
}