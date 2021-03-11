/**
 * @file    HitEffect.h
 * @brief  ヒットエフェクトクラス
 *
 * @author Takuya Fujisawa
 * @date   2020/11/05
 */

#pragma once
#include"../Object/ObjectBase.h"

//キャラクターのエフェクト位置調節用定数
namespace
{
	constexpr int  NARI_OFFSET_LEFT = -80;
	constexpr int  NARI_OFFSET_RIGHT = -25;
	constexpr int  NONAME_OFFSET_LEFT = -45;
	constexpr int  NONAME_OFFSET_RIGHT = -55;
}

namespace illumism
{
	/**
	 * @brief ヒットエフェクト
	 */
	class HitEffect : public ObjectBase
	{
	public:
		/**
		 * @brief　 コンストラクタ
		 *
		 * @param  _x	x座標
		 * @param  _y	y座標
		 * @param  _cnt	持続フレーム数
		 */
		HitEffect(int _x, int _y, int _cnt);
		~HitEffect();

		/**
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

		/**
		 * @brief　 キャラクターごとの位置調整
		 *
		 * @param  _charactor_type　キャラクターの種類
		 * @param  _direction	方向
		 */
		void SetPositionOffset(int _charactor_type, int _direction);

	private:
		int m_hiteffect_graph[8] = { 0 };//!<画像ハンドル
		int m_all_count;//!<出現時間
	};
}