/**
 * @file	AMG_Summer_Co_Production_2020\script\GroundParticle.h.
 *
 * @brief	ボスの棘が地面から突き出す攻撃のcation表示エフェクト
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
	  * @class	GroundParticle
	  *
	  * @brief	ボスの棘が地面から突き出す攻撃のcation表示エフェクトクラス
	  *
	  */
	class GroundParticle : public ObjectBase
	{
	public:

		/**
		 * @fn	GroundParticle::GroundParticle(const char* _filename, double x, double y, double vx, double vy, int cnt);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_filename	画像名
		 * @param 	x		 	x座標
		 * @param 	y		 	y座標
		 * @param 	vx		 	x方向の移動量
		 * @param 	vy		 	y方向の移動量
		 * @param 	cnt		 エフェクト生存時間
		 */
		GroundParticle(const char* _filename, double x, double y, double vx, double vy, int cnt);
		~GroundParticle();

		/**
		 * @fn	virtual OBJECT_TYPE GroundParticle::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::PARTICLE; }

		/**
		 * @fn	virtual void GroundParticle::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		virtual void	Process(Game& _game);

		/**
		 * @fn	virtual void GroundParticle::Draw(Game& _game) override;
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		virtual void	Draw(Game& _game) override;

	public:
		int m_graph;			//!< 画像ハンドル
		double	_x, _y;		//!< 座標
		double	_vx, _vy;	//!< 移動方向
		int		_cnt;				//!< 動作カウンタ
	};
}