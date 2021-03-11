/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeScoreBonus.cpp.
 *
 * @brief	スコアボーナス表示モード
 */

#include "ModeScoreBonus.h"
#include "DxLib.h"
#include"ModeOverlay.h"
#include"ModeResult.h"
#include"../Server/ResourceServer.h"
using namespace illumism;

ModeScoreBonus::ModeScoreBonus(
	const int _point1, const int _point2,
	const int _P1charactor, const int _P2charactor,
	ModeGame::BONUS_PARAM _player1, ModeGame::BONUS_PARAM _player2)
{
	SetCharaGraph(_P1charactor, _P2charactor);

	m_player_point[0] = _point1;
	m_player_point[1] = _point2;

	m_bonus_param[0] = _player1;
	m_bonus_param[1] = _player2;

	AddBonusPoint();

	Init();
}

void ModeScoreBonus::Init()
{
	m_background_graph = ResourceServer::LoadGraph("resource/scorebonus/background_scorebonus.png");
	m_spotlight_graph = ResourceServer::LoadGraph("resource/object/spotlight_y_test.png");
	m_bg_bonus_graph = ResourceServer::LoadGraph("resource/scorebonus/bg_bonus_3.png");
	m_bonus_graph[0] = ResourceServer::LoadGraph("resource/scorebonus/ui_bonus_boss.png");
	m_bonus_graph[1] = ResourceServer::LoadGraph("resource/scorebonus/ui_bonus_combo.png");
	m_bonus_graph[2] = ResourceServer::LoadGraph("resource/scorebonus/ui_bonus_death.png");
	m_bonus_point_graph = ResourceServer::LoadGraph("resource/scorebonus/ui_bonus_100.png");

	m_boss_bonus = false;
	m_combo_bonus = false;
	m_death_bonus = false;
}

bool ModeScoreBonus::Initialize(Game& _game)
{
	if (!ModeBase::Initialize(_game)) { return false; }

	ModeOverlay* modeoverlay = new ModeOverlay();
	modeoverlay->Fade(30, FADE_IN);
	_game.m_modeserver->Add(modeoverlay, 0, "Overlay");

	return true;
}

bool ModeScoreBonus::Terminate(Game& _game)
{
	ModeBase::Terminate(_game);
	return true;

}

bool ModeScoreBonus::Process(Game& _game)
{
	ModeBase::Process(_game);

	if (GetModeCount() >= 80)
	{
		if (GetModeCount() == 80)
			PlaySE("resource/se/scorebonus.wav", 1.0f, _game);

		//ボーナス加算されていれば、ボーナスエフェクトを描画
		if (m_num_graph[0] != 0)
			bonuspoint1.Process(_game);

		m_boss_bonus = true;
	}
	if (GetModeCount() >= 160)
	{
		if (GetModeCount() == 160)
			PlaySE("resource/se/scorebonus.wav", 1.0f, _game);

		//ボーナス加算されていれば、ボーナスエフェクトを描画
		if (m_num_graph[1] != 0)
			bonuspoint2.Process(_game);

		m_combo_bonus = true;
	}
	if (GetModeCount() >= 240)
	{
		if (GetModeCount() == 240)
			PlaySE("resource/se/scorebonus.wav", 1.0f, _game);

		//ボーナス加算されていれば、ボーナスエフェクトを描画
		if (m_num_graph[2] != 0)
			bonuspoint3.Process(_game);

		m_death_bonus = true;
	}

	if (GetModeCount() == 350)
	{
		ModeOverlay* modeoverlay = new ModeOverlay();
		modeoverlay->Fade(30, FADE_OUT);
		_game.m_modeserver->Add(modeoverlay, 0, "Overlay");
	}

	if (GetModeCount() == 380)
	{
		ModeResult* moderesult = new ModeResult(
			m_player_point[0], m_player_point[1],
			m_player_charactor[0], m_player_charactor[1]);
		_game.m_modeserver->Add(moderesult, 0, "Result");
		_game.m_modeserver->Del(this);
	}

	return true;
}

