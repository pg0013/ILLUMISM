/**
 * @file	AMG_Summer_Co_Production_2020\script\CoopMoveController.h.
 *
 * @brief	協力技成功で発生するSPMoveObjectを管理するクラス
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
	 * @brief	SPMoveObjectを管理するクラス
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
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void CoopMoveController::SetPushTime(int _num, int _frame);
		 *
		 * @brief	プレイヤーがLBを押したフレームを記録
		 *
		 * @param 	_num  	プレイヤー番号.
		 * @param 	_frame	LBを押したフレーム.
		 */
		void SetPushTime(int _num, int _frame);

		/**
		 * @fn	void CoopMoveController::SetDiffTime(int _pushtime[2]);
		 *
		 * @brief	2人のプレイヤーがLBを押した時間の差分を記録
		 *
		 * @param 	_pushtime	各プレイヤーがLBを押した時間.
		 */
		void SetDiffTime(int _pushtime[2]);

	private:
		int m_pushtime[2];  //!< 押した時間を記録
		int m_difftime; //!< プレイヤーがLBを押した時間の差分
	};
}