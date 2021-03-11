/**
 * @file	AMG_Summer_Co_Production_2020\script\Utility.h.
 *
 * @brief	Utility
 */

#pragma once
#include"../Server/ResourceServer.h"

namespace utility
{

	/*
	**ソース: https://dxlib.xsrv.jp/cgi/patiobbs/patio.cgi?mode=past&no=1825
	*/

	/**
	 * @fn	int* GetColorHSV(float H, float S, float V);
	 *
	 * @brief	HSVをRGBに変換する
	 *
	 * @param 	H : 色相　有効範囲 0.0f ～ 360.0f
	 * @param 	S : 彩度　有効範囲 0.0f ～ 1.0f
	 * @param 	V : 明度　有効範囲 0.0f ～ 1.0f.
	 *
	 * @returns	RGBを格納したポインタ
	 */
	int* GetColorHSV(float H, float S, float V);

	/**
	 * @fn	void LoadGraphHandle();
	 *
	 * @brief	ゲームシーンの画像を非同期読み込み
	 *
	 */
	void LoadGraphHandle();
}