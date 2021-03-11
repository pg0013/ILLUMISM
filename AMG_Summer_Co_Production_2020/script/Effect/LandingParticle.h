/**
 * @file    LandingParticle.h
 * @brief  着地エフェクト用パーティクル
 * 
 * @author Takuya Fujisawa
 * @date   2020/10/26
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
	* @brief 着地エフェクト用パーティクルクラス
	*/
	class LandingParticle : public ObjectBase
	{
	public:
		/**
		 * @brief コンストラクタ.
		 *
		 * @param _x				x座標
		 * @param _y				y座標
		 * @param _cnt				出現時間
		 */
		LandingParticle(int _x, int _y, int _cnt);
		~LandingParticle();

		/**
		 * @fn	virtual OBJECT_TYPE GroundParticle::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::PARTICLE; }

		/**
		 * @brief　演算処理.
		 *
		 * @param _game　ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @brief　描画処理.
		 *
		 * @param _game　ゲームクラスの参照
		 */
		void Draw(Game& _game);

	private:
		int m_landing_graph[10] = { 0 };
		int m_all_count;
	};
}