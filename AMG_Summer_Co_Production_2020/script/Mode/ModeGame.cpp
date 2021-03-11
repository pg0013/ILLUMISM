/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeGame.cpp
 *
 * @brief	ゲームモード
 */

#include "ModeGame.h"
#include"../UI/GameSign.h"
#include"ModeOverlay.h"
#include"Dxlib.h"
#include"../Game.h"
using namespace illumism;

ModeGame::ModeGame(const int _P1charactor, const int _P2charactor)
{
	m_player_charactor[0] = _P1charactor;
	m_player_charactor[1] = _P2charactor;

	m_vignette_graph = ResourceServer::LoadGraph("resource/ingame/vignette.png");
}

bool ModeGame::Initialize(Game& _game)
{
	if (!ModeBase::Initialize(_game)) { return false; }

	//画面をフェードイン
	ModeOverlay* modeoverlay = new ModeOverlay();
	modeoverlay->Fade(30, FADE_IN);
	_game.m_modeserver->Add(modeoverlay, 0, "Overlay");

	//2人の操作プレイヤーを追加
	ObjectBase* Player1 = new Player(DX_INPUT_PAD1, m_player_charactor[0]);
	ObjectBase* Player2 = new Player(DX_INPUT_PAD2, m_player_charactor[1]);
	_game.m_objectserver.Add(Player1);
	_game.m_objectserver.Add(Player2);

	//BGMの再生
	_game.m_bgm.Load("resource/bgm/Noesis.wav");
	_game.m_bgm.SetVolume(0.4f);
	_game.m_bgm.SetLoopCount(0);
	_game.m_bgm.PlayBackGround(_game.m_bgm);

	m_stopObjProcess = false;

	return true;
}

bool ModeGame::Terminate(Game& _game)
{
	ModeBase::Terminate(_game);

	_game.m_objectserver.Clear();

	return true;
}

bool ModeGame::Process(Game& _game)
{
	ModeBase::Process(_game);

	DrawGameCount(_game);
	DrawGameSign(_game);

	if (m_stopObjProcess == false)
	{
		_game.m_objectserver.Process(_game);
		m_touch_object_controller.Process(_game);
		m_spotlight_controller.Process(_game);
		m_coopmove_controller.Process(_game);
		m_gameUI_controller.Process(_game);
	}
	m_timeUI.Process(_game);
	m_camera.Process(_game);


	//ゲーム時間終了時に画面の動きを止める
	if (GetModeCount() == START_TIME + GAMETIME)
		m_stopObjProcess = true;

	return true;
}

bool ModeGame::Draw(Game& _game)
{
	ModeBase::Draw(_game);

	m_background.Draw(_game);
	_game.m_objectserver.Draw(_game);
	m_background.DrawAudience(_game);
	DrawGraph(-240 - m_camera.GetScreenX(), -160, m_vignette_graph, TRUE);
	m_gameUI_controller.Draw(_game);
	m_timeUI.Draw(_game);

	return true;
}

void ModeGame::SetPlayerPoint(const int _player_num, const int _player_point)
{
	m_player_point[_player_num - 1] = _player_point;
}

void ModeGame::DrawGameSign(Game& _game)
{
	//READY？を表示
	if (GetModeCount() == 1)
	{
		GameSign* ready = new GameSign("resource/ingame/ready.png", READY_pos_x, READY_pos_y, 90);
		_game.m_objectserver.Add(ready);
	}
	//FIGHT!!を表示
	if (GetModeCount() == 120)
	{
		GameSign* fight = new GameSign("resource/ingame/fight.png", FIGHT_pos_x, FIGHT_pos_y, 60);
		_game.m_objectserver.Add(fight);
	}
	//FINISH!!を表示
	if (GetModeCount() == START_TIME + GAMETIME)
	{
		GameSign* finish = new GameSign("resource/ingame/finish.png",
			FINISH_pos_x, FINISH_pos_y, 90);
		_game.m_objectserver.Add(finish);
	}
}

void ModeGame::DrawGameCount(Game& _game)
{
	GenerateGameCount("resource/ingame/10.png", 10, _game);
	GenerateGameCount("resource/ingame/9.png", 9, _game);
	GenerateGameCount("resource/ingame/8.png", 8, _game);
	GenerateGameCount("resource/ingame/7.png", 7, _game);
	GenerateGameCount("resource/ingame/6.png", 6, _game);
	GenerateGameCount("resource/ingame/5.png", 5, _game);
	GenerateGameCount("resource/ingame/4.png", 4, _game);
	GenerateGameCount("resource/ingame/3.png", 3, _game);
	GenerateGameCount("resource/ingame/2.png", 2, _game);
	GenerateGameCount("resource/ingame/1.png", 1, _game);
}

void ModeGame::GenerateGameCount(const char* _filename, const int _count, Game& _game)
{
	if (GetModeCount() == START_TIME + GAMETIME - _count * 60)
	{
		GameSign* count = new GameSign(_filename, COUNT_pos_x, COUNT_pos_y, 60);
		_game.m_objectserver.Add(count);
	}
}