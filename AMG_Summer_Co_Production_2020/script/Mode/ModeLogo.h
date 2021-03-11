/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeLogo.h.
 *
 * @brief	AMGとチームロゴ表示モード
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ModeBase.h"

namespace illumism
{
	namespace   //!< ロゴ画像指定用定数
	{
		constexpr int AMG_LOGO = 0;
		constexpr int TEAM_LOGO = 1;
	}

	/**
	 * @class	ModeLogo
	 *
	 * @brief	A mode logo.
	 *
	 */
	class ModeLogo : public ModeBase
	{
	public:
		/**
		 * @fn	ModeLogo::ModeLogo(int _num);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_num	表示するロゴを選択
		 * 								0 : AMGロゴ
		 * 								1 : チームロゴ
		 */
		ModeLogo(int _num);

		/**
		 * @fn	virtual bool ModeLogo::Initialize(Game& _game);
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
		 * @fn	virtual bool ModeLogo::Terminate(Game& _game);
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
		 * @fn	virtual bool ModeLogo::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 *
		 * @returns	演算処理成功の可否
		 */
		virtual bool Process(Game& _game);

		/**
		 * @fn	virtual bool ModeLogo::Draw(Game& _game);
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
		 * @fn	void ModeLogo::Input(Game& _game);
		 *
		 * @brief	コントローラーから入力を検出
		 *
		 * @param [in,out]	_game	The game.
		 */
		void Input(Game& _game);

		/**
		 * @fn	void ModeLogo::NextMode(Game& _game);
		 *
		 * @brief	モード開始から4秒後にフェードアウトへ移行
		 * 				モード開始から6秒後に次のモードへ遷移
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Transition(Game& _game);

		/**
		 * @fn	void ModeLogo::SkipLogoMode(Game& _game);
		 *
		 * @brief	Aボタンが押されたら1秒後に次モードに移行
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void SkipLogoMode(Game& _game);

	protected:
		/// <画像ハンドル.
		int m_graph;
		int logonum;

		int m_press_count;  //!< <ボタンが押されてからの経過時間カウンタ
		bool m_once_flag;   //!< <一度のみ行われる処理用フラグ
	};
}