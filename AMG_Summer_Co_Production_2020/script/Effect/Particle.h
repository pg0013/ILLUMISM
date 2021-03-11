/**
 * @file	AMG_Summer_Co_Production_2020\script\Particle.h.
 *
 * @brief	エフェクト用パーティクル
 * @author	Takuya Fujisawa
 */

#pragma once
#include"../Object/ObjectBase.h"

namespace illumism
{
	/**
	 * @class	Particle
	 *
	 * @brief	パーティクルクラス
	 *
	 */
	class Particle :public ObjectBase
	{
	public:

		/**
		 * @fn	Particle::Particle(const char* _filename, double x, double y, double vx, double vy, int cnt);
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
		Particle(const char* _filename, double x, double y, double vx, double vy, int cnt);
		~Particle();

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

		/**
		 * @fn	void Particle::SetBright(int _r, int _g, int _b)
		 *
		 * @brief	パーティクルの描画色を指定
		 *
		 * @param 	_r	 RED
		 * @param 	_g	 GREEN
		 * @param 	_b	 BLUE
		 */
		void SetBright(int _r, int _g, int _b) { _red = _r, _green = _g, _blue = _b; }

	public:
		int m_graph[2]; //!< 画像ハンドル
		double	_x, _y;		//!<座標
		double	_vx, _vy;	//!< 移動方向
		int		_cnt;   //!< 動作カウンタ
		int _sizeratio; //!< 画像の最大の大きさを記録
		int _red, _green, _blue;//!<RGB用変数
	};
}