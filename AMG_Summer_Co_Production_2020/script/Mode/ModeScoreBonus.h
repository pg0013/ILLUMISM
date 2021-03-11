/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeScoreBonus.h.
 *
 * @brief	スコアボーナス表示モード
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ModeBase.h"
#include"ModeGame.h"
#include"../UI/BonusPoint.h"

namespace illumism
{
	namespace   //!<ボーナスポイント用定数
	{
		constexpr int BONUS_POINT = 200;
	}

	/**
	 * @class	ModeScoreBonus
	 *
	 * @brief	スコアボーナス表示モード
	 *
	 */
	class ModeScoreBonus : public ModeBase
	{
	public:

		/**
		 * @fn	ModeScoreBonus::ModeScoreBonus(const int _point1, const int _point2, const int _P1charactor, const int _P2charactor,ModeGame::BONUS_PARAM _player1, ModeGame::BONUS_PARAM _player2);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_point1			プレイヤー１所持ポイント
		 * @param 	_point2			プレイヤー２所持ポイント
		 * @param 	_P1charactor	プレイヤー１選択キャラ
		 * @param 	_P2charactor	プレイヤー２選択キャラ
		 * @param 	_player1		プレイヤー１ボーナスパラメータ
		 * @param 	_player2		プレイヤー2ボーナスパラメータ
		 */
		ModeScoreBonus(const int _point1, const int _point2, const int _P1charactor, const int _P2charactor, ModeGame::BONUS_PARAM _player1, ModeGame::BONUS_PARAM _player2);

		/**
		 * @fn	virtual bool ModeScoreBonus::Initialize(Game& _game);
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
		 * @fn	virtual bool ModeScoreBonus::Terminate(Game& _game);
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
		 * @fn	virtual bool ModeScoreBonus::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 *
		 * @returns	演算処理成功の可否
		 */
		virtual bool Process(Game& _game);

		/**
		 * @fn	virtual bool ModeScoreBonus::Draw(Game& _game);
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
		 * @fn	void ModeScoreBonus::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();
		/**
		 * @fn	void ModeScoreBonus::SetCharaGraph(int _player1, int _player2);
		 *
		 * @brief	プレイヤーが選択したキャラの待機アニメーションとアピールアニメーションを設定
		 *
		 * @param 	_player1	プレイヤー１選択キャラ
		 * @param 	_player2	プレイヤー２選択キャラ
		 */
		void SetCharaGraph(int _player1, int _player2);

		/**
		 * @fn	void ModeScoreBonus::DrawBonusSign(Game& _game);
		 *
		 * @brief	ボーナス名画像とボーナス加算エフェクトを、指定時間に表示
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void DrawBonusSign(Game& _game);

		/**
		 * @fn	void ModeScoreBonus::DrawCharactor();
		 *
		 * @brief	キャラクターを描画
		 */
		void DrawCharactor();

		/**
		 * @fn	void ModeScoreBonus::DrawSpotlight();
		 *
		 * @brief	Draw spotlight
		 *
		 */
		void DrawSpotlight();

		/**
		 * @fn	void ModeScoreBonus::AddBonusPoint();
		 *
		 * @brief	ボーナスパラメータを評価し、スコアボーナスを加算
		 *
		 */
		void AddBonusPoint();

		/**
		 * @fn	void ModeScoreBonus::PlaySE(const char* _filename, const float _pitch, Game & _game);
		 *
		 * @brief	効果音再生
		 *
		 * @param 		   	_filename	音声ファイル名.
		 * @param 		   	_pitch   	再生速度.
		 * @param [in, out]	_game	 	ゲームクラスの参照.
		 */
		void PlaySE(const char* _filename, const float _pitch, Game& _game);

	private:
		int m_player_point[2] = { 0 };  //!< プレイヤー獲得ポイント
		ModeGame::BONUS_PARAM m_bonus_param[2]; //!< 各プレイヤーボーナスパラメータ


		BonusPoint bonuspoint1; //!< ボーナスポイント描画クラス
		BonusPoint bonuspoint2;
		BonusPoint bonuspoint3;


		int m_background_graph; //!< 画像ハンドル
		int m_bg_bonus_graph;
		int m_spotlight_graph;
		int m_player_charactor_graph[2] = { 0 };
		int m_charactor1_graph[30] = { 0 };
		int m_charactor2_graph[30] = { 0 };
		int m_appealchara1_graph[40] = { 0 };
		int m_appealchara2_graph[40] = { 0 };
		int m_player_charactor[2] = { 0 };
		int m_bonus_graph[3] = { 0 };
		int m_num_graph[3] = { 0 };
		int m_bonus_point_graph;

		bool  m_boss_bonus, m_combo_bonus, m_death_bonus;//!< ボーナス加算処理を行うフラグ
	};
}