bool ModeScoreBonus::Draw(Game& _game)
{
	ModeBase::Draw(_game);

	//背景を描画
	int width, height;
	GetGraphSize(m_background_graph, &width, &height);
	DrawGraph(-width / 2 + SCREEN_WIDTH / 2, -height / 2 + 100 + SCREEN_HEIGHT / 2 - 100, m_background_graph, TRUE);
	GetGraphSize(m_bg_bonus_graph, &width, &height);
	DrawRotaGraph(SCREEN_WIDTH / 2, height / 2 + 50, 1.0, 0.0, m_bg_bonus_graph, TRUE);

	DrawBonusSign(_game);
	DrawCharactor();
	DrawSpotlight();

	return true;
}

void ModeScoreBonus::DrawBonusSign(Game& _game)
{
	int margin = 100;

	//ボーナス名と加算プレイヤーを描画し、加算プレイヤーがいたらボーナス加算エフェクトを描画
	if (m_boss_bonus)
	{
		DrawGraph(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 4 + 0 * margin, m_bonus_graph[0], TRUE);
		DrawGraph(SCREEN_WIDTH * 2 / 3 - 20, SCREEN_HEIGHT / 4 + 0 * margin, m_num_graph[0], TRUE);

		if (m_num_graph[0] != 0)
			bonuspoint1.Draw(_game);
	}
	if (m_combo_bonus)
	{
		DrawGraph(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 4 + 1 * margin, m_bonus_graph[1], TRUE);
		DrawGraph(SCREEN_WIDTH * 2 / 3 - 20, SCREEN_HEIGHT / 4 + 1 * margin, m_num_graph[1], TRUE);

		if (m_num_graph[1] != 0)
			bonuspoint2.Draw(_game);
	}
	if (m_death_bonus)
	{
		DrawGraph(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 4 + 2 * margin, m_bonus_graph[2], TRUE);
		DrawGraph(SCREEN_WIDTH * 2 / 3 - 20, SCREEN_HEIGHT / 4 + 2 * margin, m_num_graph[2], TRUE);

		if (m_num_graph[2] != 0)
			bonuspoint3.Draw(_game);
	}
}

