/**
 * @file	AMG_Summer_Co_Production_2020\script\Game.h.
 *
 * @brief	�Q�[���V�[��
 * @author	Takuya Fujisawa
 */

#pragma once
#include"Server/ObjectServer.h"
#include"Server/ModeServer.h"
#include"Sound/PlayWAVE.h"
#include"Dxlib.h"

namespace illumism
{

	namespace
	{
		constexpr auto SCREEN_WIDTH = 1920; //!< ��ʐݒ�
		constexpr auto SCREEN_HEIGHT = 1080;
		constexpr auto SCREEN_DEPTH = 32;

		constexpr auto THUMB_MAX = 32767.0f;
		constexpr auto ANALOG_MIN = 0.1f;

		constexpr auto GROUND = 925;
		constexpr auto GAME_PLAYER_NUM = 2; //!< �v���C���[�l��

		constexpr auto STAGE_WIDTH_LEFT = 170;  //!< �X�e�[�W��
		constexpr auto STAGE_WIDTH_RIGHT = 1840;

		constexpr auto START_TIME = 180;	//!< �Q�[���J�n����

		constexpr int LEFT = -1;
		constexpr int RIGHT = 1;
		constexpr int UP = -1;
		constexpr int DOWN = 1;

		constexpr int JUMP_HEIGHT = 27; //!< �W�����v�̍���
		constexpr int BULLET_MAX = 99;  //!< �e�ە`��\��
		constexpr int ANIM_FRAME = 10;  //!< �A�j���[�V�����Đ��\�t���[��

		constexpr int  MOVE_SPEED = 12; //!< �ړ����x

		constexpr int FLY_SPEED = 25;   //!< ��s�X�s�[�h
		constexpr int FLY_TIME = 40;	//!< ��s����

		constexpr int BULLET_DAMAGE = -5;   //!< �e�ۃ_���[�W
		constexpr int ATTACK_DAMAGE = -10;  //!< �A�^�b�N�_���[�W
		constexpr int SPMOVE_DAMAGE = -30; //!< �K�E�Z�_���[�W
		constexpr int BOSS_ATTACK_DAMAGE = -10; //!< �{�X�U���̃_���[�W

		constexpr int MP_MAX = 100; //!< HP�ő�l

		float SE_VOLUME = 0.8f; //!< SE����
		float BGM_VOLUME = 0.6f;	//!< BGM����

		/**
		 * @enum	CHARACTOR
		 *
		 * @brief	�L�����N�^�[��ޒ萔
		 */
		enum CHARACTOR
		{
			NARI1, NONAME1, NARI2, NONAME2
		};
	}

	/**
	 * @class	Game
	 *
	 * @brief	�Q�[���V�[���N���X
	 *
	 */
	class Game
	{
	public:
		Game();
		~Game();

		/**
		 * @fn	void Game::Input();
		 *
		 * @brief	�R���g���[���[����̓��͏���
		 *
		 */
		void Input();

		/**
		 * @fn	void Game::Process();
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 */
		void Process();

		/**
		 * @fn	void Game::Draw();
		 *
		 * @brief	�`�揈��
		 *
		 */
		void Draw();

		/**
		 * @fn	const void Game::SetExitFlag(const bool _flag)
		 *
		 * @brief	���C�����[�v�𔲂���t���O��ݒ�
		 *
		 * @param 	_flag		���C�����[�v�𔲂���t���O
		 */
		const void SetExitFlag(const bool _flag) { m_exit_flag = _flag; }

		/**
		 * @fn	const bool Game::GetExitFlag()
		 *
		 * @brief	���C�����[�v�𔲂���t���O���擾
		 *
		 * @returns	���C�����[�v�𔲂���t���O
		 */
		const bool GetExitFlag() { return m_exit_flag; }

		int m_gkey[GAME_PLAYER_NUM] = { 0 };	//!< �Q�[���p�b�h����
		int m_trigger_key[GAME_PLAYER_NUM] = { 0 }; //!< �Q�[���p�b�h�̃g���K�[����

		//DINPUT_JOYSTATE m_dinput_state[GAME_PLAYER_NUM];	//!< L�g���K�[,R�g���K�[,�X�e�B�b�N���͗p
		XINPUT_STATE m_xinput_state[GAME_PLAYER_NUM]; //!< L�g���K�[,R�g���K�[,�X�e�B�b�N���͗p

		ObjectServer m_objectserver;	//!< �I�u�W�F�N�g�T�[�o

		ModeServer* m_modeserver;   //!<���[�h�T�[�o

		sound::PlayWAVE m_bgm; //!< BGM

		sound::PlayWAVE m_se;  //!< SE
	private:
		int m_gframe_count; //!< �Q�[���V�[�����̃t���[���J�E���^
		bool m_exit_flag;   //!< ���C�����[�v�𔲂���t���O
	};
}