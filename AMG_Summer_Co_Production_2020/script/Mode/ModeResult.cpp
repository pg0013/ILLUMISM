/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeResult.cpp.
 *
 * @brief	リザルト画面表示モード
 */

#include "ModeResult.h"
#include "DxLib.h"
#include "ModeGame.h"
#include"ModeOverlay.h"
#include"ModeMainMenu.h"
#include"../Server/ResourceServer.h"
#include"../Game.h"
using namespace illumism;

ModeResult::ModeResult(const int _point1, const int _point2, const int _P1charactor, const int _P2charactor)
{
	m_player_charactor[0] = _P1charactor;
	m_player_charactor[1] = _P2charactor;

	m_player_point[0] = _point1;
	m_player_point[1] = _point2;
	m_result_point.SetPoint(1, _point1);
	m_result_point.SetPoint(2, _point2);
	m_result_point.SetPointRank();

	SelectCharactorGraph(_point1, _point2, _P1charactor, _P2charactor);

	Init();
}

void ModeResult::Init()
{
	m_backGround = ResourceServer::LoadGraph("resource/result/bg_result.jpg");
	m_num_graph[0] = ResourceServer::LoadGraph("resource/result/result_bana_p1.png");
	m_num_graph[1] = ResourceServer::LoadGraph("resource/result/result_bana_p2.png");

	m_winbanner_graph = ResourceServer::LoadGraph("resource/result/result_bana_win.png");
	m_losebanner_graph = ResourceServer::LoadGraph("resource/result/result_bana_lose.png");
	m_drawbanner_graph = ResourceServer::LoadGraph("resource/result/ui_result_draw.png");

	m_draw_graph = ResourceServer::LoadGraph("resource/result/draw.png");

	m_menu_graph[0] = ResourceServer::LoadGraph("resource/result/result_botan_menu(2).png");
	m_menu_graph[1] = ResourceServer::LoadGraph("resource/result/result_botan_menu.png");
	m_retry_graph[0] = ResourceServer::LoadGraph("resource/result/result_botan_retry(2).png");
	m_retry_graph[1] = ResourceServer::LoadGraph("resource/result/result_botan_retry.png");

	//画像幅分イージングでアニメーションするため、画像幅を取得しイージングパラメータを設定
	int banner_w, banner_h;
	GetGraphSize(m_winbanner_graph, &banner_w, &banner_h);
	int winner_w, winner_h;
	GetGraphSize(m_winner_graph, &winner_w, &winner_h);

	m_move_win.SetParam(true, 0, 60, 0, 0, 0, banner_w, "OutCubic");
	m_move_lose.SetParam(true, 60, 60, 0, 0, 0, banner_w, "OutCubic");
	m_move_winner.SetParam(true, 120, 60, 0, 0, 0, winner_w, "OutCubic");

	m_x = 0;
	m_y = 0;

	m_menu_state = RETRY;
	m_selected_flag = false;
	m_press_count = -1;
}

bool ModeResult::Initialize(Game& _game)
{
	if (!ModeBase::Initialize(_game)) { return false; }

	ModeOverlay* modeoverlay = new ModeOverlay();
	modeoverlay->Fade(30, FADE_IN);
	_game.m_modeserver->Add(modeoverlay, 0, "Overlay");

	//BGMの再生
	_game.m_bgm.Load("resource/bgm/Winner.wav");						//BGMを読み込み
	_game.m_bgm.SetVolume(0.4f);
	_game.m_bgm.SetLoopCount(XAUDIO2_LOOP_INFINITE);
	_game.m_bgm.PlayBackGround(_game.m_bgm);

	return true;
}

bool ModeResult::Terminate(Game& _game)
{
	ModeBase::Terminate(_game);

	return true;
}

bool ModeResult::Process(Game& _game)
{
	ModeBase::Process(_game);
	m_press_count--;

	//イージングアニメーション
	m_move_win.Update(GetModeCount());
	m_move_lose.Update(GetModeCount());
	m_move_winner.Update(GetModeCount());
	AnimationSE(_game);

	//アニメーション終了後に操作可能
	if (GetModeCount() > 200)
	{
		Input(_game);
		State(_game);
	}

	return true;
}

