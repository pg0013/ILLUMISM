/**
 * @file	AMG_Summer_Co_Production_2020\script\LaserAttack.h.
 *
 * @brief	プレイヤーに向かうレーザー攻撃処理
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"
#include"DxLib.h"

namespace illumism
{
	/**
	  * @class	LaserAttack
	  *
	  * @brief	プレイヤーに向かうレーザー攻撃を行うクラス
	  *
	  */
	class LaserAttack : public ObjectBase
	{
	public:

		/**
		 * @fn	LaserAttack::LaserAttack(int _x,int _y,int _taget_x,int _target_y,int _speed);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_x		 	ボスの目のx座標
		 * @param 	_y		 	ボスの目のy座標
		 * @param 	_taget_x	プレイヤーのx座標
		 * @param 	_target_y	プレイヤーのy座標
		 * @param 	_speed   	レーザーの移行速度
		 */
		LaserAttack(int _x, int _y, int _taget_x, int _target_y, int _speed);
		~LaserAttack();

		/**
		 * @fn	virtual OBJECT_TYPE LaserAttack::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::LASER; }

		/**
		 * @fn	void LaserAttack::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void LaserAttack::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void LaserAttack::Damage(Game& _game);
		 *
		 * @brief	プレイヤーに当たるとオブジェクトを削除
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Damage(Game& _game);

		/**
		 * @fn	void LaserAttack::Draw(Game& _game) override;
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void LaserAttack::Hit(Game& _game);
		 *
		 * @brief	当たり判定処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Hit(Game& _game);

		/**
		 * @fn	bool LaserAttack::IsHitToCircle(ObjectBase& _object);
		 *
		 * @brief	円と四角の当たり判定処理
		 *
		 * @param [in,out]	_object	オブジェクトベースクラスの参照
		 *
		 * @returns	プレイヤーとの当たり判定の可否
		 */
		bool IsHitToCircle(ObjectBase& _object);

		/**
		 * @fn	void LaserAttack::OffScreen(Game& _game);
		 *
		 * @brief	画面外に到達したら削除
		 *
		 * @param [in,out]	_game	The game.
		 */
		void OffScreen(Game& _game);

	private:
		VECTOR target;  //!< 目標プレイヤーの座標
		VECTOR position;	//!< ボスの目の座標

		float m_speed_x, m_speed_y;
		double e_x, e_y;//!<プレイヤーに向かうベクトルの正規化保存変数
		double m_angle;

		int hit_r[3];   //!< 円の当たり判定用パラメータ
		int hit_cx[3];
		int hit_cy[3];
	};
}