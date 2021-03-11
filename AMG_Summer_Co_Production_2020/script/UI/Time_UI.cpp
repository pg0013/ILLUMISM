/**
 * @file	AMG_Summer_Co_Production_2020\script\Time_UI.cpp.
 *
 * @brief	ゲームモードのプレイ時間を表示
 */

#include "Time_UI.h"
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#include"../Mode/ModeScoreBonus.h"
#include"../Mode/ModeOverlay.h"
using namespace illumism;

Time_UI::Time_UI()
{
	Init();
}

Time_UI::~Time_UI()
{
}

void Time_UI::Init()
{
	ResourceServer::LoadDivGraph("resource/ingameUI/time_number.png", 11, 11, 1, 242 / 11, 36, m_graph);
	m_frame_graph = ResourceServer::LoadGraph("resource/ingameUI/time_frame.png");

	m_width = 451 / 11;
	m_height = 36;

	m_x = SCREEN_WIDTH - static_cast<int>(m_width * 4.5);
	m_y = 10;

	m_GameTime = GAMETIME;

	m_minutes = 0;
	m_second = 0;

	onceflag = true;
}

void Time_UI::Process(Game& _game)
{
	ObjectBase::Process(_game);

	ModeGame* modegame = (ModeGame*)_game.m_modeserver->Get("Game");
	m_now_time = modegame->GetModeCount() - START_TIME;

	//ゲーム開始時の操作出来ない時間は試合時間を固定表示
	if (m_now_time < 0)
	{
		m_GameTime = GAMETIME;
		m_minutes = m_GameTime / 3600;
		m_second = (m_GameTime % 3600) / 60;
		return;
	}

	GenerateBOSS(_game);

	//ゲーム時間を更新
	if (m_GameTime > 0)
	{
		m_GameTime = GAMETIME - m_now_time;
		m_minutes = (m_GameTime + 60) / 3600;
		m_second = (m_GameTime % 3600) / 60;
	}
	else
	{
		m_GameTime = GAMETIME - m_now_time;
		m_minutes = 0;
		m_second = 0;

		if (m_GameTime == -150)
		{
			ModeOverlay* modeoverlay = new ModeOverlay();
			modeoverlay->Fade(151, 1);
			_game.m_modeserver->Add(modeoverlay, 99, "Overlay");
		}
		if (m_GameTime == -300)
		{
			_game.m_bgm.Pause();
			_game.m_objectserver.Clear();

			ModeScoreBonus* modescorebonus = new ModeScoreBonus(
				modegame->GetPlayerPoint(1), modegame->GetPlayerPoint(2),
				modegame->GetPlayerCharactor(1), modegame->GetPlayerCharactor(2),
				modegame->GetBonusParam(1), modegame->GetBonusParam(2));
			_game.m_modeserver->Add(modescorebonus, 0, "ScoreBonus");

			_game.m_modeserver->Del(_game.m_modeserver->Get("Game"));
			return;
		}
	}
}

void Time_UI::Draw(Game& _game)
{
	int onerank, tenrank;

	//秒未満が表示されないため、ゲーム最後の0秒以上、1秒未満のときに0秒と表示されてしまう
	// そのため1秒時間表示では多く表示する
	auto check_tenrank = [](int _second)->int
	{
		_second++;
		//60秒と表示されてしまうので十の位を0に設定
		if (_second/10 == 6) { return 0; }
		return _second / 10;
	};
	tenrank = check_tenrank(m_second);

	auto check_onerank = [](int _second,int _gametime)->int
	{
		//ゲーム終了時には0秒と表示
		if (_gametime <= 0) { return 0; }
		_second++;
		//9秒のときに一の位が10と設定されてしまうので一の位は0に設定
		if (_second == 10) { return 0; }
		return _second;
	};
	onerank = check_onerank(m_second % 10, m_GameTime);

	DrawGraph(m_x + 30, m_y + 10, m_frame_graph, TRUE);
	DrawGraph(m_x + static_cast<int>(m_width * 1.6), m_y + 20, m_graph[m_minutes], TRUE);
	DrawGraph(m_x + static_cast<int>(m_width * 2.0), m_y + 15, m_graph[10], TRUE);
	DrawGraph(m_x + static_cast<int>(m_width * 2.4), m_y + 20, m_graph[tenrank], TRUE);
	DrawGraph(m_x + static_cast<int>(m_width * 2.9), m_y + 20, m_graph[onerank], TRUE);
}

void Time_UI::GenerateBOSS(Game& _game)
{
	//ボス生成時間
	if (m_GameTime != BOSSTIME)
		return;

	//60フレーム生成されないために1度だけ処理を行う
	if (onceflag == false)
		return;

	ObjectBase* BOSS = new ::BOSS();
	_game.m_objectserver.Insert(BOSS);
	onceflag = false;
}