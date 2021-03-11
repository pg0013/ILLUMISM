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
	class TouchSuccessEffect :
		public ObjectBase
	{
	public:
		/**
		 * @brief コンストラクタ.
		 *
		 * @param _x				x座標
		 * @param _y				y座標
		 * @param _cnt				出現時間
		 */
		TouchSuccessEffect(int _num, int _cnt);
		~TouchSuccessEffect();

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
		int m_touchsuccess_graph[10] = { 0 };
		int m_all_count;
		int m_player_num;
	};
}