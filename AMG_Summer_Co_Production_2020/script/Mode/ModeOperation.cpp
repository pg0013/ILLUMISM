/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeOperation.cpp.
 *
 * @brief	����������[�h
 */

#include "ModeOperation.h"
#include"ModeSelectChara.h"
#include"ModeOverlay.h"
#include"../Server/ResourceServer.h"
#include"../Game.h"
#include "DxLib.h"
using namespace illumism;

ModeOperation::ModeOperation(int _p1, int _p2)
{
	//�L�����I�����[�h�ɑJ�ڂ����Ƃ��ɁA�I�����Ă����L������\�����邽�ߑI���L������ۑ�
	m_selectchara_state[0] = _p1;
	m_selectchara_state[1] = _p2;
}

bool ModeOperation::Initialize(Game& _game)
{
	if (!ModeBase::Initialize(_game)) { return false; }

	m_graph = ResourceServer::LoadGraph("resource/tutorial/tutorial_2.png");

	_game.m_se.Load("resource/se/cancel.wav");
	_game.m_se.SetVolume(SE_VOLUME);

	m_press_count = -1;
	m_once_flag = false;

	return true;
}

bool ModeOperation::Terminate(Game& _game)
{
	ModeBase::Terminate(_game);

	return true;
}

bool ModeOperation::Process(Game& _game)
{
	ModeBase::Process(_game);

	m_press_count--;

	Input(_game);

	NextMode(_game);

	return true;
}

void ModeOperation::Input(Game& _game)
{
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		//B�{�^���ŃL�����I����ʂɖ߂�
		if ((_game.m_trigger_key[i] & PAD_INPUT_2) &&
			m_once_flag == false)
		{
			_game.m_se.PlayBackGround(_game.m_se);

			ModeOverlay* modeoverlay = new ModeOverlay();
			modeoverlay->Capture(60);
			_game.m_modeserver->Add(modeoverlay, 1, "Overlay");

			m_press_count = 1;

			m_once_flag = true;
		}

		//Y�{�^���ŃL�����I����ʂɖ߂�
		if ((_game.m_trigger_key[i] & PAD_INPUT_4) &&
			m_once_flag == false)
		{
			_game.m_se.PlayBackGround(_game.m_se);

			ModeOverlay* modeoverlay = new ModeOverlay();
			modeoverlay->Capture(60);
			_game.m_modeserver->Add(modeoverlay, 1, "Overlay");

			m_press_count = 1;

			m_once_flag = true;
		}
	}
}

void ModeOperation::NextMode(Game& _game)
{
	//�w��b����ɃL�����I����ʂɖ߂�
	if (m_press_count == 0)
	{
		ModeSelectChara* modeselect = new ModeSelectChara(m_selectchara_state[0], m_selectchara_state[1], false);
		_game.m_modeserver->Add(modeselect, 0, "ModeSelectChara");
		_game.m_modeserver->Del(this);
	}
}

bool ModeOperation::Draw(Game& _game)
{
	ModeBase::Draw(_game);

	DrawGraph(0, 0, m_graph, FALSE);

	return true;
}