void ModeResult::Input(Game& _game)
{
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		//左右選択でMENUかRETRYか選ぶ
		if (_game.m_trigger_key[i] & PAD_INPUT_LEFT && m_selected_flag == false)
		{
			PlaySE("resource/se/menu_select.wav", 1.0f, _game);

			if (m_menu_state == RETRY)
				m_menu_state = MENU;
			else if (m_menu_state == MENU)
				m_menu_state = RETRY;
		}
		if (_game.m_trigger_key[i] & PAD_INPUT_RIGHT && m_selected_flag == false)
		{
			PlaySE("resource/se/menu_select.wav", 1.0f, _game);

			if (m_menu_state == RETRY)
				m_menu_state = MENU;
			else if (m_menu_state == MENU)
				m_menu_state = RETRY;
		}
	}
}

void ModeResult::State(Game& _game)
{
	switch (m_menu_state)
	{
	case RETRY:
		Retry(_game);
		break;
	case MENU:
		Menu(_game);
		break;
	}
}

void ModeResult::Retry(Game& _game)
{
	//Aボタンでゲームシーンへ移行する
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		if ((_game.m_trigger_key[i] & PAD_INPUT_1) &&
			m_selected_flag == false)
		{
			PlaySE("resource/se/menu_select.wav", 1.1f, _game);

			ModeOverlay* modeoverlay = new ModeOverlay();
			modeoverlay->Fade(120, FADE_OUT);
			_game.m_modeserver->Add(modeoverlay, 0, "Overlay");

			_game.m_bgm.Fade(0.0f, 2.0f);

			m_press_count = 120;
			m_selected_flag = true;
		}
	}

	if (m_press_count == 0)
	{
		ModeGame* modegame = new ModeGame(m_player_charactor[0], m_player_charactor[1]);
		_game.m_modeserver->Add(modegame, 0, "Game");
		_game.m_modeserver->Del(this);
	}
}

void ModeResult::Menu(Game& _game)
{
	//Aボタンでメインメニューモードへ移行する
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		if ((_game.m_trigger_key[i] & PAD_INPUT_1) &&
			m_selected_flag == false)
		{
			PlaySE("resource/se/menu_select.wav", 1.1f, _game);

			ModeOverlay* modeoverlay = new ModeOverlay();
			modeoverlay->Fade(120, FADE_OUT);
			_game.m_modeserver->Add(modeoverlay, 0, "Overlay");

			_game.m_bgm.Fade(0.0f, 2.0f);

			m_press_count = 120;
			m_selected_flag = true;
		}
	}

	if (m_press_count == 0)
	{
		_game.m_bgm.Pause();

		ModeMainMenu* modemenu = new ModeMainMenu(ModeMainMenu::BATTLE, TRUE);
		_game.m_modeserver->Add(modemenu, 0, "MainMenu");
		_game.m_modeserver->Del(this);
	}
}

bool ModeResult::Draw(Game& _game)
{
	ModeBase::Draw(_game);

	DrawGraph(0, 0, m_backGround, FALSE);

	DrawWinner();
	DrawBanner();
	m_result_point.Draw(m_player_point[0], m_player_point[1], _game);

	//アニメーション終了後に操作ボタンを表示
	if (GetModeCount() > 200)
		DrawButton();

	return true;
}

