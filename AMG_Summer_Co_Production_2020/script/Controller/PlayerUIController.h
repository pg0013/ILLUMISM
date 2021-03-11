/**
 * @file	AMG_Summer_Co_Production_2020\script\PlayerUIController.h.
 *
 * @brief	�Q�[�����[�h���̃v���C���[�Ɋւ���UI���Ǘ�����N���X
 * @author	Takuya Fujisawa
 */

#pragma once
#include"../UI/PointNumber_UI.h"
#include"../UI/HPbar_UI.h"
#include"../UI/Flybar_UI.h"
#include"../UI/SPmove_UI.h"

namespace illumism
{
	/**
	  * @class	PlayerUIController
	  *
	  * @brief	�Q�[�����[�h���̃v���C���[�Ɋւ���UI���Ǘ�����N���X
	  */
	class PlayerUIController
	{
	public:
		PlayerUIController();
		~PlayerUIController();

		/**
		 * @fn	void PlayerUIController::Process(Game& _game);
		 *
		 * @brief	UI�Ŏg�p����v���C���[�p�����[�^���X�V
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void PlayerUIController::Draw(Game& _game);
		 *
		 * @brief	�v���C���[UI��`��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game);

		/**
		 * @brief �v���C���[UI�̃A�C�R����ݒ�.
		 * 
		 * @param _p1chara�@P1�L�������
		 * @param _p2chara�@P2�L�������
		 */
		void SetPlayerIcon(const int _p1chara, const int _p2chara);


		/** @brief	�@�l���|�C���g��\�� */
		PointNumber_UI m_pointUI;

		/** @brief�@�c��HP��\�� */
		HPbar_UI m_hpbarUI;

		/** @brief	�@��s���Ԃ�\�� */
		Flybar_UI m_flybarUI;

		/** @brief	�@�K�E�Z�Q�[�W��\�� */
		SPmove_UI m_spmoveUI;

	private:
		int m_x, m_y;
		int m_width, m_height;
		int m_graph_1, m_graph_2, m_graph_4, m_graph_5_1, m_graph_5_2,
			m_graph_6, m_graph_7, m_graph_8, m_graph_9;
		int m_graph_10[2] = { 0 };
		bool m_once_flag;
	};
} 