/**
 * @file	AMG_Summer_Co_Production_2020\script\TouchObjectController.h.
 *
 * @brief	タッチオブジェクトの出現を管理するクラス
 *
 * @detail	一定のBPMでタッチオブジェクトを画面上に生成する
 * @author	Takuya Fujisawa
 */

#pragma once
#include"DxLib.h"

namespace illumism
{
	class Game;//< 二重インクルード防止

	namespace
	{
		constexpr int MINUTES = 3600;
	}

	/**
	 * @class	TouchObjectController
	 *
	 * @brief	タッチオブジェクトの出現を管理するクラス
	 */
	class TouchObjectController
	{
	public:
		TouchObjectController();
		~TouchObjectController();

		void Process(Game& _game);

	private:
		int m_bpm_counter_6;	//!< BPMの経過回数をカウント
		int m_bpm_counter_45;   //!< BPMの経過回数をカウント

		int m_time; //!< BGM再生時からの経過時間
	};
}