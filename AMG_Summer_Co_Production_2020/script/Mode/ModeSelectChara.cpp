/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeSelectChara.cpp.
 *
 * @brief	プレイキャラクター選択モード
 */

#include "ModeSelectChara.h"
#include "DxLib.h"
#include "ModeGame.h"
#include"ModeMainMenu.h"
#include"ModeOperation.h"
#include"ModeOverlay.h"
#include"../Server/ResourceServer.h"
#include"../Game.h"
using namespace illumism;

ModeSelectChara::ModeSelectChara(int _p1, int _p2, bool _startEQ)
{
	m_selectchara_state[0] = _p1;
	m_selectchara_state[1] = _p2;
	m_startEQ_flag = _startEQ;

	Init();
}

void ModeSelectChara::Init()
{
	m_background_graph = ResourceServer::LoadGraph("resource/selectchara/bg_select_1.jpg");
	m_charactor_graph[0] = ResourceServer::LoadGraph("resource/selectchara/nari1.png");
	m_charactor_graph[1] = ResourceServer::LoadGraph("resource/selectchara/noname1.png");
	m_charactor_graph[2] = ResourceServer::LoadGraph("resource/selectchara/nari2.png");
	m_charactor_graph[3] = ResourceServer::LoadGraph("resource/selectchara/noname2.png");
	m_exit_graph[0] = ResourceServer::LoadGraph("resource/selectchara/ui_select_exit(2).png");
	m_exit_graph[1] = ResourceServer::LoadGraph("resource/selectchara/ui_select_exit.png");
	m_operation_graph[0] = ResourceServer::LoadGraph("resource/selectchara/ui_select_tut(2).png");
	m_operation_graph[1] = ResourceServer::LoadGraph("resource/selectchara/ui_select_tut.png");
	m_select_under_graph = ResourceServer::LoadGraph("resource/selectchara/ui_select_under.png");
	m_select_arrow_graph = ResourceServer::LoadGraph("resource/selectchara/ui_select_yazi.png");
	m_light_select_back_graph = ResourceServer::LoadGraph("resource/selectchara/light_select_effect.png");
	m_light_select_graph[0] = ResourceServer::LoadGraph("resource/selectchara/light_select_p1.png");
	m_light_select_graph[1] = ResourceServer::LoadGraph("resource/selectchara/light_select_p2.png");
	m_light_ready_graph = ResourceServer::LoadGraph("resource/selectchara/ui_select_readylight.png");
	m_ready_graph = ResourceServer::LoadGraph("resource/selectchara/ui_select_ready.png");
	GetGraphSize(m_charactor_graph[0], &m_width, &m_height);

	m_freq = 100.0f;
	m_menu_state = SELECT;

	m_once_flag = false;
	m_exit_flag = false;
	m_gogame_flag = false;
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
		m_ready_flag[i] = false;

	m_press_count = -1;
	m_press_frame = 0;
}

bool ModeSelectChara::Initialize(Game& _game)
{
	if (!ModeBase::Initialize(_game)) { return false; }

	//メインメニューモードからの遷移する場合のみ
	//ローパスフィルタを解除すると音量が上がるのでフェードを行う
	if (m_startEQ_flag)
		_game.m_bgm.Fade(0.5f, 3.0f);

	ModeOverlay* modeoverlay = new ModeOverlay();
	modeoverlay->Fade(120, FADE_IN);
	_game.m_modeserver->Add(modeoverlay, 0, "Overlay");

	return true;
}

bool ModeSelectChara::Terminate(Game& _game)
{
	ModeBase::Terminate(_game);

	return true;
}

bool ModeSelectChara::Process(Game& _game)
{
	ModeBase::Process(_game);
	m_press_count--;

	EQFade(_game);

	//終了中は操作を受け付けない
	if (m_exit_flag == false)
		Input(_game);

	State(_game);

	return true;
}

bool ModeSelectChara::Draw(Game& _game)
{
	ModeBase::Draw(_game);

	DrawGraph(0, 0, m_background_graph, FALSE);

	DrawOperationButton();
	DrawExitButton();

	SelectCharaAnim();

	DrawSelectArrow();
	DrawSelectLight();

	DrawReadySign();

	DrawGraph(0, SCREEN_HEIGHT - 122, m_select_under_graph, TRUE);

	return true;
}

