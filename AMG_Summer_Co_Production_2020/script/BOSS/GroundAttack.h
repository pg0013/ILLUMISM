/**
 * @file	AMG_Summer_Co_Production_2020\script\GroundAttack.h.
 *
 * @brief	地面から突き出す攻撃処理
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
 * @class	GroundAttack
 *
 * @brief	地面から突き出す攻撃を行うクラス
 *
 */
	class GroundAttack : public ObjectBase
	{
	public:
		GroundAttack(int _x, int _y, int _angle, int _type);
		~GroundAttack();

		/**
		 * @fn	virtual OBJECT_TYPE GroundAttack::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::GROUNDATTACK; }

		/**
		 * @fn	void GroundAttack::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void GroundAttack::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void GroundAttack::Draw(Game& _game) override;
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void GroundAttack::Hit(Game& _game);
		 *
		 * @brief	当たり判定処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Hit(Game& _game);

		/**
		 * @fn	void GroundAttack::SwitchDirection();
		 *
		 * @brief	棘が最大まで突き出したら、引っ込ませる処理
		 *
		 */
		void SwitchDirection();

		/**
		 * @fn	bool GroundAttack::IsHitToCircle(ObjectBase& _object);
		 *
		 * @brief	円と四角の当たり判定処理
		 *
		 * @param [in,out]	_object	オブジェクトベースクラスの参照
		 *
		 * @returns	プレイヤーと当たり判定可否
		 */
		bool IsHitToCircle(ObjectBase& _object);

		/**
		 * @fn	inline void GroundAttack::SetSpeed(int _speed)
		 *
		 * @brief	Sets a speed
		 *
		 * @param 	_speed	The speed.
		 */
		inline void SetSpeed(int _speed) { m_speed = _speed; }

		/**
		 * @fn	inline void GroundAttack::SetAngle(int _angle)
		 *
		 * @brief	突き出す角度を設定
		 *
		 * @param 	_angle	The angle.
		 */
		inline void SetAngle(int _angle) { m_angle = _angle; }

	private:
		int m_speed_x;
		int m_speed_y;
		int m_angle;

		float vector_x; //!< 角度から算出する移動ベクトル
		float vector_y;

		int m_stop_count;   //!< 最大まで突き出したときの止まる時間

		int hit_cx[18]; //!< 当たり判定の中心座標
		int hit_cy[18];
		int hit_r[18];  //!< 当たり判定の半径
		int hit_circle_num;
	};
}