/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeLogo.cpp.
 *
 * @brief	AMG�ƃ`�[�����S�\�����[�h
 * 				�R���X�g���N�^�ŕ`�悷�郍�S���w�肷��
 * 				2�b�t�F�[�h�C�� �� 2�b���S�摜 �� 2�b�t�F�[�h�A�E�g
 * 				A�{�^���������ꂽ��1�b�Ŏ��̃��[�h�Ɉڍs
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
	//�`�悷�郍�S�摜��I��
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

	//�t�F�[�h�C��
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
	//A�{�^���������ꂽ��X�L�b�v
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		if ((_game.m_trigger_key[i] & PAD_INPUT_1) &&
			m_once_flag == false &&
			GetModeCount() < 240)
		{
			//�t�F�[�h�A�E�g
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
	//���[�h�J�n����4�b��Ƀt�F�[�h�A�E�g
	if (GetModeCount() == 240 && m_once_flag == false)
	{
		ModeOverlay* modeoverlay = new ModeOverlay();
		modeoverlay->Fade(121, FADE_OUT);
		_game.m_modeserver->Add(modeoverlay, 1, "Overlay");
	}

	//���[�h�J�n����6�b��Ƀ��[�h�J��
	if (GetModeCount() == 360 && logonum == TEAM_LOGO)
	{
		//�^�C�g�����[�h�ֈڍs
		ModeTitle* modetitle = new ModeTitle();
		_game.m_modeserver->Add(modetitle, 0, "Title");
		_game.m_modeserver->Del(this);
	}
	else if (GetModeCount() == 360)
	{
		//�`�[�����S�ֈڍs
		ModeLogo* modelogo = new ModeLogo(TEAM_LOGO);
		_game.m_modeserver->Add(modelogo, 0, "Logo");
		_game.m_modeserver->Del(this);
	}
}

void ModeLogo::SkipLogoMode(Game& _game)
{
	//�`�[�����S�摜�ւ����ڍs
	if (logonum == AMG_LOGO && m_press_count == 0)
	{
		ModeLogo* modelogo = new ModeLogo(TEAM_LOGO);
		_game.m_modeserver->Add(modelogo, 0, "Logo");
		_game.m_modeserver->Del(this);
	}

	//�^�C�g�����[�h�ւ����ڍs
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