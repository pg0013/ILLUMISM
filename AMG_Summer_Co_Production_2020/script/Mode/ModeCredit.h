/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeCredit.h
 *
 * @brief	�N���W�b�g��ʂ�\�����郂�[�h
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ModeBase.h"

namespace illumism
{
	/**
	 * @class	ModeCredit
	 *
	 * @brief	�N���W�b�g��ʂ�\�����郂�[�h
	 *
	 */
	class ModeCredit : public ModeBase
	{
	public:
		/**
		 * @fn	virtual bool ModeCredit::Initialize(Game& _game);
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
		 * @fn	virtual bool ModeCredit::Terminate(Game& _game);
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
		 * @fn	virtual bool ModeCredit::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	���Z���������̉�
		 */
		virtual bool Process(Game& _game);

		/**
		 * @fn	virtual bool ModeCredit::Draw(Game& _game);
		 *�@
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	�`�揈�������̉�
		 */
		virtual bool Draw(Game& _game);

	private:
		//!<�摜�n���h��
		int m_graph;
		int m_overlay_graph;
		int m_credit_graph;

		int m_press_count;  //!< <�{�^����������Ă���̌o�ߎ��ԃJ�E���^
		bool m_once_flag;   //!< <��x�̂ݍs���鏈���p�t���O
	};
}