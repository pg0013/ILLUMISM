/**
 * @file	AMG_Summer_Co_Production_2020\script\ResultPoint.h.
 *
 * @brief	リザルト画面でポイントを表示
 * @author	Takuya Fujisawa
 */

#pragma once
#include "PointNumber_UI.h"
#include"../Effect/EffectComponent.h"

namespace illumism
{
	/**
	 * @class	ResultPoint
	 *
	 * @brief	リザルト画面でポイントを表示するクラス
	 *
	 */
	class ResultPoint : public PointNumber_UI
	{
	public:
		ResultPoint();
		~ResultPoint();

		/**
		 * @fn	void ResultPoint::Draw(const int& _player1, const int& _player2, Game& _game);
		 *
		 * @brief	描画処理
		 *
		 * @param 		  	_player1	プレイヤー１の獲得ポイント
		 * @param 		  	_player2	プレイヤー２の獲得ポイント
		 * @param [in,out]	_game  ゲームクラスの参照
		 */
		void Draw(const int& _player1, const int& _player2, Game& _game);

		/**
		 * @fn	void ResultPoint::SetPointRank();
		 *
		 * @brief	ポイントの桁の値を設定
		 *
		 */
		void SetPointRank();

		/**
		 * @fn	void ResultPoint::SetPoint(const int _player_num, const int _point);
		 *
		 * @brief	表示するポイントを設定
		 *
		 * @param 	_player_num	プレイヤー番号
		 * @param 	_point			獲得ポイント
		 */
		void SetPoint(const int _player_num, const int _point);

	private:
		int m_one_graph[10];	//!< 画像ハンドル
		int m_ten_graph[10];
		int m_hundred_graph[10];
		int m_thousand_graph[10];

		int m_point[2] = { 0 }; //!< プレイヤーのポイントを格納

		int one_rank[2];	//!< ポイントの一、十、百、千の位の数値を格納
		int ten_rank[2];
		int hundred_rank[2];
		int thousand_rank[2];

		bool more_than_1000[2]; //!< 指定数よりポイントが多いか
		bool more_than_100[2];
		bool more_than_10[2];

		utility::EffectComponent m_move_win; //!< アニメーション用イージング
		utility::EffectComponent m_move_lose;
	};
}