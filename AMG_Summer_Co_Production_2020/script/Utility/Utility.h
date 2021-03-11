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
	**�\�[�X: https://dxlib.xsrv.jp/cgi/patiobbs/patio.cgi?mode=past&no=1825
	*/

	/**
	 * @fn	int* GetColorHSV(float H, float S, float V);
	 *
	 * @brief	HSV��RGB�ɕϊ�����
	 *
	 * @param 	H : �F���@�L���͈� 0.0f �` 360.0f
	 * @param 	S : �ʓx�@�L���͈� 0.0f �` 1.0f
	 * @param 	V : ���x�@�L���͈� 0.0f �` 1.0f.
	 *
	 * @returns	RGB���i�[�����|�C���^
	 */
	int* GetColorHSV(float H, float S, float V);

	/**
	 * @fn	void LoadGraphHandle();
	 *
	 * @brief	�Q�[���V�[���̉摜��񓯊��ǂݍ���
	 *
	 */
	void LoadGraphHandle();
}