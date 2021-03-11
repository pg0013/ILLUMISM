/**
 * @file	AMG_Summer_Co_Production_2020\script\main.cpp.
 *
 * @brief	�v���O�����̃G���g���[�|�C���g
 */

#include"DxLib.h"
#include"Game.h"
#include"Sound/PlayWAVE.h"
#include"Server/ResourceServer.h"
#include"time.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//DX���C�u�����̃A�[�J�C�u�t�@�C���ǂݍ��݂��g�p����
	SetUseDXArchiveFlag(TRUE);
	//Log.txt���o�͂��Ȃ�
	SetOutApplicationLogValidFlag(FALSE);

	//�E�B���h�E�ɕ\������閼�O�̐ݒ�
	SetMainWindowText("ILLUMISM");
	//�E�B���h�E���[�h�̐ݒ�
	ChangeWindowMode(TRUE);

	//��ʐݒ�
	SetGraphMode(illumism::SCREEN_WIDTH, illumism::SCREEN_HEIGHT, illumism::SCREEN_DEPTH);

	//DX���C�u�����̏�����
	if (DxLib_Init() == -1)
	{
		//�G���[���N������I��
		return -1;
	}

	sound::PlayWAVE::Init();
	illumism::ResourceServer::Init();

	srand((unsigned int)time(NULL));
	SetJoypadDeadZone(DX_INPUT_PAD1, 0.1);
	SetJoypadDeadZone(DX_INPUT_PAD2, 0.1);

	illumism::Game* game = new illumism::Game();

	//���C�����[�v
	while (ProcessMessage() == 0)
	{
		game->Input();
		game->Process();
		game->Draw();

		if (game->GetExitFlag() == true)
			break;
	}

	delete game;

	illumism::ResourceServer::Release();
	sound::PlayWAVE::Release();

	DxLib_End();

	return 0;
}