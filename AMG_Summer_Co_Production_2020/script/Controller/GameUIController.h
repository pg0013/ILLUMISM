/**
 * @file	AMG_Summer_Co_Production_2020\script\GameUIController.h.
 *
 * @brief	�Q�[�����[�h��UI���Ǘ�
 * @author	Takuya Fujisawa 
 */

#pragma once
#include"PlayerUIController.h"

namespace illumism
{
	class Game;	//��d�C���N���[�h�h�~

	/**
	 * @class	GameUIController
	 *
	 * @brief	�Q�[������GameUIController���Ǘ�����N���X
	 */
	class GameUIController
	{
	public:
		GameUIController();
		~GameUIController();

		/**
		 * @fn	void GameUIController::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void GameUIController::Draw(Game& _game);
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game);

		PlayerUIController m_playerUI;  //!< �v���C���[�\��UI
	};
}