/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeOperation.h.
 *
 * @brief	����������[�h
 * @author	Takuya Fujisawa
 */
#pragma once
#include "ModeBase.h"

namespace illumism
{
	/**
 * @class	ModeOperation
 *
 * @brief	����������[�h
 *
 */
	class ModeOperation : public ModeBase
	{
	public:
		/**
		 * @fn	ModeOperation::ModeOperation(int _p1, int _p2);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_p1	P1�I���L�����N�^�[
		 * @param 	_p2	P2�I���L�����N�^�[
		 */
		ModeOperation(int _p1, int _p2);

		/**
		 * @fn	virtual bool ModeOperation::Initialize(Game& _game);
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
		 * @fn	virtual bool ModeOperation::Terminate(Game& _game);
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
		 * @fn	virtual bool ModeOperation::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	���Z���������̉�
		 */
		virtual bool Process(Game& _game);

		/**
		 * @fn	virtual bool ModeOperation::Draw(Game& _game);
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
		 * @fn	void ModeOperation::Input(Game& _game);
		 *
		 * @brief	�R���g���[���[������͂����m���A�w�胂�[�h�ֈڍs
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Input(Game& _game);

		/**
		 * @fn	void ModeOperation::NextMode(Game& _game);
		 *
		 * @brief	�w�胂�[�h�ֈڍs
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void NextMode(Game& _game);

	private:
		int m_graph;	//!< �摜�n���h��
		bool m_once_flag;   //!< <��x�̂ݍs���鏈���p�t���O
		int m_press_count;  //!< <�{�^����������Ă���̌o�ߎ��ԃJ�E���^
		int m_selectchara_state[2] = { 0 }; //!<�L�����I�����[�h�őI�����Ă����L�����ۑ��p�ϐ�
	};
}