void ModeResult::DrawBanner()
{
	int banner_w, banner_h;
	GetGraphSize(m_winbanner_graph, &banner_w, &banner_h);
	m_draw_graph = ResourceServer::LoadGraph("resource/result/draw.png");

	int win_move_x = -banner_w + static_cast<int>(m_move_win.GetValue());
	int lose_move_x = -banner_w + static_cast<int>(m_move_lose.GetValue());

	//P1P2の位置を勝敗から設定、ドローの場合は上からP1P2の順
	if (m_player_point[0] > m_player_point[1])
		DrawGraph(pos_x_P1P2 + win_move_x, pos_y_P1P2_win, m_num_graph[0], TRUE);
	else if (m_player_point[1] > m_player_point[0])
		DrawGraph(pos_x_P1P2 + lose_move_x, pos_y_P1P2_lose, m_num_graph[0], TRUE);

	if (m_player_point[1] > m_player_point[0])
		DrawGraph(pos_x_P1P2 + win_move_x, pos_y_P1P2_win, m_num_graph[1], TRUE);
	else if (m_player_point[0] > m_player_point[1])
		DrawGraph(pos_x_P1P2 + lose_move_x, pos_y_P1P2_lose, m_num_graph[1], TRUE);

	if (m_player_point[0] == m_player_point[1])
	{
		DrawGraph(pos_x_P1P2 + win_move_x, pos_y_P1P2_win, m_num_graph[0], TRUE);
		DrawGraph(pos_x_P1P2 + lose_move_x, pos_y_P1P2_lose, m_num_graph[1], TRUE);
	}

	//バナーの種類を勝敗から決定
	if (m_player_point[0] == m_player_point[1])
	{
		DrawGraph(pos_x_banner + win_move_x, pos_y_banner_win, m_drawbanner_graph, TRUE);
		DrawGraph(pos_x_banner + lose_move_x, pos_y_banner_lose, m_drawbanner_graph, TRUE);
	}
	else
	{
		DrawGraph(pos_x_banner + win_move_x, pos_y_banner_win, m_winbanner_graph, TRUE);
		DrawGraph(pos_x_banner + lose_move_x, pos_y_banner_lose, m_losebanner_graph, TRUE);
	}


	//キャラクター名とキャラアイコンの表示位置を勝敗から決定
	if (m_player_point[0] > m_player_point[1])
	{
		DrawGraph(pos_x_charaname + win_move_x, pos_y_charaname_win, m_name_graph[0], TRUE);
		DrawGraph(pos_x_banner + win_move_x, pos_y_banner_win + 62, m_banner_icon_graph[0], TRUE);
	}
	else if (m_player_point[1] > m_player_point[0])
	{
		DrawGraph(pos_x_charaname + lose_move_x, pos_y_charaname_lose, m_name_graph[0], TRUE);
		DrawGraph(pos_x_banner + lose_move_x, pos_y_banner_lose + 63, m_banner_icon_graph[0], TRUE);
	}

	if (m_player_point[1] > m_player_point[0])
	{
		DrawGraph(pos_x_charaname + win_move_x, pos_y_charaname_win, m_name_graph[1], TRUE);
		DrawGraph(pos_x_banner + win_move_x, pos_y_banner_win + 62, m_banner_icon_graph[1], TRUE);
	}
	else if (m_player_point[0] > m_player_point[1])
	{
		DrawGraph(pos_x_charaname + lose_move_x, pos_y_charaname_lose, m_name_graph[1], TRUE);
		DrawGraph(pos_x_banner + lose_move_x, pos_y_banner_lose + 63, m_banner_icon_graph[1], TRUE);
	}

	if (m_player_point[0] == m_player_point[1])
	{
		DrawGraph(pos_x_charaname + win_move_x, pos_y_charaname_win, m_name_graph[0], TRUE);
		DrawGraph(pos_x_charaname + lose_move_x, pos_y_charaname_lose, m_name_graph[1], TRUE);
		DrawGraph(pos_x_banner + win_move_x, pos_y_banner_win + 62, m_banner_icon_graph[0], TRUE);
		DrawGraph(pos_x_banner + lose_move_x, pos_y_banner_lose + 63, m_banner_icon_graph[1], TRUE);
	}
}