void ModeSelectChara::EQFade(Game& _game)
{
	//モード開始時にローパスフィルタを解除する
	if (GetModeCount() > 0 && GetModeCount() <= 90 && m_startEQ_flag)
	{
		m_freq += 10.0f;
		_game.m_bgm.LowPassFilter(m_freq);
	}
	if (GetModeCount() > 90 && GetModeCount() <= 180 && m_startEQ_flag)
	{
		m_freq += (7350.0f - 1000.0f) / 90.0f;
		_game.m_bgm.LowPassFilter(m_freq);
	}

	//メインメニューモード移行時にフォーパスフィルターをかける
	if (m_press_count > 0 && m_exit_flag == true)
	{
		m_freq -= (7350.0f - 100.0f) / 120.0f;
		if (m_freq < 100.0f)
			m_freq = 100.0f;

		_game.m_bgm.LowPassFilter(m_freq);
	}
}

void ModeSelectChara::Input(Game& _game)
{
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		int pre_state[GAME_PLAYER_NUM];
		pre_state[i] = m_selectchara_state[i];

		//左右入力でキャラ選択
		if (_game.m_trigger_key[i] & PAD_INPUT_LEFT && m_ready_flag[i] == false)
		{
			PlaySE("resource/se/selectchara.wav", 1.0f, _game);

			if (pre_state[i] == NARI1)
				m_selectchara_state[i] = NONAME1;
			else if (pre_state[i] == NONAME1)
				m_selectchara_state[i] = NARI1;

			m_anim_count[i] = 30;
			m_direction[i] = LEFT;
		}
		if (_game.m_trigger_key[i] & PAD_INPUT_RIGHT && m_ready_flag[i] == false)
		{
			PlaySE("resource/se/selectchara.wav", 1.0f, _game);

			if (pre_state[i] == NARI1)
				m_selectchara_state[i] = NONAME1;
			else if (pre_state[i] == NONAME1)
				m_selectchara_state[i] = NARI1;

			m_anim_count[i] = 30;
			m_direction[i] = RIGHT;
		}

		//Yボタン
		if (_game.m_trigger_key[i] & PAD_INPUT_4 && m_once_flag == false)
		{
			PlaySE("resource/se/menu_select.wav", 1.0f, _game, sound::PAN_RIGHT);

			m_menu_state = OPERATION;
			m_press_count = 60;
			m_once_flag = true;
		}

		//Aボタン
		if (_game.m_trigger_key[i] & PAD_INPUT_1 && m_once_flag == false)
		{
			if (m_ready_flag[i] == false)
				PlaySE("resource/se/menu_select.wav", 1.0f, _game);

			m_ready_flag[i] = true;

			//最後のプレイヤーが選択キャラを決めたらREADYへ移行
			if (m_ready_flag[0] == true && m_ready_flag[1] == true)
			{
				m_menu_state = READY;
				m_once_flag = true;
				m_press_frame = GetModeCount();
			}
		}

		//キャンセル
		if (_game.m_trigger_key[i] & PAD_INPUT_2 && m_ready_flag[i] == true)
		{
			PlaySE("resource/se/cancel.wav", 0.9f, _game);

			//キャラクター選択のキャンセル
			m_ready_flag[i] = false;

			//READY状態のキャンセル
			if (m_menu_state == READY)
			{
				m_ready_flag[i] = false;
				m_once_flag = false;
				m_menu_state = CANSEL;
				m_press_frame = GetModeCount();
			}
		}

		//Bボタン長押し
		if (_game.m_gkey[i] & PAD_INPUT_2 && m_once_flag == false)
		{
			m_cancel_count[i]++;

			if (m_cancel_count[i] > 90.0f)
			{
				m_menu_state = EXIT;
				m_once_flag = true;
			}
		}
		else
		{
			m_cancel_count[i] = 0;
		}
	}
}

void ModeSelectChara::State(Game& _game)
{
	switch (m_menu_state)
	{
	case SELECT:
		break;
	case EXIT:
		Exit(_game);
		break;
	case OPERATION:
		Operation(_game);
		break;
	case READY:
		Ready(_game);
		break;
	}
}

void ModeSelectChara::Exit(Game& _game)
{
	if (!m_exit_flag)
	{
		PlaySE("resource/se/cancel.wav", 1.0f, _game, sound::PAN_LEFT);

		ModeOverlay* modeoverlay = new ModeOverlay();
		modeoverlay->Fade(120, FADE_OUT);
		_game.m_modeserver->Add(modeoverlay, 0, "Overlay");

		m_press_count = 120;
		m_exit_flag = true;
	}

	if (m_press_count == 60 && m_exit_flag == true)
	{
		_game.m_bgm.Fade(1.0f, 1.0f);
	}

	if (m_press_count == 0 && m_exit_flag == true)
	{
		ModeMainMenu* modemenu = new ModeMainMenu(ModeMainMenu::BATTLE, false);
		_game.m_modeserver->Add(modemenu, 0, "MainMenu");
		_game.m_modeserver->Del(this);
	}
}

