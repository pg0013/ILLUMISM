/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeMainMenu.h.
 *
 * @brief	メインメニューモード
 * @author	Takuya Fujisawa
 */

#pragma once
#include"ModeBase.h"
#include"../Sound/PlayWAVE.h"

namespace illumism
{
	/**
	 * @class	ModeMainMenu
	 *
	 * @brief	メインメニューモード
	 *
	 */
	class ModeMainMenu :
		public ModeBase
	{
	public:

		/**
		 * @fn	ModeMainMenu::ModeMainMenu(int _menu_state,bool _playbgm);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_menu_state	モード開始時に選択されているメニューを指定
		 * 										BATTLE : 0, TUTORIAL : 1, EXIT : 2, CREDIT : 3
		 * @param 	_playbgm   	BGM再生用フラグ（リザルト画面から遷移したとき用）
		 */
		ModeMainMenu(int _menu_state, bool _playbgm);

		/**
		 * @fn	virtual bool ModeMainMenu::Initialize(Game& _game);
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
		 * @fn	virtual bool ModeMainMenu::Terminate(Game& _game);
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
		 * @fn	virtual bool ModeMainMenu::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 *
		 * @returns	演算処理成功の可否
		 */
		virtual bool Process(Game& _game);

		/**
		 * @fn	virtual bool ModeMainMenu::Draw(Game& _game);
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 *
		 * @returns	描画処理成功の可否
		 */
		virtual bool Draw(Game& _game);

		/**
		 * @fn	void ModeMainMenu::Input(Game& _game);
		 *
		 * @brief	コントローラーからボタン入力を検知し、メニューの遷移を行う
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 */
		void Input(Game& _game);

		/**
		 * @fn	void ModeMainMenu::State(Game& _game);
		 *
		 * @brief	メニューの状態遷移を管理
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 */
		void State(Game& _game);

		/**
		 * @enum	MENU_STATE
		 *
		 * @brief	メニューの状態遷移用変数
		 */
		enum MENU_STATE
		{
			BATTLE, TUTORIAL, EXIT, CREDIT, BACKTITLE
		};
	private:
		/**
		 * @fn	void ModeMainMenu::Battle(Game& _game);
		 *
		 * @brief	バトルメニューへ遷移
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 */
		void Battle(Game& _game);

		/**
		 * @fn	void ModeMainMenu::Tutorial(Game& _game);
		 *
		 * @brief	チュートリアルメニューへ遷移
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 */
		void Tutorial(Game& _game);

		/**
		 * @fn	void ModeMainMenu::Exit(Game& _game);
		 *
		 * @brief	ゲーム終了へ遷移
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 */
		void Exit(Game& _game);

		/**
		 * @fn	void ModeMainMenu::Credit(Game& _game);
		 *
		 * @brief	クレジット画面へ遷移
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 */
		void Credit(Game& _game);

		/**
		 * @fn	void ModeMainMenu::NextMode(Game& _game);
		 *
		 * @brief	選択されたモードへ遷移
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 */
		void NextMode(Game& _game);

		/**
		 * @fn	void ModeMainMenu::PlayBGM(Game& _game);
		 *
		 * @brief	リザルト画面から遷移したときにBGMを流す処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void PlayBGM(Game& _game);

		/**
		 * @fn	void ModeMainMenu::PlaySE(const char* _filename, const float _pitch, Game& _game);
		 *
		 * @brief	効果音再生
		 *
		 * @param 		  	_filename	音声ファイル名
		 * @param 		  	_pitch   	再生速度
		 * @param [in,out]	_game	 	ゲームクラスの参照
		 */
		void PlaySE(const char* _filename, const float _pitch, Game& _game);
	private:
		//!< 画像ハンドル.
		int m_background_graph;
		int m_battle_graph;
		int m_tutorial_graph;
		int m_exit_graph;
		int m_credit_graph;

		int m_width, m_height;

		int m_menu_state;   //!< 状態遷移用変数
		bool m_selected_flag;   //!<	メニュー選択済み用フラグ
		int m_press_count;   //!< <ボタンが押されてからの経過時間カウンタ
		int m_press_frame;  //!< エフェクト用フレーム記録変数

		float m_freq;   //!< ローパスフィルタの遮断周波数
		bool m_playbgm_flag;	//!<BGM再生用フラグ（リザルト画面から遷移したとき用）
	};
}