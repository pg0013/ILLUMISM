/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeTutorial.h.
 *
 * @brief	�`���[�g���A���\�����[�h
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ModeBase.h"

namespace illumism
{
	/**
 * @class	ModeTutorial
 *
 * @brief	�`���[�g���A���\�����[�h
 *
 */
	class ModeTutorial : public ModeBase
	{
	public:
		/**
		 * @fn	virtual bool ModeTutorial::Initialize(Game& _game);
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
		 * @fn	virtual bool ModeTutorial::Terminate(Game& _game);
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
		 * @fn	virtual bool ModeTutorial::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	���Z���������̉�
		 */
		virtual bool Process(Game& _game);

		/**
		 * @fn	virtual bool ModeTutorial::Draw(Game& _game);
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	�`�揈�������̉�
		 */
		virtual bool Draw(Game& _game);

	private:

		/**
		 * @fn	void ModeTutorial::Init();
		 *
		 * @brief	�����o�ϐ��̏�����
		 *
		 */
		void Init();

		/**
		 * @fn	void ModeTutorial::Input(Game& _game);
		 *
		 * @brief	�R���g���[���[������͂����m���A���C�����j���[���[�h�ֈڍs
		 *
		 * @param [in,out]	_game	The game.
		 */
		void Input(Game& _game);

		/**
		 * @fn	void ModeTutorial::NextMode(Game& _game);
		 *
		 * @brief	���C�����j���[���[�h�ֈڍs
		 *
		 * @param [in,out]	_game	The game.
		 */
		void NextMode(Game& _game);

	private:
		int m_graph;	//!< �摜�n���h��
		int m_tutorial1_graph, m_tutorial2_graph;
		int m_tutorial_mode, m_premode;//< �摜�؂�ւ��p��ԑJ�ڕϐ�
		int m_press_count;  //!< <�{�^����������Ă���̌o�ߎ��ԃJ�E���^
		bool m_once_flag;   //!< <��x�̂ݍs���鏈���p�t���O
	};
}