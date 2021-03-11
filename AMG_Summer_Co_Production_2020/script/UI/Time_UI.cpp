/**
 * @file	AMG_Summer_Co_Production_2020\script\Time_UI.cpp.
 *
 * @brief	�Q�[�����[�h�̃v���C���Ԃ�\��
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

	//�Q�[���J�n���̑���o���Ȃ����Ԃ͎������Ԃ��Œ�\��
	if (m_now_time < 0)
	{
		m_GameTime = GAMETIME;
		m_minutes = m_GameTime / 3600;
		m_second = (m_GameTime % 3600) / 60;
		return;
	}

	GenerateBOSS(_game);

	//�Q�[�����Ԃ��X�V
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

	//�b�������\������Ȃ����߁A�Q�[���Ō��0�b�ȏ�A1�b�����̂Ƃ���0�b�ƕ\������Ă��܂�
	// ���̂���1�b���ԕ\���ł͑����\������
	auto check_tenrank = [](int _second)->int
	{
		_second++;
		//60�b�ƕ\������Ă��܂��̂ŏ\�̈ʂ�0�ɐݒ�
		if (_second/10 == 6) { return 0; }
		return _second / 10;
	};
	tenrank = check_tenrank(m_second);

	auto check_onerank = [](int _second,int _gametime)->int
	{
		//�Q�[���I�����ɂ�0�b�ƕ\��
		if (_gametime <= 0) { return 0; }
		_second++;
		//9�b�̂Ƃ��Ɉ�̈ʂ�10�Ɛݒ肳��Ă��܂��̂ň�̈ʂ�0�ɐݒ�
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
	//�{�X��������
	if (m_GameTime != BOSSTIME)
		return;

	//60�t���[����������Ȃ����߂�1�x�����������s��
	if (onceflag == false)
		return;

	ObjectBase* BOSS = new ::BOSS();
	_game.m_objectserver.Insert(BOSS);
	onceflag = false;
}