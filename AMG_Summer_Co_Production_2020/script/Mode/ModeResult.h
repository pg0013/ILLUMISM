/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeResult.h.
 *
 * @brief	リザルト画面表示モード
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ModeBase.h"
#include"../UI/ResultPoint.h"
#include"../Effect/EffectComponent.h"

namespace illumism
{
	namespace   //!<	画像表示用座標
	{
		constexpr int pos_x_P1P2 = 610;
		constexpr int pos_y_P1P2_win = 1080 / 4 + 55;
		constexpr int pos_y_P1P2_lose = 1080 / 2 + 55;
		constexpr int pos_x_banner = 0;
		constexpr int pos_y_banner_win = 1080 / 4 + 50;
		constexpr int pos_y_banner_lose = 1080 / 2 + 50;
		constexpr int pos_x_charaname = 230;
		constexpr int pos_y_charaname_win = 1080 / 4 + 135;
		constexpr int pos_y_charaname_lose = 1080 / 2 + 135;
	}

	/**
	 * @class	ModeResult
	 *
	 * @brief	リザルト画面表示用モード
	 *
	 */
	class ModeResult : public ModeBase
	{
	public:
		/**
		 * @fn	ModeResult::ModeResult(const int _point1, const int _point2, const int _P1charactor, const int _P2charactor);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_point1			プレイヤー１所持ポイント
		 * @param 	_point2			プレイヤー２所持ポイント
		 * @param 	_P1charactor	プレイヤー１選択キャラ
		 * @param 	_P2charactor	プレイヤー２選択キャラ
		 */
		ModeResult(const int _point1, const int _point2, const int _P1charactor, const int _P2charactor);

		/**
		 * @fn	virtual bool ModeResult::Initialize(Game& _game);
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
		 * @fn	virtual bool ModeResult::Terminate(Game& _game);
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
		 * @fn	virtual bool ModeResult::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 *
		 * @returns	演算処理成功の可否
		 */
		virtual bool Process(Game& _game);

		/**
		 * @fn	virtual bool ModeResult::Draw(Game& _game);
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
		 * @fn	void ModeResult::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void ModeResult::Input(Game& _game);
		 *
		 * @brief	コントローラーから入力を検知し、画面遷移を行う
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 */
		void Input(Game& _game);

		/**
		 * @fn	void ModeResult::State(Game& _game);
		 *
		 * @brief	状態遷移を管理
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 */
		void State(Game& _game);

		/**
		 * @fn	void ModeResult::Retry(Game& _game);
		 *
		 * @brief	ゲームモードへ画面遷移を行う
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 */
		void Retry(Game& _game);

		/**
		 * @fn	void ModeResult::Menu(Game& _game);
		 *
		 * @brief　メインメニューモードへ画面遷移を行う
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 */
		void Menu(Game& _game);

		/**
		 * @fn	void ModeResult::DrawBanner();
		 *
		 * @brief	Draw banner
		 *
		 */
		void DrawBanner();

		/**
		 * @fn	void ModeResult::DrawButton();
		 *
		 * @brief	Draw button
		 *
		 */
		void DrawButton();

		/**
		 * @fn	void ModeResult::DrawWinner();
		 *
		 * @brief	Draw winner
		 *
		 */
		void DrawWinner();

		/**
		 * @fn	void ModeResult::SelectCharactorGraph(const int _point1, const int _point2, const int _P1charactor, const int _P2charactor);
		 *
		 * @brief	リザルト画面で表示するキャラクター画像をプレイヤーごとに読み込み
		 *
		 * @param 	_point1			プレイヤー１所持ポイント
		 * @param 	_point2			プレイヤー２所持ポイント
		 * @param 	_P1charactor	プレイヤー１選択キャラ
		 * @param 	_P2charactor	プレイヤー２選択キャラ
		 */
		void SelectCharactorGraph(const int _point1, const int _point2, const int _P1charactor, const int _P2charactor);

		/**
		 * @fn	void ModeResult::PlaySE(Game& _game);
		 *
		 * @brief	効果音再生
		 *
		 * @param 		  	_filename	音声ファイル名
		 * @param 		  	_pitch   	再生速度
		 * @param [in,out]	_game	 	ゲームクラスの参照
		 */
		void PlaySE(const char* _filename, const float _pitch, Game& _game);

		/**
		 * @fn	void ModeResult::AnimationSE(Game& _game);
		 *
		 * @brief	リザルト画面の動きに合うようにSEを再生
		 *
		 * @param [in,out]	_game	ゲームクラスの参照.
		 */
		void AnimationSE(Game& _game);

		/**
		 * @enum	MENU_STATE
		 *
		 * @brief
		 */
		enum MENU_STATE
		{
			RETRY, MENU
		};

		ResultPoint m_result_point; //!<所持ポイント表示

		utility::EffectComponent m_move_win; //!< イージング用
		utility::EffectComponent m_move_lose;
		utility::EffectComponent m_move_winner;

		int m_x, m_y;

		int m_num_graph[2]; //!< 画像ハンドル
		int m_winbanner_graph;
		int m_losebanner_graph;
		int m_drawbanner_graph;
		int m_draw_graph;
		int m_banner_icon_graph[2] = { 0 };
		int m_backGround;
		int m_player_point[2] = { 0 };
		int m_name_graph[2] = { 0 };
		int m_menu_graph[2] = { 0 };
		int m_retry_graph[2] = { 0 };
		int m_winner_graph;
		int m_loser_graph;
		int m_winner_win_graph;

		int m_menu_state;   //!<状態遷移用変数
		bool m_selected_flag;   //!<	メニュー選択済み用フラグ
		int m_press_count;   //!< <ボタンが押されてからの経過時間カウンタ
		int m_player_charactor[2] = { 0 };  //!< プレイヤー選択キャラ保存用変数
	};
}