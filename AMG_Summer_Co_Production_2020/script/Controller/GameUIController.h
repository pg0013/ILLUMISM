/**
 * @file	AMG_Summer_Co_Production_2020\script\GameUIController.h.
 *
 * @brief	ゲームモードのUIを管理
 * @author	Takuya Fujisawa 
 */

#pragma once
#include"PlayerUIController.h"

namespace illumism
{
	class Game;	//二重インクルード防止

	/**
	 * @class	GameUIController
	 *
	 * @brief	ゲーム内のGameUIControllerを管理するクラス
	 */
	class GameUIController
	{
	public:
		GameUIController();
		~GameUIController();

		/**
		 * @fn	void GameUIController::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void GameUIController::Draw(Game& _game);
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game);

		PlayerUIController m_playerUI;  //!< プレイヤー表示UI
	};
}