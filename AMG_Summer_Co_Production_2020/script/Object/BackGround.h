/**
 * @file	AMG_Summer_Co_Production_2020\script\BackGround.h.
 *
 * @brief	ゲームモードの背景オブジェクトクラス
 * @author	Takuya Fujisawa
 */

#pragma once
#include"ObjectBase.h"

namespace illumism
{
	class Game;//!<二重インクルード防止

	/**
	 * @class	BackGround
	 *
	 * @brief	ゲームモードの背景クラス
	 *
	 */
	class BackGround
	{
	public:
		BackGround();
		~BackGround();

		/**
		 * @fn	void BackGround::Draw(Game& _game);
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game);

		/**
		 * @fn	void BackGround::DrawAudience(Game& _game);
		 *
		 * @brief	観客のアニメーションを描画
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void DrawAudience(Game& _game);

	private:
		int m_background_graph; //!< 画像ハンドル
		int m_arch_graph[4] = { 0 };
		int m_seat_graph[4] = { 0 };
		int m_penlight_graph[4] = { 0 };
		int m_stage_graph;
		int m_spot_graph[2];
		int m_audience_graph;
		int m_vignette_graph;

		int m_x, m_y;
		int m_width, m_height;
	};
}