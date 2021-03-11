/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeTitle.h.
 *
 * @brief	タイトル表示モード
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ModeBase.h"
#include"../Sound/PlayWAVE.h"

namespace illumism
{
	/**
 * @class	ModeTitle
 *
 * @brief	タイトル表示モード
 *
 */
	class ModeTitle : public ModeBase
	{
	public:
		/**
		 * @fn	virtual bool ModeTitle::Initialize(Game& _game);
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
		 * @fn	virtual bool ModeTitle::Terminate(Game& _game);
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
		 * @fn	virtual bool ModeTitle::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 *
		 * @returns	演算処理成功の可否
		 */
		virtual bool Process(Game& _game);

		/**
		 * @fn	virtual bool ModeTitle::Draw(Game& _game);
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
		 * @fn	void ModeTitle::Init();
		 *
		 * @brief	メンバ変数の初期化
		 *
		 */
		void Init();

		/**
		 * @fn	void ModeTitle::Input(Game& _game);
		 *
		 * @brief	コントローラーから入力を検知し、メインメニューモードへ移行
		 *
		 * @param [in,out]	_game	The game.
		 */
		void Input(Game& _game);

		/**
		 * @fn	void ModeTitle::NextMode(Game& _game);
		 *
		 * @brief	メインメニューモードへ移行
		 *
		 * @param [in,out]	_game	The game.
		 */
		void NextMode(Game& _game);

		/**
		 * @fn	void ModeTitle::PlayBGM(Game& _game);
		 *
		 * @brief	BGMを再生
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void PlayBGM(Game& _game);

	private:
		int m_graph;	//!< 画像ハンドル
		int m_press_graph;
		int m_press_count;  //!< <ボタンが押されてからの経過時間カウンタ
		bool m_once_flag;   //!< <一度のみ行われる処理用フラグ
		float m_freq;   //!< EQ用遮断周波数
	};
}