void ModeSelectChara::Operation(Game& _game)
{
	if (m_press_count == 30 && m_once_flag == true)
	{
		ModeOverlay* modeoverlay = new ModeOverlay();
		modeoverlay->Capture(30);
		_game.m_modeserver->Add(modeoverlay, 1, "Overlay");

		ModeOperation* modeoperation = new ModeOperation(m_selectchara_state[0], m_selectchara_state[1]);
		_game.m_modeserver->Add(modeoperation, 0, "Operation");
	}

	if (m_press_count == 0 && m_once_flag == true)
	{
		_game.m_modeserver->Del(this);
	}
}

void ModeSelectChara::Ready(Game& _game)
{
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		//STARTボタンでゲームモードへ移行
		if (_game.m_trigger_key[i] & PAD_INPUT_8 && m_gogame_flag == false)
		{
			PlaySE("resource/se/start.wav", 1.0f, _game);

			ModeOverlay* modeoverlay = new ModeOverlay();
			modeoverlay->Fade(121, FADE_OUT);
			_game.m_bgm.Fade(0.0f, 2.0f);
			_game.m_modeserver->Add(modeoverlay, 0, "Overlay");

			m_press_count = 120;
			m_gogame_flag = true;
		}
	}

	if (m_press_count == 0 && m_gogame_flag == true)
	{
		_game.m_bgm.Pause();
		_game.m_modeserver->Del(this);
		SelectAutoChara();
		ModeGame* modegame = new ModeGame(m_selectchara_state[0], m_selectchara_state[1]);
		_game.m_modeserver->Add(modegame, 0, "Game");
	}
}

void ModeSelectChara::DrawOperationButton()
{
	//85bpmで点滅
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(abs(255 * sin(3.14f / 180 * 2.125f * GetModeCount()))));

	//操作説明
	if (m_menu_state == OPERATION)
		DrawGraph(SCREEN_WIDTH - 505, -50, m_operation_graph[1], TRUE);
	else
		DrawGraph(SCREEN_WIDTH - 505, -50, m_operation_graph[0], TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void ModeSelectChara::DrawExitButton()
{
	//85bpmで点滅
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(abs(255 * sin(3.14f / 180 * 2.125f * GetModeCount()))));

	DrawGraph(0, 0, m_exit_graph[0], TRUE);

	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		if (m_cancel_count[i] > 0)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255.0f * m_cancel_count[i] / 90.0f));

			int width, height;
			GetGraphSize(m_exit_graph[1], &width, &height);

			SetDrawArea(0, 0, static_cast<int>(width * m_cancel_count[i] / 90.0f), height);
			DrawGraph(0, 0, m_exit_graph[1], TRUE);
			SetDrawArea(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void ModeSelectChara::SelectCharaAnim()
{
	//選択されたキャラポスターを描画
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		if (m_selectchara_state[i] == NARI1)
			DrawRotaGraph(SCREEN_WIDTH * (3 + 4 * i) / 10, SCREEN_HEIGHT / 2, 1.0, 0.0, m_charactor_graph[0], FALSE);
		if (m_selectchara_state[i] == NONAME1)
			DrawRotaGraph(SCREEN_WIDTH * (3 + 4 * i) / 10, SCREEN_HEIGHT / 2, 1.0, 0.0, m_charactor_graph[1], FALSE);
	}

	int width, height;
	GetGraphSize(m_charactor_graph[0], &width, &height);

	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		if (m_anim_count[i] < 0) { m_anim_count[i] = 0; }
		m_anim_count[i]--;

		//描画域をポスターの大きさに指定
		SetDrawArea(SCREEN_WIDTH * (3 + 4 * i) / 10 - width / 2, SCREEN_HEIGHT / 2 - height / 2, SCREEN_WIDTH * (3 + 4 * i) / 10 + width / 2 + 1, SCREEN_HEIGHT / 2 + height / 2);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(400 * (m_anim_count[i] / 30.0f)));

		//選択されていたキャラポスターを入力方向に移動させる
		if (m_selectchara_state[i] == NARI1)
		{
			DrawRotaGraph(SCREEN_WIDTH * (3 + 4 * i) / 10 + m_direction[i] * static_cast<int>(width - width * m_anim_count[i] / 30.0f), SCREEN_HEIGHT / 2, 1.0, 0.0, m_charactor_graph[1], FALSE);
		}
		if (m_selectchara_state[i] == NONAME1)
		{
			DrawRotaGraph(SCREEN_WIDTH * (3 + 4 * i) / 10 + m_direction[i] * static_cast<int>(width - width * m_anim_count[i] / 30.0f), SCREEN_HEIGHT / 2, 1.0, 0.0, m_charactor_graph[0], FALSE);
		}

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawArea(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}

}

