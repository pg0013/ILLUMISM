/**
 * @file	AMG_Summer_Co_Production_2020\script\Spotlight.h.
 *
 * @brief	スポットライトオブジェクト
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ObjectBase.h"

namespace illumism
{
	/**
  * @class	Spotlight
  *
  * @brief	ゲームギミックであるスポットライトのクラス
  *
  */
	class Spotlight : public ObjectBase
	{
	public:
		/**
		 * @fn	Spotlight::Spotlight(int _num,int _move_time);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_num	  	スポットライトの色用変数
		 * @param 	_move_time	移動時間
		 */
		Spotlight(int _num, int _move_time);
		~Spotlight();

		/**
		 * @fn	virtual OBJECT_TYPE Spotlight::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual OBJECT_TYPE GetType() { return OBJECT_TYPE::NOHIT; }

		/**
		 * @fn	void Spotlight::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void Spotlight::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void Spotlight::Damage(Game& _game);
		 *
		 * @brief	オブジェクトの削除
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Damage(Game& _game);

		/**
		 * @fn	void Spotlight::Draw(Game& _game) override;
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void Spotlight::SetSpeed(const int _speed)
		 *
		 * @brief	移動速度を設定
		 *
		 * @param 	_speed	移動速度
		 */
		void SetSpeed(const int _speed) { m_speed = _speed; }

		/**
		 * @fn	void Spotlight::SetTime(const int _time)
		 *
		 * @brief	停止するまでの時間を設定
		 *
		 * @param 	_time	移動時間
		 */
		void SetTime(const int _time) { m_move_time = _time; }

		/**
		 * @fn	int Spotlight::Move();
		 *
		 * @brief	移動距離を返す
		 *
		 * @returns	移動距離
		 */
		int Move();

	private:
		const int BODY_W = 1213;	//!< 移動距離
		const int BODY_H = 1224;

		int m_move_x;   //!<	x方向の移動距離
		int m_move_time;	//!< 移動時間

		ObjectBase* spotlight_hit;  //!< スポットライトの当たり判定
	};
}