/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeSelectChara.h.
 *
 * @brief	プレイキャラクター選択モード
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ModeBase.h"

namespace illumism
{
	/**
	  * @class	ModeSelectChara
	  *
	  * @brief	キャラクター選択モードクラス
	  *
	  */
	class ModeSelectChara : public ModeBase
	{
	public:
		/**
		 * @fn	ModeSelectChara::ModeSelectChara(int _p1, int _p2 ,bool _startEQ);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_p1			プレイヤー１選択キャラ（他モードから遷移時用）
		 * @param 	_p2			プレイヤー2選択キャラ（他モードから遷移時用）
		 * @param 	_startEQ	モード開始時にEQを行うフラグ（メインメニューモードからのみtrue）
		 */
		ModeSelectChara(int _p1, int _p2, bool _startEQ);

		/**
		 * @fn	virtual bool ModeSelectChara::Initialize(Game& _game);
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
		 * @fn	virtual bool ModeSelectChara::Terminate(Game& _game);
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
		 * @fn	virtual bool ModeSelectChara::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 *
		 * @returns	演算処理成功の可否
		 */
		virtual bool Process(Game& _game);

		/**
		 * @fn	virtual bool ModeSelectChara::Draw(Game& _game);
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 *
		 * @returns	描画処理成功の可否
		 */
		virtual bool Draw(Game& _game);

		/**
		 * @fn	void ModeSelectChara::Input(Game& _game);
		 *
		 *
		 * @brief	コントローラーから入力を検知し、画面遷移を行う
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 */
		void Input(Game& _game);

		/**
		 * @fn	void ModeSelectChara::State(Game& _game);
		 *
		 * @brief	状態遷移を管理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照.
		 */
		void State(Game& _game);

	private:

		/**
		 * @fn	void ModeSelectChara::Init();
		 *
		 * @brief	初期化処理
		 */
		void Init();

		/**
		 * @fn	void ModeSelectChara::EQFade(Game& _game);
		 *
		 * @brief	モード開始,終了時にEQをかける
		 *
		 * @param [in,out]	_game	ゲームクラスの参照.
		 */
		void EQFade(Game& _game);

		/**
		 * @fn	void ModeSelectChara::Exit(Game& _game);
		 *
		 * @brief	キャラ選択モードを終了し、メインメニューモードへ遷移
		 *
		 * @param [in,out]	_game	ゲームクラスの参照.
		 */
		void Exit(Game& _game);

		/**
		 * @fn	void ModeSelectChara::Operation(Game& _game);
		 *
		 * @brief	操作説明モードへ遷移
		 *
		 * @param [in,out]	_game	ゲームクラスの参照.
		 */
		void Operation(Game& _game);

		/**
		 * @fn	void ModeSelectChara::Ready(Game& _game);
		 *
		 * @brief	ゲーム開始状態へ状態遷移を移行
		 *
		 * @param [in,out]	_game	ゲームクラスの参照.
		 */
		void Ready(Game& _game);

		/**
		 * @fn	void ModeSelectChara::DrawOperationButton();
		 *
		 * @brief	操作説明ボタンを描画
		 *
		 */
		void DrawOperationButton();

		/**
		 * @fn	void ModeSelectChara::DrawExitButton();
		 *
		 * @brief	Exitボタンを描画
		 *
		 */
		void DrawExitButton();

		/**
		 * @fn	void ModeSelectChara::DrawSelectArrow();
		 *
		 * @brief	キャラ選択矢印を描画
		 *
		 */
		void DrawSelectArrow();

		/**
		 * @fn	void ModeSelectChara::DrawSelectLight();
		 *
		 * @brief	キャラ選択決定時にライトを描画
		 *
		 */
		void DrawSelectLight();

		/**
		 * @fn	void ModeSelectChara::DrawReadySign();
		 *
		 * @brief	READY?画像を描画
		 *
		 */
		void DrawReadySign();

		/**
		 * @fn	void ModeSelectChara::SelectCharaAnim();
		 *
		 * @brief	キャラクター選択時のアニメーション描画処理
		 *
		 */
		void SelectCharaAnim();

		/**
		 * @fn	void ModeSelectChara::SelectAutoChara();
		 *
		 * @brief	選択キャラが被ったときに、P1P2カラーを自動で選択する処理
		 *
		 */
		void SelectAutoChara();

		/**
		 * @fn	void ModeSelectChara::PlaySE(const char* _filename, const float _pitch, Game& _game,const float _pan = 0.0f);
		 *
		 * @brief	Play se
		 *
		 * @param 		   	_filename	音声ファイル名.
		 * @param 		   	_pitch   	再生速度.
		 * @param [in, out]	_game	 	ゲームクラスの参照.
		 * @param 		   	_pan	 	(Optional) 左右バランス（指定なしでは中央）.
		 */
		void PlaySE(const char* _filename, const float _pitch, Game& _game, const float _pan = 0.0f);

		/**
		 * @enum	MENU_STATE
		 *
		 * @brief	状態遷移用定数
		 */
		enum MENU_STATE
		{
			SELECT, EXIT, OPERATION, READY, CANSEL
		};

	private:

		int m_background_graph; //!< 画像ハンドル
		int m_charactor_graph[4] = { 0 };
		int m_exit_graph[2] = { 0 };
		int m_operation_graph[2] = { 0 };
		int m_select_under_graph;
		int m_select_arrow_graph;
		int m_light_select_back_graph;
		int m_light_select_graph[2] = { 0 };
		int m_light_ready_graph;
		int m_ready_graph;

		int m_selectchara_state[2] = { 0 }; //!< 選択キャラ保存用変数
		int m_menu_state;   //!< 状態遷移用変数

		bool m_gogame_flag; //!< READY状態からゲームシーン移行用フラグ
		bool m_once_flag;   //!< <一度のみ行われる処理用フラグ
		bool m_exit_flag;   //!< メインメニューモードへ移行用フラグ
		bool m_ready_flag[2] = { 0 };   //!< キャラクター選択済みフラグ
		bool m_startEQ_flag;	//!< モード開始時にEQを行うフラグ

		float m_cancel_count[2] = { 0.0f }; //!<Bボタン長押しカウンタ
		int m_press_count; //!< ボタンが押されてからの経過時間カウンタ
		int m_press_frame;  //!< エフェクト用ボタンを押したフレーム保存変数
		int m_anim_count[2] = { 0 };	//!< キャラクター選択ポスター用エフェクトカウンタ
		int m_direction[2] = { 0 }; //!< キャラクター選択ポスター用スティック方向記録変数
		int m_width, m_height;
		float m_freq;   //!<　EQ用遮断周波数
	};
}