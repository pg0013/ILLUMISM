/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeMainMenu.cpp.
 *
 * @brief	メインメニューモード
 */

#include "ModeMainMenu.h"
#include"ModeTitle.h"
#include"ModeOverlay.h"
#include"ModeTutorial.h"
#include"ModeCredit.h"
#include"ModeSelectChara.h"
#include"../Server/ResourceServer.h"
#include"../Game.h"
#include"../Utility/Utility.h"
#include "DxLib.h"
using namespace illumism;

ModeMainMenu::ModeMainMenu(int _menu_state, bool _playbgm)
{
	m_background_graph = ResourceServer::LoadGraph("resource/mainmenu/bg_menu_00.jpg");
	m_battle_graph = ResourceServer::LoadGraph("resource/mainmenu/ui_menu_battle_00.png");
	m_tutorial_graph = ResourceServer::LoadGraph("resource/mainmenu/ui_menu_tut_00.png");
	m_exit_graph = ResourceServer::LoadGraph("resource/mainmenu/ui_menu_exit_00.png");
	GetGraphSize(m_exit_graph, &m_width, &m_height);
	m_credit_graph = ResourceServer::LoadGraph("resource/mainmenu/ui_menu_cre_00.png");

	m_menu_state = _menu_state;
	m_playbgm_flag = _playbgm;

	m_selected_flag = false;
	m_press_count = -1;
	m_press_frame = 0;
	m_freq = 0;
}

bool ModeMainMenu::Initialize(Game& _game)
{
	if (!ModeBase::Initialize(_game)) { return false; }

	//ゲームモードの画像を非同期読み込み
	utility::LoadGraphHandle();

	//暗転からフェードイン
	ModeOverlay* modeoverlay = new ModeOverlay();
	modeoverlay->Fade(120, FADE_IN);
	_game.m_modeserver->Add(modeoverlay, 0, "Overlay");

	//リザルト画面から遷移したときにBGMを流す
	PlayBGM(_game);

	return true;
}

bool ModeMainMenu::Terminate(Game& _game)
{
	ModeBase::Terminate(_game);

	return true;
}

bool ModeMainMenu::Process(Game& _game)
{
	ModeBase::Process(_game);

	m_press_count--;

	Input(_game);
	State(_game);

	NextMode(_game);
	return true;
}

void ModeMainMenu::Input(Game& _game)
{
	if (m_selected_flag == true)
		return;

	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		int pre_state = m_menu_state;

		//↑↓選択でメニューを選択
		if (_game.m_trigger_key[i] & PAD_INPUT_UP)
		{
			m_menu_state--;
			//一番上のメニューから一番下のメニューへ循環
			if (pre_state == BATTLE)
				m_menu_state = CREDIT;

			//点滅エフェクト用にフレームを記録
			m_press_frame = GetModeCount();

			PlaySE("resource/se/menu_select.wav", 1.0f, _game);
		}
		if (_game.m_trigger_key[i] & PAD_INPUT_DOWN)
		{
			m_menu_state++;
			//一番下のメニューから一番上のメニューへ循環
			if (pre_state == CREDIT)
				m_menu_state = BATTLE;

			//点滅エフェクト用にフレームを記録
			m_press_frame = GetModeCount();

			PlaySE("resource/se/menu_select.wav", 1.0f, _game);
		}

		//Bボタンでタイトルモードへ戻る
		if ((_game.m_trigger_key[i] & PAD_INPUT_2) &&
			m_selected_flag == false)
		{
			PlaySE("resource/se/cancel.wav", 0.9f, _game);

			ModeOverlay* modeoverlay = new ModeOverlay();
			modeoverlay->Fade(120, FADE_OUT);
			_game.m_modeserver->Add(modeoverlay, 0, "Overlay");

			m_press_count = 120;
			m_menu_state = BACKTITLE;
			m_selected_flag = true;
		}
	}
}

void ModeMainMenu::State(Game& _game)
{
	switch (m_menu_state)
	{
	case BATTLE:
		Battle(_game);
		break;
	case TUTORIAL:
		Tutorial(_game);
		break;
	case EXIT:
		Exit(_game);
		break;
	case CREDIT:
		Credit(_game);
		break;
	}
}

void ModeMainMenu::Battle(Game& _game)
{
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		//Aボタンでバトルメニューへ移行
		if ((_game.m_trigger_key[i] & PAD_INPUT_1) &&
			m_selected_flag == false)
		{
			PlaySE("resource/se/title.wav", 1.0f, _game);

			ModeOverlay* modeoverlay = new ModeOverlay();
			modeoverlay->Fade(120, FADE_OUT);
			_game.m_modeserver->Add(modeoverlay, 0, "Overlay");

			m_press_count = 120;
			m_selected_flag = true;
		}
	}
}

