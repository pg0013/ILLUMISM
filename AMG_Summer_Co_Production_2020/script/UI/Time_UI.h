/**
 * @file	AMG_Summer_Co_Production_2020\script\Time_UI.h.
 *
 * @brief	ゲームモードのプレイ時間を表示
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"
#include"DxLib.h"

namespace illumism
{
	class Game;//二重インクルード防止

	namespace
	{
		constexpr int GAMETIME = 3600 * 4 + 60 * 18 - 315;  //!< 試合時間
		constexpr int BOSSTIME = GAMETIME - (80 - 12) * 60; //!< ボス登場時間
	}

	/**
	 * @class	Time_UI
	 *
	 * @brief	試合時間を表示するUIのクラス
	 *
	 */
	class Time_UI : public ObjectBase
	{
	public:
		Time_UI();
		~Time_UI();

		/**
		 * @fn	virtual ObjectBase::OBJECT_TYPE Time_UI::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual ObjectBase::OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::UI; }

		/**
		 * @fn	void Time_UI::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void Time_UI::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void Time_UI::Draw(Game& _game) override;
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void Time_UI::GenerateBOSS(Game& _game);
		 *
		 * @brief	ボスを生成
		 *
		 * @param [in,out]	_game	The game.
		 */
		void GenerateBOSS(Game& _game);

	private:
		int m_graph[11];	//!< 画像ハンドル
		int m_frame_graph;

		int m_GameTime; //!< プレイ時間
		int m_now_time; //!< 残り時間

		int m_minutes;  //!<	残り時間[minutes]
		int m_second;   //!< 残り時間[second]

		bool onceflag;  //!< 一度だけ呼ばれる処理用フラグ
	};
}