void ModeScoreBonus::DrawCharactor()
{
	int charamargin = 155;

	if (GetModeCount() >= 80 && GetModeCount() < 160)
	{
		//BOSSダメージボーナスを獲得者がいれば、アピールアニメーションを再生
		// いなければ二人とも待機アニメーションのまま
		if (m_num_graph[0] != 0)
		{
			if (m_bonus_param[0].BOSS_DAMAGE > m_bonus_param[1].BOSS_DAMAGE)
				DrawRotaGraph(SCREEN_WIDTH / 4, GROUND - charamargin, 1.0, 0.0, m_appealchara1_graph[GetModeCount() / 2 % 40], TRUE, TRUE);
			else if (m_bonus_param[1].BOSS_DAMAGE > m_bonus_param[0].BOSS_DAMAGE)
				DrawRotaGraph(SCREEN_WIDTH * 3 / 4, GROUND - charamargin, 1.0, 0.0, m_appealchara2_graph[GetModeCount() / 2 % 40], TRUE);
		}
		else
		{
			DrawRotaGraph(SCREEN_WIDTH / 4, GROUND - charamargin, 1.0, 0.0, m_charactor1_graph[GetModeCount() / 2 % 30], TRUE, TRUE);
			DrawRotaGraph(SCREEN_WIDTH * 3 / 4, GROUND - charamargin, 1.0, 0.0, m_charactor2_graph[GetModeCount() / 2 % 30], TRUE);
		}
	}
	else if (GetModeCount() >= 160 && GetModeCount() < 240)
	{
		//最大コンボボーナスを獲得者がいれば、アピールアニメーションを再生
		//いなければ二人とも待機アニメーションのまま
		if (m_num_graph[1] != 0)
		{
			if (m_bonus_param[0].MAX_COMBO > m_bonus_param[1].MAX_COMBO)
				DrawRotaGraph(SCREEN_WIDTH / 4, GROUND - charamargin, 1.0, 0.0, m_appealchara1_graph[GetModeCount() / 2 % 40], TRUE, TRUE);
			else if (m_bonus_param[1].MAX_COMBO > m_bonus_param[0].MAX_COMBO)
				DrawRotaGraph(SCREEN_WIDTH * 3 / 4, GROUND - charamargin, 1.0, 0.0, m_appealchara2_graph[GetModeCount() / 2 % 40], TRUE);
		}
		else
		{
			DrawRotaGraph(SCREEN_WIDTH / 4, GROUND - charamargin, 1.0, 0.0, m_charactor1_graph[GetModeCount() / 2 % 30], TRUE, TRUE);
			DrawRotaGraph(SCREEN_WIDTH * 3 / 4, GROUND - charamargin, 1.0, 0.0, m_charactor2_graph[GetModeCount() / 2 % 30], TRUE);
		}
	}
	else if (GetModeCount() >= 240 && GetModeCount() < 320)
	{
		//死亡回数ボーナスを獲得者がいれば、アピールアニメーションを再生
		//いなければ二人とも待機アニメーションのまま
		if (m_num_graph[2] != 0)
		{
			if (m_bonus_param[1].DEATH_COUNT > m_bonus_param[0].DEATH_COUNT)
				DrawRotaGraph(SCREEN_WIDTH / 4, GROUND - charamargin, 1.0, 0.0, m_appealchara1_graph[GetModeCount() / 2 % 40], TRUE, TRUE);
			else if (m_bonus_param[0].DEATH_COUNT > m_bonus_param[1].DEATH_COUNT)
				DrawRotaGraph(SCREEN_WIDTH * 3 / 4, GROUND - charamargin, 1.0, 0.0, m_appealchara2_graph[GetModeCount() / 2 % 40], TRUE);
		}
		else
		{
			DrawRotaGraph(SCREEN_WIDTH / 4, GROUND - charamargin, 1.0, 0.0, m_charactor1_graph[GetModeCount() / 2 % 30], TRUE, TRUE);
			DrawRotaGraph(SCREEN_WIDTH * 3 / 4, GROUND - charamargin, 1.0, 0.0, m_charactor2_graph[GetModeCount() / 2 % 30], TRUE);
		}
	}
	else
	{
		//ボーナスタイム終了後は待機アニメーション
		DrawRotaGraph(SCREEN_WIDTH / 4, GROUND - charamargin, 1.0, 0.0, m_charactor1_graph[GetModeCount() / 2 % 30], TRUE, TRUE);
		DrawRotaGraph(SCREEN_WIDTH * 3 / 4, GROUND - charamargin, 1.0, 0.0, m_charactor2_graph[GetModeCount() / 2 % 30], TRUE);
	}

}