void ModeResult::DrawWinner()
{
	int width, height;
	GetGraphSize(m_winner_graph, &width, &height);
	if (m_player_point[0] == m_player_point[1])
	{
		//ドローの場合は負け画像をそれぞれ表示
		int x1 = SCREEN_WIDTH - width / 2 + static_cast<int>(width - 0.9 * m_move_winner.GetValue());
		int x2 = SCREEN_WIDTH - width / 2 + static_cast<int>(width - 0.7 * m_move_winner.GetValue());
		DrawRotaGraph(x1, SCREEN_HEIGHT / 3, 1.0, 0.0, m_loser_graph, TRUE);
		DrawRotaGraph(x2, SCREEN_HEIGHT / 3, 1.0, 0.0, m_winner_graph, TRUE);
	}
	else
	{
		//勝敗がついた場合は勝者と敗者画像をそれぞれ表示
		int x = SCREEN_WIDTH - width / 2 + static_cast<int>(width - m_move_winner.GetValue());
		DrawRotaGraph(x, height / 2, 1.0, 0.0, m_loser_graph, TRUE);
		DrawRotaGraph(x, height / 2, 1.0, 0.0, m_winner_graph, TRUE);
	}

	//勝者アニメーション終了後に、右下にWIN画像を点滅表示
	if (GetModeCount() < 200)
		return;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(abs(255 * sin(3.14f / 180 * 2.125f / 2.0f * GetModeCount()))));
	GetGraphSize(m_winner_win_graph, &width, &height);
	DrawGraph(SCREEN_WIDTH - width, SCREEN_HEIGHT - height + 50, m_winner_win_graph, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void ModeResult::DrawButton()
{
	int margin = 25;
	//ボタンの下地を描画
	DrawGraph(0 + margin, SCREEN_HEIGHT - 132 - margin, m_retry_graph[0], TRUE);
	DrawGraph(380 + margin, SCREEN_HEIGHT - 132 - margin, m_menu_graph[0], TRUE);

	//選択されたボタンは点滅が目立つように描画する
	if (m_selected_flag == true)
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>((255 * sin(3.14f / 180 * 10 * GetModeCount()))));
	else
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(abs(255 * sin(3.14f / 180 * 2.125f * GetModeCount()))));

	if (m_menu_state == RETRY)
		DrawGraph(0 + margin, SCREEN_HEIGHT - 132 - margin, m_retry_graph[1], TRUE);
	if (m_menu_state == MENU)
		DrawGraph(380 + margin, SCREEN_HEIGHT - 132 - margin, m_menu_graph[1], TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void ModeResult::SelectCharactorGraph(const int _point1, const int _point2, const int _P1charactor, const int _P2charactor)
{
	int charatype[2] = { 0 };
	bool drawflag = false;
	if (_point1 > _point2)
	{
		charatype[0] = _P1charactor;//win
		charatype[1] = _P2charactor;//lose

	}
	else if (_point2 > _point1)
	{
		charatype[0] = _P2charactor;//win
		charatype[1] = _P1charactor;//lose
	}
	else
	{
		charatype[0] = _P1charactor;//win
		charatype[1] = _P2charactor;//lose
		drawflag = true;
	}

	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		//drawの場合はどちらも負け画像
		if (drawflag)
		{
			if (charatype[i] == NARI1)
			{
				if (i == 0)
					m_winner_graph = ResourceServer::LoadGraph("resource/result/result_c_nari1_lose.png");
				if (i == 1)
					m_loser_graph = ResourceServer::LoadGraph("resource/result/result_c_nari1_lose.png");
			}
			else if (charatype[i] == NARI2)
			{
				if (i == 0)
					m_winner_graph = ResourceServer::LoadGraph("resource/result/result_c_nari2_lose.png");
				if (i == 1)
					m_loser_graph = ResourceServer::LoadGraph("resource/result/result_c_nari2_lose.png");
			}
			else if (charatype[i] == NONAME1)
			{
				if (i == 0)
					m_winner_graph = ResourceServer::LoadGraph("resource/result/result_c_noname1_lose.png");
				if (i == 1)
					m_loser_graph = ResourceServer::LoadGraph("resource/result/result_c_noname1_lose.png");
			}
			else if (charatype[i] == NONAME2)
			{
				if (i == 0)
					m_winner_graph = ResourceServer::LoadGraph("resource/result/result_c_noname2_lose.png");
				if (i == 1)
					m_loser_graph = ResourceServer::LoadGraph("resource/result/result_c_noname2_lose.png");
			}

			m_winner_win_graph = ResourceServer::LoadGraph("resource/result/draw.png");//大きいドロー表示
			continue;
		}

		//winner
		if (charatype[0] == NARI1)
		{
			m_winner_graph = ResourceServer::LoadGraph("resource/result/result_c_nari1_win.png");
		}
		else if (charatype[0] == NARI2)
		{
			m_winner_graph = ResourceServer::LoadGraph("resource/result/result_c_nari2_win.png");
		}
		else if (charatype[0] == NONAME1)
		{
			m_winner_graph = ResourceServer::LoadGraph("resource/result/result_c_noname1_win.png");
		}
		else if (charatype[0] == NONAME2)
		{
			m_winner_graph = ResourceServer::LoadGraph("resource/result/result_c_noname2_win.png");
		}

		//loser
		if (charatype[1] == NARI1)
		{
			m_loser_graph = ResourceServer::LoadGraph("resource/result/result_c_nari1_lose.png");
		}
		else if (charatype[1] == NARI2)
		{
			m_loser_graph = ResourceServer::LoadGraph("resource/result/result_c_nari2_lose.png");
		}
		else if (charatype[1] == NONAME1)
		{
			m_loser_graph = ResourceServer::LoadGraph("resource/result/result_c_noname1_lose.png");
		}
		else if (charatype[1] == NONAME2)
		{
			m_loser_graph = ResourceServer::LoadGraph("resource/result/result_c_noname2_lose.png");
		}

		m_winner_win_graph = ResourceServer::LoadGraph("resource/result/ui_result_win.png");
	}

	//キャラクター名の選択
	if (_P1charactor == NARI1 || _P1charactor == NARI2)
	{
		m_name_graph[0] = ResourceServer::LoadGraph("resource/result/result_bana_nari.png");
		m_banner_icon_graph[0] = ResourceServer::LoadGraph("resource/result/result_bana_icon_1.png");
	}
	if (_P1charactor == NONAME1 || _P1charactor == NONAME2)
	{
		m_name_graph[0] = ResourceServer::LoadGraph("resource/result/result_bana_blue.png");
		m_banner_icon_graph[0] = ResourceServer::LoadGraph("resource/result/result_bana_icon_2.png");

	}
	if (_P2charactor == NARI1 || _P2charactor == NARI2)
	{
		m_name_graph[1] = ResourceServer::LoadGraph("resource/result/result_bana_nari.png");
		m_banner_icon_graph[1] = ResourceServer::LoadGraph("resource/result/result_bana_icon_1.png");
	}
	if (_P2charactor == NONAME1 || _P2charactor == NONAME2)
	{
		m_name_graph[1] = ResourceServer::LoadGraph("resource/result/result_bana_blue.png");
		m_banner_icon_graph[1] = ResourceServer::LoadGraph("resource/result/result_bana_icon_2.png");
	}
}

void ModeResult::AnimationSE(Game& _game)
{
	if (GetModeCount() == 60)
	{
		PlaySE("resource/se/menu_select.wav", 1.0f, _game);
	}
	if (GetModeCount() == 120)
	{
		PlaySE("resource/se/menu_select.wav", 1.0f, _game);
	}
	if (GetModeCount() == 200)
	{
		PlaySE("resource/se/title.wav", 1.0f, _game);
	}
}

void ModeResult::PlaySE(const char* _filename, const float _pitch, Game& _game)
{
	_game.m_se.Load(_filename);
	_game.m_se.SetVolume(SE_VOLUME);
	_game.m_se.Pitch(_pitch);
	_game.m_se.PlayBackGround(_game.m_se);
}