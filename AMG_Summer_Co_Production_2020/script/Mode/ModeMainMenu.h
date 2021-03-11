/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeMainMenu.h.
 *
 * @brief	���C�����j���[���[�h
 * @author	Takuya Fujisawa
 */

#pragma once
#include"ModeBase.h"
#include"../Sound/PlayWAVE.h"

namespace illumism
{
	/**
	 * @class	ModeMainMenu
	 *
	 * @brief	���C�����j���[���[�h
	 *
	 */
	class ModeMainMenu :
		public ModeBase
	{
	public:

		/**
		 * @fn	ModeMainMenu::ModeMainMenu(int _menu_state,bool _playbgm);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_menu_state	���[�h�J�n���ɑI������Ă��郁�j���[���w��
		 * 										BATTLE : 0, TUTORIAL : 1, EXIT : 2, CREDIT : 3
		 * @param 	_playbgm   	BGM�Đ��p�t���O�i���U���g��ʂ���J�ڂ����Ƃ��p�j
		 */
		ModeMainMenu(int _menu_state, bool _playbgm);

		/**
		 * @fn	virtual bool ModeMainMenu::Initialize(Game& _game);
		 *
		 * @brief	����������
		 * @detail	ModeServer�ڑ����Ɉ�x�����Ă΂��
		 *
		 * @param [in,out]	_game	Game�N���X�̎Q��
		 *
		 * @returns	�����������̉�
		 */
		virtual bool Initialize(Game& _game);

		/**
		 * @fn	virtual bool ModeMainMenu::Terminate(Game& _game);
		 *
		 * @brief	�I������
		 * @detail	ModeServer����폜�����ہA��x�����Ă΂��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	�I�����������̉�
		 */
		virtual bool Terminate(Game& _game);

		/**
		 * @fn	virtual bool ModeMainMenu::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	���Z���������̉�
		 */
		virtual bool Process(Game& _game);

		/**
		 * @fn	virtual bool ModeMainMenu::Draw(Game& _game);
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	�`�揈�������̉�
		 */
		virtual bool Draw(Game& _game);

		/**
		 * @fn	void ModeMainMenu::Input(Game& _game);
		 *
		 * @brief	�R���g���[���[����{�^�����͂����m���A���j���[�̑J�ڂ��s��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 */
		void Input(Game& _game);

		/**
		 * @fn	void ModeMainMenu::State(Game& _game);
		 *
		 * @brief	���j���[�̏�ԑJ�ڂ��Ǘ�
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 */
		void State(Game& _game);

		/**
		 * @enum	MENU_STATE
		 *
		 * @brief	���j���[�̏�ԑJ�ڗp�ϐ�
		 */
		enum MENU_STATE
		{
			BATTLE, TUTORIAL, EXIT, CREDIT, BACKTITLE
		};
	private:
		/**
		 * @fn	void ModeMainMenu::Battle(Game& _game);
		 *
		 * @brief	�o�g�����j���[�֑J��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 */
		void Battle(Game& _game);

		/**
		 * @fn	void ModeMainMenu::Tutorial(Game& _game);
		 *
		 * @brief	�`���[�g���A�����j���[�֑J��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 */
		void Tutorial(Game& _game);

		/**
		 * @fn	void ModeMainMenu::Exit(Game& _game);
		 *
		 * @brief	�Q�[���I���֑J��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 */
		void Exit(Game& _game);

		/**
		 * @fn	void ModeMainMenu::Credit(Game& _game);
		 *
		 * @brief	�N���W�b�g��ʂ֑J��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 */
		void Credit(Game& _game);

		/**
		 * @fn	void ModeMainMenu::NextMode(Game& _game);
		 *
		 * @brief	�I�����ꂽ���[�h�֑J��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 */
		void NextMode(Game& _game);

		/**
		 * @fn	void ModeMainMenu::PlayBGM(Game& _game);
		 *
		 * @brief	���U���g��ʂ���J�ڂ����Ƃ���BGM�𗬂�����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void PlayBGM(Game& _game);

		/**
		 * @fn	void ModeMainMenu::PlaySE(const char* _filename, const float _pitch, Game& _game);
		 *
		 * @brief	���ʉ��Đ�
		 *
		 * @param 		  	_filename	�����t�@�C����
		 * @param 		  	_pitch   	�Đ����x
		 * @param [in,out]	_game	 	�Q�[���N���X�̎Q��
		 */
		void PlaySE(const char* _filename, const float _pitch, Game& _game);
	private:
		//!< �摜�n���h��.
		int m_background_graph;
		int m_battle_graph;
		int m_tutorial_graph;
		int m_exit_graph;
		int m_credit_graph;

		int m_width, m_height;

		int m_menu_state;   //!< ��ԑJ�ڗp�ϐ�
		bool m_selected_flag;   //!<	���j���[�I���ςݗp�t���O
		int m_press_count;   //!< <�{�^����������Ă���̌o�ߎ��ԃJ�E���^
		int m_press_frame;  //!< �G�t�F�N�g�p�t���[���L�^�ϐ�

		float m_freq;   //!< ���[�p�X�t�B���^�̎Ւf���g��
		bool m_playbgm_flag;	//!<BGM�Đ��p�t���O�i���U���g��ʂ���J�ڂ����Ƃ��p�j
	};
}