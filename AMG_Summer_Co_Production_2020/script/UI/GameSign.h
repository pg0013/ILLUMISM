/**
 * @file	AMG_Summer_Co_Production_2020\script\GameSign.h.
 *
 * @brief	ゲームカウントやREADY?などを表示するパーティクル
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
	 * @class	GameSign
	 *
	 * @brief	インゲーム内の標識を描画するクラス
	 */
	class GameSign :
		public ObjectBase
	{
	public:
		/**
		 * @fn	GameSign::GameSign(const char* _filename, int _x, int _y, int _cnt);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_filename	画像名
		 * @param 	_x		 	x座標
		 * @param 	_y		 	y座標
		 * @param 	_cnt	 	画像を描画する時間
		 */
		GameSign(const char* _filename, int _x, int _y, int _cnt);
		~GameSign();

		/**
	 * @fn	virtual OBJECT_TYPE Particle::GetType()
	 *
	 * @brief	オブジェクトの種類を返す
	 *
	 * @returns	オブジェクトの種類
	 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::PARTICLE; }

		/**
		 * @fn	virtual void Particle::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		virtual void Process(Game& _game);

		/**
		 * @fn	virtual void Particle::Draw(Game& _game) override;
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		virtual void Draw(Game& _game) override;

	private:
		int m_count;	//!< 画像表示カウンタ
	};
}