/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeOverlay.h.
 *
 * @brief	画面遷移モード
 * 				キャプチャかフェードかを指定して画面遷移を行う
 * 				キャプチャでは、表示画面の上からオーバーレイ表示
 * 				フェードでは、画面を暗転させる
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ModeBase.h"

namespace illumism
{
	namespace
	{
		constexpr int FADE_IN = 0;
		constexpr int FADE_OUT = 1;
	}

	/**
	 * @class	ModeOverlay
	 *
	 * @brief	オーバーレイで画面遷移を行うクラス
	 *
	 */
	class ModeOverlay :
		public ModeBase
	{
	public:
		/**
		 * @fn	virtual bool ModeOverlay::Initialize(Game& g);
		 *
		 * @brief	初期化処理
		 * @detail	ModeServer接続時に一度だけ呼ばれる
		 *
		 * @param [in,out]	_game	Gameクラスの参照
		 *
		 * @returns	初期化成功の可否
		 */
		virtual bool Initialize(Game& g);

		/**
		 * @fn	virtual bool ModeOverlay::Terminate(Game& g);
		 *
		 * @brief	終了処理
		 * @detail	ModeServerから削除される際、一度だけ呼ばれる
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 *
		 * @returns	終了処理成功の可否
		 */
		virtual bool Terminate(Game& g);

		/**
		 * @fn	virtual bool ModeOverlay::Process(Game& g);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 *
		 * @returns	演算処理成功の可否
		 */
		virtual bool Process(Game& g);

		/**
		 * @fn	virtual bool ModeOverlay::Draw(Game& g);
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 *
		 * @returns	描画処理成功の可否
		 */
		virtual bool Draw(Game& g);

		/**
		 * @fn	void ModeOverlay::Capture(int fadecnt);
		 *
		 * @brief	現在表示されているモードをキャプチャして、画面遷移を行う
		 *
		 * @param 	fadecnt	フェード時間
		 */
		void Capture(int fadecnt);

		/**
		 * @fn	void ModeOverlay::Fade(int fadecount, int fadetype);
		 *
		 * @brief	フェードイン : 暗転から明るくなる
		 * 				フェードアウト : 明るい画面から徐々に暗転
		 *
		 * @param 	fadecount	フェード時間
		 * @param 	fadetype 	フェードイン : 0
		 * 									フェードアウト : 1
		 */
		void Fade(int fadecount, int fadetype);

	private:
		int m_graph;
		int m_count;	//!< フェード時間
		int m_all;  //!< フェード時間記録用変数
		int m_fade_type;	//!< フェードの種類
	};
}