void ModeScoreBonus::DrawSpotlight()
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, 128);

	int width, height;
	GetGraphSize(m_spotlight_graph, &width, &height);

	//BOSSダメージボーナス獲得者がいれば、獲得者の位置にスポットライトを生成
	if (GetModeCount() >= 80 && GetModeCount() < 160)
	{
		if (m_num_graph[0] != 0)
		{
			if (m_bonus_param[0].BOSS_DAMAGE > m_bonus_param[1].BOSS_DAMAGE)
				DrawRotaGraph(SCREEN_WIDTH / 4, height / 2 - 50, 1.0, 0.0, m_spotlight_graph, TRUE);
			else if (m_bonus_param[1].BOSS_DAMAGE > m_bonus_param[0].BOSS_DAMAGE)
				DrawRotaGraph(SCREEN_WIDTH * 3 / 4, height / 2 - 50, 1.0, 0.0, m_spotlight_graph, TRUE);
		}
	}

	//最大コンボボーナス獲得者がいれば、獲得者の位置にスポットライトを生成
	if (GetModeCount() >= 160 && GetModeCount() < 240)
	{
		if (m_num_graph[1] != 0)
		{
			if (m_bonus_param[0].MAX_COMBO > m_bonus_param[1].MAX_COMBO)
				DrawRotaGraph(SCREEN_WIDTH / 4, height / 2 - 50, 1.0, 0.0, m_spotlight_graph, TRUE);
			else if (m_bonus_param[1].MAX_COMBO > m_bonus_param[0].MAX_COMBO)
				DrawRotaGraph(SCREEN_WIDTH * 3 / 4, height / 2 - 50, 1.0, 0.0, m_spotlight_graph, TRUE);
		}

	}

	//死亡回数ボーナス獲得者がいれば、獲得者の位置にスポットライトを生成
	if (GetModeCount() >= 240 && GetModeCount() < 320)
	{
		if (m_num_graph[2] != 0)
		{
			if (m_bonus_param[1].DEATH_COUNT > m_bonus_param[0].DEATH_COUNT)
				DrawRotaGraph(SCREEN_WIDTH / 4, height / 2 - 50, 1.0, 0.0, m_spotlight_graph, TRUE);
			else if (m_bonus_param[0].DEATH_COUNT > m_bonus_param[1].DEATH_COUNT)
				DrawRotaGraph(SCREEN_WIDTH * 3 / 4, height / 2 - 50, 1.0, 0.0, m_spotlight_graph, TRUE);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ModeScoreBonus::SetCharaGraph(int _player1, int _player2)
{
	m_player_charactor[0] = _player1;
	m_player_charactor[1] = _player2;

	int charatype[2] = { _player1,_player2 };

	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		if (charatype[i] == NARI1)
		{
			if (i == 0)
			{
				LoadDivGraph("resource/player/nari_wait1.png", 30, 30, 1, 500, 500, m_charactor1_graph);
				LoadDivGraph("resource/player/nari_appeal1.png", 40, 40, 1, 500, 500, m_appealchara1_graph);
			}
			else
			{
				LoadDivGraph("resource/player/nari_wait1.png", 30, 30, 1, 500, 500, m_charactor2_graph);
				LoadDivGraph("resource/player/nari_appeal1.png", 40, 40, 1, 500, 500, m_appealchara2_graph);
			}
		}
		else if (charatype[i] == NARI2)
		{
			if (i == 0)
			{
				LoadDivGraph("resource/player/nari_wait2.png", 30, 30, 1, 500, 500, m_charactor1_graph);
				LoadDivGraph("resource/player/nari_appeal2.png", 40, 40, 1, 500, 500, m_appealchara1_graph);
			}
			else
			{
				LoadDivGraph("resource/player/nari_wait2.png", 30, 30, 1, 500, 500, m_charactor2_graph);
				LoadDivGraph("resource/player/nari_appeal2.png", 40, 40, 1, 500, 500, m_appealchara2_graph);
			}
		}
		else if (charatype[i] == NONAME1)
		{
			if (i == 0)
			{
				LoadDivGraph("resource/player/noname_wait1.png", 30, 30, 1, 500, 500, m_charactor1_graph);
				LoadDivGraph("resource/player/noname_appeal1.png", 40, 40, 1, 500, 500, m_appealchara1_graph);
			}
			else
			{
				LoadDivGraph("resource/player/noname_wait1.png", 30, 30, 1, 500, 500, m_charactor2_graph);
				LoadDivGraph("resource/player/noname_appeal1.png", 40, 40, 1, 500, 500, m_appealchara2_graph);
			}
		}
		else if (charatype[i] == NONAME2)
		{
			if (i == 0)
			{
				LoadDivGraph("resource/player/noname_wait2.png", 30, 30, 1, 500, 500, m_charactor1_graph);
				LoadDivGraph("resource/player/noname_appeal2.png", 40, 40, 1, 500, 500, m_appealchara1_graph);
			}
			else
			{
				LoadDivGraph("resource/player/noname_wait2.png", 30, 30, 1, 500, 500, m_charactor2_graph);
				LoadDivGraph("resource/player/noname_appeal2.png", 40, 40, 1, 500, 500, m_appealchara2_graph);
			}
		}
	}
}


void ModeScoreBonus::AddBonusPoint()
{
	//ボスボーナス
	if (m_bonus_param[0].BOSS_DAMAGE > m_bonus_param[1].BOSS_DAMAGE)
	{
		m_player_point[0] += BONUS_POINT;
		m_num_graph[0] = ResourceServer::LoadGraph("resource/result/result_bana_p1.png");
		bonuspoint1.SetParam("resource/scorebonus/ui_bonus_100.png", SCREEN_WIDTH / 4, GROUND - 200, 0.0, 30.0, 60);
	}
	else if (m_bonus_param[1].BOSS_DAMAGE > m_bonus_param[0].BOSS_DAMAGE)
	{
		m_player_point[1] += BONUS_POINT;
		m_num_graph[0] = ResourceServer::LoadGraph("resource/result/result_bana_p2.png");
		bonuspoint1.SetParam("resource/scorebonus/ui_bonus_100.png", SCREEN_WIDTH * 3 / 4, GROUND - 200, 0.0, 30.0, 60);
	}
	else
		m_num_graph[0] = 0;

	//コンボボーナス
	if (m_bonus_param[0].MAX_COMBO > m_bonus_param[1].MAX_COMBO)
	{
		m_player_point[0] += BONUS_POINT;
		m_num_graph[1] = ResourceServer::LoadGraph("resource/result/result_bana_p1.png");
		bonuspoint2.SetParam("resource/scorebonus/ui_bonus_100.png", SCREEN_WIDTH / 4, GROUND - 200, 0.0, 30.0, 60);

	}
	else if (m_bonus_param[1].MAX_COMBO > m_bonus_param[0].MAX_COMBO)
	{
		m_player_point[1] += BONUS_POINT;
		m_num_graph[1] = ResourceServer::LoadGraph("resource/result/result_bana_p2.png");
		bonuspoint2.SetParam("resource/scorebonus/ui_bonus_100.png", SCREEN_WIDTH * 3 / 4, GROUND - 200, 0.0, 30.0, 60);
	}
	else
		m_num_graph[1] = 0;


	//デスボーナス
	if (m_bonus_param[1].DEATH_COUNT > m_bonus_param[0].DEATH_COUNT)
	{
		m_player_point[0] += BONUS_POINT;
		m_num_graph[2] = ResourceServer::LoadGraph("resource/result/result_bana_p1.png");
		bonuspoint3.SetParam("resource/scorebonus/ui_bonus_100.png", SCREEN_WIDTH / 4, GROUND - 200, 0.0, 30.0, 60);
	}
	else if (m_bonus_param[0].DEATH_COUNT > m_bonus_param[1].DEATH_COUNT)
	{
		m_player_point[1] += BONUS_POINT;
		m_num_graph[2] = ResourceServer::LoadGraph("resource/result/result_bana_p2.png");
		bonuspoint3.SetParam("resource/scorebonus/ui_bonus_100.png", SCREEN_WIDTH * 3 / 4, GROUND - 200, 0.0, 30.0, 60);
	}
	else
		m_num_graph[2] = 0;
}

void ModeScoreBonus::PlaySE(const char* _filename, const float _pitch, Game& _game)
{
	_game.m_se.Load(_filename);
	_game.m_se.SetVolume(SE_VOLUME);
	_game.m_se.Pitch(_pitch);
	_game.m_se.PlayBackGround(_game.m_se);
}