/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeCredit.h
 *
 * @brief	クレジット画面を表示するモード
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ModeBase.h"

namespace illumism
{
	/**
	 * @class	ModeCredit
	 *
	 * @brief	クレジット画面を表示するモード
	 *
	 */
	class ModeCredit : public ModeBase
	{
	public:
		/**
		 * @fn	virtual bool ModeCredit::Initialize(Game& _game);
		 *
		 * @brief	初期化処理
		 * @detail	ModeServer接続時に一度だけ呼ばれる
		 *
		 * @param [in,out]	_game	Gameクラスの参照
		 *
		 * @returns	初期化成功の可否
		 */
		virtual bool Initialize(Game& _game);

		/**
		 * @fn	virtual bool ModeCredit::Terminate(Game& _game);
		 *
		 * @brief	終了処理
		 * @detail	ModeServerから削除される際、一度だけ呼ばれる
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 *
		 * @returns	終了処理成功の可否
		 */
		virtual bool Terminate(Game& _game);

		/**
		 * @fn	virtual bool ModeCredit::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 *
		 * @returns	演算処理成功の可否
		 */
		virtual bool Process(Game& _game);

		/**
		 * @fn	virtual bool ModeCredit::Draw(Game& _game);
		 *　
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 *
		 * @returns	描画処理成功の可否
		 */
		virtual bool Draw(Game& _game);

	private:
		//!<画像ハンドル
		int m_graph;
		int m_overlay_graph;
		int m_credit_graph;

		int m_press_count;  //!< <ボタンが押されてからの経過時間カウンタ
		bool m_once_flag;   //!< <一度のみ行われる処理用フラグ
	};
}