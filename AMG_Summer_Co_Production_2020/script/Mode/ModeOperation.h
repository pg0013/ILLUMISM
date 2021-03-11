/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeOperation.h.
 *
 * @brief	操作説明モード
 * @author	Takuya Fujisawa
 */
#pragma once
#include "ModeBase.h"

namespace illumism
{
	/**
 * @class	ModeOperation
 *
 * @brief	操作説明モード
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
		 * @param 	_p1	P1選択キャラクター
		 * @param 	_p2	P2選択キャラクター
		 */
		ModeOperation(int _p1, int _p2);

		/**
		 * @fn	virtual bool ModeOperation::Initialize(Game& _game);
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
		 * @fn	virtual bool ModeOperation::Terminate(Game& _game);
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
		 * @fn	virtual bool ModeOperation::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 *
		 * @returns	演算処理成功の可否
		 */
		virtual bool Process(Game& _game);

		/**
		 * @fn	virtual bool ModeOperation::Draw(Game& _game);
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 *
		 * @returns	描画処理成功の可否
		 */
		virtual bool Draw(Game& _game);

	private:
		/**
		 * @fn	void ModeOperation::Input(Game& _game);
		 *
		 * @brief	コントローラーから入力を検知し、指定モードへ移行
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Input(Game& _game);

		/**
		 * @fn	void ModeOperation::NextMode(Game& _game);
		 *
		 * @brief	指定モードへ移行
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void NextMode(Game& _game);

	private:
		int m_graph;	//!< 画像ハンドル
		bool m_once_flag;   //!< <一度のみ行われる処理用フラグ
		int m_press_count;  //!< <ボタンが押されてからの経過時間カウンタ
		int m_selectchara_state[2] = { 0 }; //!<キャラ選択モードで選択していたキャラ保存用変数
	};
}