/**
 * @file	AMG_Summer_Co_Production_2020\script\BonusPoint.h.
 *
 * @brief	スコアボーナスモードでボーナスポイントを描画する
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
  * @class	BonusPoint
  *
  * @brief	ボーナスポイントを描画するクラス
  *
  */
	class BonusPoint : public ObjectBase
	{
	public:
		/**
		 * @fn	BonusPoint::BonusPoint();
		 *
		 * @brief	Default constructor
		 * 				パラメータはSetParamで設定
		 *
		 */
		BonusPoint();
		~BonusPoint();

		/**
		 * @fn	virtual OBJECT_TYPE BonusPoint::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::PARTICLE; }

		/**
		 * @fn	void BonusPoint::SetParam(const char* _filename, double x, double y, double vx, double vy, int cnt);
		 *
		 * @brief	パラメータを設定
		 * 				動的に生成しないので、コンストラクタではなくこの関数でパラメータを設定する
		 *
		 * @param 	_filename	画像名
		 * @param 	x		 	x座標
		 * @param 	y		 	y座標
		 * @param 	vx		 	x方向の移動量
		 * @param 	vy		 	y方向の移動量
		 * @param 	cnt		 エフェクト生存時間
		 */
		void SetParam(const char* _filename, double x, double y, double vx, double vy, int cnt);

		/**
		 * @fn	void BonusPoint::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void BonusPoint::Draw(Game& _game);
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game);

	public:
		int m_graph;	//!< 画像ハンドル
		double	_x, _y;		//!< 座標
		double	_vx, _vy;	//!< 移動方向
		int		_cnt;   //!< 動作カウンタ
	};
}