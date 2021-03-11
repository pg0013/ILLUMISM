/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeLogo.h.
 *
 * @brief	AMG�ƃ`�[�����S�\�����[�h
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ModeBase.h"

namespace illumism
{
	namespace   //!< ���S�摜�w��p�萔
	{
		constexpr int AMG_LOGO = 0;
		constexpr int TEAM_LOGO = 1;
	}

	/**
	 * @class	ModeLogo
	 *
	 * @brief	A mode logo.
	 *
	 */
	class ModeLogo : public ModeBase
	{
	public:
		/**
		 * @fn	ModeLogo::ModeLogo(int _num);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_num	�\�����郍�S��I��
		 * 								0 : AMG���S
		 * 								1 : �`�[�����S
		 */
		ModeLogo(int _num);

		/**
		 * @fn	virtual bool ModeLogo::Initialize(Game& _game);
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
		 * @fn	virtual bool ModeLogo::Terminate(Game& _game);
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
		 * @fn	virtual bool ModeLogo::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	���Z���������̉�
		 */
		virtual bool Process(Game& _game);

		/**
		 * @fn	virtual bool ModeLogo::Draw(Game& _game);
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
		 * @fn	void ModeLogo::Input(Game& _game);
		 *
		 * @brief	�R���g���[���[������͂����o
		 *
		 * @param [in,out]	_game	The game.
		 */
		void Input(Game& _game);

		/**
		 * @fn	void ModeLogo::NextMode(Game& _game);
		 *
		 * @brief	���[�h�J�n����4�b��Ƀt�F�[�h�A�E�g�ֈڍs
		 * 				���[�h�J�n����6�b��Ɏ��̃��[�h�֑J��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Transition(Game& _game);

		/**
		 * @fn	void ModeLogo::SkipLogoMode(Game& _game);
		 *
		 * @brief	A�{�^���������ꂽ��1�b��Ɏ����[�h�Ɉڍs
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void SkipLogoMode(Game& _game);

	protected:
		/// <�摜�n���h��.
		int m_graph;
		int logonum;

		int m_press_count;  //!< <�{�^����������Ă���̌o�ߎ��ԃJ�E���^
		bool m_once_flag;   //!< <��x�̂ݍs���鏈���p�t���O
	};
}