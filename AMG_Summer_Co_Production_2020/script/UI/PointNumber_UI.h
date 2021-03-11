/**
 * @file	AMG_Summer_Co_Production_2020\script\PointNumber_UI.h.
 *
 * @brief	プレイヤー所持ポイントを表示
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	class Game;	//二重インクルード防止

	/**
	 * @class	PointNumber_UI
	 *
	 * @brief	プレイヤー所持ポイントを表示するクラス
	 *
	 */
	class PointNumber_UI :public ObjectBase
	{
	public:
		PointNumber_UI();
		~PointNumber_UI();

		/**
		 * @fn	virtual ObjectBase::OBJECT_TYPE PointNumber_UI::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual ObjectBase::OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::UI; }

		/**
		 * @fn	void PointNumber_UI::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void PointNumber_UI::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	virtual void PointNumber_UI::Draw(Game& _game) override;
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		virtual void Draw(Game& _game) override;

		/**
		 * @fn	void PointNumber_UI::SetPoint(const int _player_num,const int _point);
		 *
		 * @brief	表示するポイント数を設定
		 *
		 * @param 	_player_num	プレイヤー番号
		 * @param 	_point	   		表示するポイント数
		 */
		void SetPoint(const int _player_num, const int _point);

		/**
		 * @fn	void PointNumber_UI::SetPointRank();
		 *
		 * @brief	ポイントの桁数の値を設定
		 *
		 */
		void SetPointRank();

	private:
		int m_graph[10];	//!< 画像ハンドル

		int m_one_graph[10];
		int m_ten_graph[10];
		int m_hundred_graph[10];
		int m_thousand_graph[10];

		int m_point[2] = { 0 }; //!< プレイヤーのポイントを格納

		int one_rank[2];	//!< ポイントの一、十、百、千の位の数値を格納
		int ten_rank[2];
		int hundred_rank[2];
		int thousand_rank[2];

		bool more_than_1000[2]; //!< 指定数より大きいかどうか
		bool more_than_100[2];
		bool more_than_10[2];
	};
}