void ModeSelectChara::DrawSelectArrow()
{
	//PLAYER1の矢印
	if (m_ready_flag[0] == false)
	{
		DrawRotaGraph(-50 - static_cast<int>(m_width / 2 + SCREEN_WIDTH * 3 / 10 - abs(10 * sin(3.14f / 180 * 2.125f * GetModeCount()))), SCREEN_HEIGHT / 2, 1.0, 0.0, m_select_arrow_graph, TRUE);
		DrawRotaGraph(50 + static_cast<int>(m_width / 2 + SCREEN_WIDTH * 3 / 10 + abs(10 * sin(3.14f / 180 * 2.125f * GetModeCount()))), SCREEN_HEIGHT / 2, 1.0, 0.0, m_select_arrow_graph, TRUE, TRUE);
	}
	//PLAYER2の矢印
	if (m_ready_flag[1] == false)
	{
		DrawRotaGraph(-50 - static_cast<int>(m_width / 2 + SCREEN_WIDTH * 7 / 10 - abs(10 * sin(3.14f / 180 * 2.125f * GetModeCount()))), SCREEN_HEIGHT / 2, 1.0, 0.0, m_select_arrow_graph, TRUE);
		DrawRotaGraph(50 + static_cast<int>(m_width / 2 + SCREEN_WIDTH * 7 / 10 + abs(10 * sin(3.14f / 180 * 2.125f * GetModeCount()))), SCREEN_HEIGHT / 2, 1.0, 0.0, m_select_arrow_graph, TRUE, TRUE);
	}
}

void ModeSelectChara::DrawSelectLight()
{
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		if (m_ready_flag[i])
		{
			SetDrawBlendMode(DX_BLENDMODE_ADD, 64 + static_cast<int>(abs(64 * sin(3.14f / 180 * 2.125f / 2.0f * GetModeCount()))));
			DrawRotaGraph(SCREEN_WIDTH * (3 + 4 * i) / 10, 855, 1.0, 0.0, m_light_select_graph[i], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
	}
}

void ModeSelectChara::DrawReadySign()
{
	if (m_menu_state == READY)
	{
		//フェードイン
		int alpha = 6 * (GetModeCount() - m_press_frame);
		if (alpha > 255) { alpha = 255; }
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0, 0.0, m_ready_graph, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	else if (m_menu_state == CANSEL)
	{
		//フェードアウト
		int alpha = 6 * (GetModeCount() - m_press_frame);
		if (alpha > 255) { alpha = 255; }
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - alpha);
		DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0, 0.0, m_ready_graph, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}

void ModeSelectChara::SelectAutoChara()
{
	//キャラ被り時の色差分自動選択処理
	if ((m_selectchara_state[0] == NARI1 && m_selectchara_state[1] == NARI1) ||
		(m_selectchara_state[0] == NARI2 && m_selectchara_state[1] == NARI2) ||
		(m_selectchara_state[0] == NARI1 && m_selectchara_state[1] == NARI2) ||
		(m_selectchara_state[0] == NARI2 && m_selectchara_state[1] == NARI1))
	{
		m_selectchara_state[0] = NARI1; m_selectchara_state[1] = NARI2;
	}
	if ((m_selectchara_state[0] == NONAME1 && m_selectchara_state[1] == NONAME1) ||
		(m_selectchara_state[0] == NONAME2 && m_selectchara_state[1] == NONAME2) ||
		(m_selectchara_state[0] == NONAME1 && m_selectchara_state[1] == NONAME2) ||
		(m_selectchara_state[0] == NONAME2 && m_selectchara_state[1] == NONAME1))
	{
		m_selectchara_state[0] = NONAME1; m_selectchara_state[1] = NONAME2;
	}
}

void ModeSelectChara::PlaySE(const char* _filename, const float _pitch, Game& _game, const float _pan)
{
	_game.m_se.Load(_filename);
	_game.m_se.SetVolume(SE_VOLUME);
	_game.m_se.Pitch(_pitch);
	_game.m_se.Pan(_pan);
	_game.m_se.PlayBackGround(_game.m_se);
}