/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeSelectChara.h.
 *
 * @brief	�v���C�L�����N�^�[�I�����[�h
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ModeBase.h"

namespace illumism
{
	/**
	  * @class	ModeSelectChara
	  *
	  * @brief	�L�����N�^�[�I�����[�h�N���X
	  *
	  */
	class ModeSelectChara : public ModeBase
	{
	public:
		/**
		 * @fn	ModeSelectChara::ModeSelectChara(int _p1, int _p2 ,bool _startEQ);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_p1			�v���C���[�P�I���L�����i�����[�h����J�ڎ��p�j
		 * @param 	_p2			�v���C���[2�I���L�����i�����[�h����J�ڎ��p�j
		 * @param 	_startEQ	���[�h�J�n����EQ���s���t���O�i���C�����j���[���[�h����̂�true�j
		 */
		ModeSelectChara(int _p1, int _p2, bool _startEQ);

		/**
		 * @fn	virtual bool ModeSelectChara::Initialize(Game& _game);
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
		 * @fn	virtual bool ModeSelectChara::Terminate(Game& _game);
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
		 * @fn	virtual bool ModeSelectChara::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	���Z���������̉�
		 */
		virtual bool Process(Game& _game);

		/**
		 * @fn	virtual bool ModeSelectChara::Draw(Game& _game);
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	�`�揈�������̉�
		 */
		virtual bool Draw(Game& _game);

		/**
		 * @fn	void ModeSelectChara::Input(Game& _game);
		 *
		 *
		 * @brief	�R���g���[���[������͂����m���A��ʑJ�ڂ��s��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 */
		void Input(Game& _game);

		/**
		 * @fn	void ModeSelectChara::State(Game& _game);
		 *
		 * @brief	��ԑJ�ڂ��Ǘ�
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��.
		 */
		void State(Game& _game);

	private:

		/**
		 * @fn	void ModeSelectChara::Init();
		 *
		 * @brief	����������
		 */
		void Init();

		/**
		 * @fn	void ModeSelectChara::EQFade(Game& _game);
		 *
		 * @brief	���[�h�J�n,�I������EQ��������
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��.
		 */
		void EQFade(Game& _game);

		/**
		 * @fn	void ModeSelectChara::Exit(Game& _game);
		 *
		 * @brief	�L�����I�����[�h���I�����A���C�����j���[���[�h�֑J��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��.
		 */
		void Exit(Game& _game);

		/**
		 * @fn	void ModeSelectChara::Operation(Game& _game);
		 *
		 * @brief	����������[�h�֑J��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��.
		 */
		void Operation(Game& _game);

		/**
		 * @fn	void ModeSelectChara::Ready(Game& _game);
		 *
		 * @brief	�Q�[���J�n��Ԃ֏�ԑJ�ڂ��ڍs
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��.
		 */
		void Ready(Game& _game);

		/**
		 * @fn	void ModeSelectChara::DrawOperationButton();
		 *
		 * @brief	��������{�^����`��
		 *
		 */
		void DrawOperationButton();

		/**
		 * @fn	void ModeSelectChara::DrawExitButton();
		 *
		 * @brief	Exit�{�^����`��
		 *
		 */
		void DrawExitButton();

		/**
		 * @fn	void ModeSelectChara::DrawSelectArrow();
		 *
		 * @brief	�L�����I�����`��
		 *
		 */
		void DrawSelectArrow();

		/**
		 * @fn	void ModeSelectChara::DrawSelectLight();
		 *
		 * @brief	�L�����I�����莞�Ƀ��C�g��`��
		 *
		 */
		void DrawSelectLight();

		/**
		 * @fn	void ModeSelectChara::DrawReadySign();
		 *
		 * @brief	READY?�摜��`��
		 *
		 */
		void DrawReadySign();

		/**
		 * @fn	void ModeSelectChara::SelectCharaAnim();
		 *
		 * @brief	�L�����N�^�[�I�����̃A�j���[�V�����`�揈��
		 *
		 */
		void SelectCharaAnim();

		/**
		 * @fn	void ModeSelectChara::SelectAutoChara();
		 *
		 * @brief	�I���L������������Ƃ��ɁAP1P2�J���[�������őI�����鏈��
		 *
		 */
		void SelectAutoChara();

		/**
		 * @fn	void ModeSelectChara::PlaySE(const char* _filename, const float _pitch, Game& _game,const float _pan = 0.0f);
		 *
		 * @brief	Play se
		 *
		 * @param 		   	_filename	�����t�@�C����.
		 * @param 		   	_pitch   	�Đ����x.
		 * @param [in, out]	_game	 	�Q�[���N���X�̎Q��.
		 * @param 		   	_pan	 	(Optional) ���E�o�����X�i�w��Ȃ��ł͒����j.
		 */
		void PlaySE(const char* _filename, const float _pitch, Game& _game, const float _pan = 0.0f);

		/**
		 * @enum	MENU_STATE
		 *
		 * @brief	��ԑJ�ڗp�萔
		 */
		enum MENU_STATE
		{
			SELECT, EXIT, OPERATION, READY, CANSEL
		};

	private:

		int m_background_graph; //!< �摜�n���h��
		int m_charactor_graph[4] = { 0 };
		int m_exit_graph[2] = { 0 };
		int m_operation_graph[2] = { 0 };
		int m_select_under_graph;
		int m_select_arrow_graph;
		int m_light_select_back_graph;
		int m_light_select_graph[2] = { 0 };
		int m_light_ready_graph;
		int m_ready_graph;

		int m_selectchara_state[2] = { 0 }; //!< �I���L�����ۑ��p�ϐ�
		int m_menu_state;   //!< ��ԑJ�ڗp�ϐ�

		bool m_gogame_flag; //!< READY��Ԃ���Q�[���V�[���ڍs�p�t���O
		bool m_once_flag;   //!< <��x�̂ݍs���鏈���p�t���O
		bool m_exit_flag;   //!< ���C�����j���[���[�h�ֈڍs�p�t���O
		bool m_ready_flag[2] = { 0 };   //!< �L�����N�^�[�I���ς݃t���O
		bool m_startEQ_flag;	//!< ���[�h�J�n����EQ���s���t���O

		float m_cancel_count[2] = { 0.0f }; //!<B�{�^���������J�E���^
		int m_press_count; //!< �{�^����������Ă���̌o�ߎ��ԃJ�E���^
		int m_press_frame;  //!< �G�t�F�N�g�p�{�^�����������t���[���ۑ��ϐ�
		int m_anim_count[2] = { 0 };	//!< �L�����N�^�[�I���|�X�^�[�p�G�t�F�N�g�J�E���^
		int m_direction[2] = { 0 }; //!< �L�����N�^�[�I���|�X�^�[�p�X�e�B�b�N�����L�^�ϐ�
		int m_width, m_height;
		float m_freq;   //!<�@EQ�p�Ւf���g��
	};
}