void ModeMainMenu::Tutorial(Game& _game)
{
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		//Aボタンでチュートリアル画面を表示
		if ((_game.m_trigger_key[i] & PAD_INPUT_1) &&
			m_selected_flag == false)
		{
			PlaySE("resource/se/title.wav", 1.0f, _game);

			ModeOverlay* modeoverlay = new ModeOverlay();
			modeoverlay->Capture(60);
			_game.m_modeserver->Add(modeoverlay, 1, "Overlay");

			ModeTutorial* modetutorial = new ModeTutorial();
			_game.m_modeserver->Add(modetutorial, 0, "Tutorial");

			m_press_count = 120;
			m_selected_flag = true;
		}
	}
}

void ModeMainMenu::Exit(Game& _game)
{
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		//Aボタンでゲームを終了
		if ((_game.m_trigger_key[i] & PAD_INPUT_1) &&
			m_selected_flag == false)
		{
			PlaySE("resource/se/menu_select.wav", 0.9f, _game);

			_game.m_bgm.Fade(0.0f, 1.5f);

			ModeOverlay* modeoverlay = new ModeOverlay();
			modeoverlay->Fade(120, FADE_OUT);
			_game.m_modeserver->Add(modeoverlay, 0, "Overlay");

			m_press_count = 120;
			m_selected_flag = true;
		}
	}
}

void ModeMainMenu::Credit(Game& _game)
{
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		//Aボタンでクレジット画面を表示
		if ((_game.m_trigger_key[i] & PAD_INPUT_1) &&
			m_selected_flag == false)
		{
			PlaySE("resource/se/title.wav", 1.0f, _game);

			ModeOverlay* modeoverlay = new ModeOverlay();
			modeoverlay->Capture(60);
			_game.m_modeserver->Add(modeoverlay, 1, "Overlay");

			ModeCredit* modecredit = new ModeCredit();
			_game.m_modeserver->Add(modecredit, 0, "Credit");

			m_press_count = 120;
			m_selected_flag = true;
		}
	}
}

void ModeMainMenu::NextMode(Game& _game)
{
	//ボタンが押されてから指定秒数経過後に、指定された画面遷移を行う
	if (m_press_count == 0)
	{
		if (m_menu_state == BATTLE)
		{
			ModeSelectChara* modeselect = new ModeSelectChara(NARI1, NONAME1, true);
			_game.m_modeserver->Add(modeselect, 0, "ModeSelectChara");
		}
		if (m_menu_state == TUTORIAL)
		{
			_game.m_modeserver->Del(this);
		}
		if (m_menu_state == EXIT)
		{
			_game.SetExitFlag(true);
		}
		if (m_menu_state == CREDIT)
		{
			_game.m_modeserver->Del(this);
		}
		if (m_menu_state == BACKTITLE)
		{
			ModeTitle* modetitle = new ModeTitle();
			_game.m_modeserver->Add(modetitle, 0, "Title");
		}
		_game.m_modeserver->Del(this);
	}
}

bool ModeMainMenu::Draw(Game& _game)
{
	ModeBase::Draw(_game);

	DrawGraph(0, 0, m_background_graph, FALSE);

	for (int i = 0; i < 4; i++)
	{
		//選択されたメニュー項目は点滅
		if (m_menu_state == i)
		{
			if (m_selected_flag == false)
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(abs(255 * sin(3.14f / 180 * 2.125f * (GetModeCount() - m_press_frame)))));//85bpmで点滅
			else
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(abs(255 * sin(3.14f / 180 * 10 * GetModeCount()))));
		}

		//メニュー項目を描画
		if (i == BATTLE)
			DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 1 / 2 - static_cast<int>(m_height * 1.3), 1.0, 0, m_battle_graph, TRUE);
		if (i == TUTORIAL)
			DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 1 / 2, 1.0, 0, m_tutorial_graph, TRUE);
		if (i == EXIT)
			DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 1 / 2 + static_cast<int>(m_height * 1.3), 1.0, 0, m_exit_graph, TRUE);
		if (i == CREDIT)
			DrawRotaGraph(SCREEN_WIDTH - 125, SCREEN_HEIGHT - 50, 1.0, 0, m_credit_graph, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	return true;
}

void ModeMainMenu::PlayBGM(Game& _game)
{
	if (m_playbgm_flag)
	{
		_game.m_bgm.Load("resource/bgm/Reflect.wav");
		_game.m_bgm.SetVolume(1.0f);
		_game.m_bgm.SetLoopCount(XAUDIO2_LOOP_INFINITE);
		_game.m_bgm.PlayBackGroundWithLoop(_game.m_bgm, 24.0f, 170.823f);
		m_freq = 100.0f;
		_game.m_bgm.LowPassFilter(m_freq);
	}
}

void ModeMainMenu::PlaySE(const char* _filename, const float _pitch, Game& _game)
{
	_game.m_se.Load(_filename);
	_game.m_se.SetVolume(SE_VOLUME);
	_game.m_se.Pitch(_pitch);
	_game.m_se.PlayBackGround(_game.m_se);
}