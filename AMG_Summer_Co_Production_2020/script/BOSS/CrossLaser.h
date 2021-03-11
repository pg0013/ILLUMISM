/**
 * @file	AMG_Summer_Co_Production_2020\script\CrossLaser.h.
 *
 * @brief	画面端からのレーザー攻撃を行う
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
 * @class	CrossLaser
 *
 * @brief	画面端からのレーザー攻撃行うクラス
 *
 */
	class CrossLaser : public ObjectBase
	{
	public:
		CrossLaser(int _num);
		~CrossLaser();

		/**
		 * @fn	virtual OBJECT_TYPE CrossLaser::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::CROSSBEAM; }

		/**
		 * @fn	void CrossLaser::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void CrossLaser::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void CrossLaser::Draw(Game& _game) override;
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void CrossLaser::Damage(Game& _game)override;
		 *
		 * @brief	生成場所から反対側の画面端まで到達すると、オブジェクトを削除
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Damage(Game& _game)override;

		/**
		 * @fn	inline void CrossLaser::SetSpeed(int _speed)
		 *
		 * @brief	移動速度を設定
		 *
		 * @param 	_speed	The speed.
		 */
		inline void SetSpeed(int _speed) { m_speed = _speed; }

	private:
		int	 direction;	//!< 上下左右方向を決定する変数
		int m_speed;	//!< 移動速度
	};
}