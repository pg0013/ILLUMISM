/**
 * @file	AMG_Summer_Co_Production_2020\script\PointObject.h.
 *
 * @brief	プレイヤーがHP<0になった時に放出するポイントオブジェクトのクラス
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ObjectBase.h"

namespace illumism
{
	class Game;	//!<二重インクルード防止

	namespace
	{
		//状態遷移用変数
		constexpr int DIFFUSION = 0;
		constexpr int VIBRATION = 1;
	}

	/**
	 * @class	PointObject
	 *
	 * @brief	プレイヤーがHP<0になった時に放出するポイントオブジェクトのクラス
	 *
	 */
	class PointObject : public ObjectBase
	{
	public:
		PointObject();
		~PointObject();

		/**
		 * @fn	virtual OBJECT_TYPE PointObject::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual OBJECT_TYPE GetType() { return OBJECT_TYPE::POINT; }

		/**
		 * @fn	void PointObject::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void PointObject::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void PointObject::Diffusion(Game& _game);
		 *
		 * @brief	ポイントオブジェクトの拡散処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Diffusion(Game& _game);

		/**
		 * @fn	void PointObject::SimpleVibration(Game& _game);
		 *
		 * @brief	ポイントオブジェクトの単振動処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void SimpleVibration(Game& _game);

		/**
		 * @fn	void PointObject::ApproachToPlayer(Game& _game);
		 *
		 * @brief	プレイヤーが近づいたらプレイヤーに吸い寄せられる処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void ApproachToPlayer(Game& _game);

		/**
		 * @fn	void PointObject::Draw(Game& _game) override;
		 *
		 * @brief	演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void PointObject::Damage(Game& _game);
		 *
		 * @brief	オブジェクトを消去
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Damage(Game& _game);

		/**
		 * @fn	void PointObject::OffScreen();
		 *
		 * @brief	プレイヤー移動制限内を出ない処理
		 *
		 */
		void OffScreen();

	private:
		int m_diffusion_height;	//!<散らばる高さ
		int m_falling_speed_x;  //!< 落下速度
		int m_falling_speed_y;  //!< 落下速度
		int m_vibration_height; //!< 単振動の時の高さ
		int m_object_state;		//!< オブジェクト状態
	};
}