/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeTutorial.h.
 *
 * @brief	チュートリアル表示モード
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ModeBase.h"

namespace illumism
{
	/**
 * @class	ModeTutorial
 *
 * @brief	チュートリアル表示モード
 *
 */
	class ModeTutorial : public ModeBase
	{
	public:
		/**
		 * @fn	virtual bool ModeTutorial::Initialize(Game& _game);
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
		 * @fn	virtual bool ModeTutorial::Terminate(Game& _game);
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
		 * @fn	virtual bool ModeTutorial::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 *
		 * @returns	演算処理成功の可否
		 */
		virtual bool Process(Game& _game);

		/**
		 * @fn	virtual bool ModeTutorial::Draw(Game& _game);
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
		 * @fn	void ModeTutorial::Init();
		 *
		 * @brief	メンバ変数の初期化
		 *
		 */
		void Init();

		/**
		 * @fn	void ModeTutorial::Input(Game& _game);
		 *
		 * @brief	コントローラーから入力を検知し、メインメニューモードへ移行
		 *
		 * @param [in,out]	_game	The game.
		 */
		void Input(Game& _game);

		/**
		 * @fn	void ModeTutorial::NextMode(Game& _game);
		 *
		 * @brief	メインメニューモードへ移行
		 *
		 * @param [in,out]	_game	The game.
		 */
		void NextMode(Game& _game);

	private:
		int m_graph;	//!< 画像ハンドル
		int m_tutorial1_graph, m_tutorial2_graph;
		int m_tutorial_mode, m_premode;//< 画像切り替え用状態遷移変数
		int m_press_count;  //!< <ボタンが押されてからの経過時間カウンタ
		bool m_once_flag;   //!< <一度のみ行われる処理用フラグ
	};
}