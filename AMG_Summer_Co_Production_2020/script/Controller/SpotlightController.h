/**
 * @file	AMG_Summer_Co_Production_2020\script\SpotlightController.h.
 *
 * @brief	スポットライトの出現を管理するクラス
 * @author	Takuya Fujisawa
 */

#pragma once
#include"DxLib.h"

namespace illumism
{
	class Game; //<	二重インクルード防止

	/**
	 * @class	SpotlightController
	 *
	 * @brief	スポットライト出現を管理するクラス
	 */
	class SpotlightController
	{
	public:
		SpotlightController();
		~SpotlightController();

		void Process(Game& _game);

	private:
		int m_start_time;	//!< BGM再生時のスタートタイム
		int m_now_time;	//!< 現在のタイム
		int m_time;			//!< BGM再生時からの経過時間[ms]
		int m_interval;		//!< スポットライトの間隔
		int m_count;			//!< フレームカウント
		bool once_flag;
	};
}