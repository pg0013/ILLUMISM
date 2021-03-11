/**
 * @file	AMG_Summer_Co_Production_2020\script\CoopMoveController.h.
 *
 * @brief	���͋Z�����Ŕ�������SPMoveObject���Ǘ�����N���X
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"
#include<cmath>

namespace illumism
{
	/**
	 * @class	CoopMoveController
	 *
	 * @brief	SPMoveObject���Ǘ�����N���X
	 *
	 */
	class CoopMoveController
	{
	public:
		CoopMoveController();
		~CoopMoveController();

		/**
		 * @fn	void CoopMoveController::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void CoopMoveController::SetPushTime(int _num, int _frame);
		 *
		 * @brief	�v���C���[��LB���������t���[�����L�^
		 *
		 * @param 	_num  	�v���C���[�ԍ�.
		 * @param 	_frame	LB���������t���[��.
		 */
		void SetPushTime(int _num, int _frame);

		/**
		 * @fn	void CoopMoveController::SetDiffTime(int _pushtime[2]);
		 *
		 * @brief	2�l�̃v���C���[��LB�����������Ԃ̍������L�^
		 *
		 * @param 	_pushtime	�e�v���C���[��LB������������.
		 */
		void SetDiffTime(int _pushtime[2]);

	private:
		int m_pushtime[2];  //!< ���������Ԃ��L�^
		int m_difftime; //!< �v���C���[��LB�����������Ԃ̍���
	};
}