/**
 * @file	AMG_Summer_Co_Production_2020\script\Game.cpp.
 *
 * @brief	�Q�[���V�[���̃N���X
 */

#include "Game.h"
#include"Mode/ModeLogo.h"
#include<time.h>
using namespace illumism;

Game::Game()
{
	m_gframe_count = 0;
	m_exit_flag = false;

	for (int i = 0; i < GAME_PLAYER_NUM; i++)
		m_gkey[i] = 0;

	m_modeserver = new ModeServer(*this);

	ModeLogo* modelogo = new ModeLogo(AMG_LOGO);
	m_modeserver->Add(modelogo, 0, "Logo");

	m_bgm.Load("resource/bgm/Reflect.wav");
	m_se.Load("resource/se/title.wav");
}

Game::~Game()
{
	m_bgm.Pause();
	m_bgm.Destroy();
	m_se.Pause();
	m_se.Destroy();

	delete m_modeserver;
}

void Game::Input()
{
	//�v���C���[���ƂɃR���g���[�����͂����o
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		int pre_key[GAME_PLAYER_NUM];										//�O�t���[���̓��͋L�^�p

		pre_key[i] = m_gkey[i];														//�O�t���[���̃p�b�h����
		m_gkey[i] = GetJoypadInputState(i + 1);							//�{�^���̓��͂����o
		GetJoypadXInputState(i + 1, &m_xinput_state[i]);//�R���g���[����LR�g���K�[��X�e�B�b�N�����o
		if (m_xinput_state[i].ThumbLX / THUMB_MAX < ANALOG_MIN &&
			m_xinput_state[i].ThumbLX / THUMB_MAX > -ANALOG_MIN)
			m_xinput_state[i].ThumbLX = 0;
		if (m_xinput_state[i].ThumbLY / THUMB_MAX < ANALOG_MIN &&
			m_xinput_state[i].ThumbLY / THUMB_MAX > -ANALOG_MIN)
			m_xinput_state[i].ThumbLY = 0;

		//XOR�őO�t���[���ƍ��t���[���̍��������邱�ƂŁA�g���K�[���͂����m�ł���B
		m_trigger_key[i] = (pre_key[i] ^ m_gkey[i]) & m_gkey[i];
	}
}

void Game::Process()
{
	m_modeserver->ProcessInit();
	m_modeserver->Process();
	m_modeserver->ProcessFinish();

	m_gframe_count++;
}

void Game::Draw()
{
	m_modeserver->DrawInit();
	SetDrawScreen(DX_SCREEN_BACK);
	m_modeserver->Draw();
	m_modeserver->DrawFinish();
}