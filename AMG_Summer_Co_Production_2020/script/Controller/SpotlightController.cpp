/**
 * @file	AMG_Summer_Co_Production_2020\script\SpotlightController.cpp.
 *
 * @brief	�X�|�b�g���C�g�̏o�����Ǘ�����N���X
 * 				1���Ԃ�2��X�|�b�g���C�g�𐶐�����
 */

#include"SpotlightController.h"
#include"../Object/Spotlight.h"
#include"../Game.h"
#include"../Mode/ModeGame.h"
#include"DxLib.h"
using namespace illumism;

SpotlightController::SpotlightController()
{
	once_flag = true;
	m_start_time = 0;
	m_now_time = 0;
	m_interval = 3600 / 2;
	m_time = 0;
	m_count = 1;
}

SpotlightController::~SpotlightController()
{

}

void SpotlightController::Process(Game& _game)
{
	//�v���C���[������ł���悤�ɂȂ��Ă���0�ɂȂ�悤�ɒ���
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	m_now_time = modeGame->GetModeCount() - START_TIME;
	m_time = m_now_time;

	//1����2��X�|�b�g���C�g�𐶐�
	if (m_time >= m_interval * m_count)
	{
		for (int i = 0; i < 2; i++)
		{
			Spotlight* spotlight = new Spotlight(GetRand(3), GetRand(8) + 4);
			spotlight->SetPosition(SCREEN_WIDTH * (i + 1) / 3 - spotlight->GetWidth() / 2, 0);
			if (i == 0) { spotlight->SetSpeed(GetRand(3) + 4); }
			if (i == 1) { spotlight->SetSpeed(-GetRand(3) - 4); }
			spotlight->SetTime(GetRand(5) + 4);
			_game.m_objectserver.Add(spotlight);
		}
		m_count++;
	}
}