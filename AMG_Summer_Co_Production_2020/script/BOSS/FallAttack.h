/**
 * @file	AMG_Summer_Co_Production_2020\script\FallAttack.h.
 *
 * @brief	画面上から落ちてくる攻撃処理
  * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
  * @class	FallAttack
  *
  * @brief	落ちもの攻撃クラス
  *
  */
	class FallAttack : public ObjectBase
	{
	public:
		FallAttack(int _num);
		~FallAttack();

		/**
		 * @fn	virtual OBJECT_TYPE FallAttack::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::FALLATTACK; }

		/**
		 * @fn	void FallAttack::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void FallAttack::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void FallAttack::Draw(Game& _game) override;
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void FallAttack::Damage(Game& _game);
		 *
		 * @brief	プレイヤーに当たるか、地面まで到達するとオブジェトを削除
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Damage(Game& _game);

		/**
		 * @fn	inline void FallAttack::SetSpeed(int _speed)
		 *
		 * @brief	移動速度を設定
		 *
		 * @param 	_speed	The speed.
		 */
		inline void SetSpeed(int _speed) { m_speed = _speed; }

	private:
		const int BODY_W = 220; //!< 画像サイズ
		const int BODY_H = 220;
		int m_speed;	//!< 移動速度
	};
}