/**
 * @file	AMG_Summer_Co_Production_2020\script\PlayerUIController.h.
 *
 * @brief	ゲームモード内のプレイヤーに関するUIを管理するクラス
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
	  * @brief	ゲームモード内のプレイヤーに関するUIを管理するクラス
	  */
	class PlayerUIController
	{
	public:
		PlayerUIController();
		~PlayerUIController();

		/**
		 * @fn	void PlayerUIController::Process(Game& _game);
		 *
		 * @brief	UIで使用するプレイヤーパラメータを更新
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void PlayerUIController::Draw(Game& _game);
		 *
		 * @brief	プレイヤーUIを描画
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game);

		/**
		 * @brief プレイヤーUIのアイコンを設定.
		 * 
		 * @param _p1chara　P1キャラ種類
		 * @param _p2chara　P2キャラ種類
		 */
		void SetPlayerIcon(const int _p1chara, const int _p2chara);


		/** @brief	　獲得ポイントを表示 */
		PointNumber_UI m_pointUI;

		/** @brief　残りHPを表示 */
		HPbar_UI m_hpbarUI;

		/** @brief	　飛行時間を表示 */
		Flybar_UI m_flybarUI;

		/** @brief	　必殺技ゲージを表示 */
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