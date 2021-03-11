/**
 * @file	AMG_Summer_Co_Production_2020\script\Bullet.h.
 *
 * @brief	プレイヤーが発射する弾丸
 * @author	Takuya Fujisawa
 */

#pragma once
#include"ObjectBase.h"
#include"../Sound/PlayWAVE.h"

namespace illumism
{
	namespace
	{
		constexpr int BULLET_SPEED = 28;		//弾丸スピード
	}

	/**
	 * @class	Bullet
	 *
	 * @brief	プレイヤーが発射する弾丸オブジェクトのクラス
	 *
	 */
	class Bullet : public ObjectBase
	{
	public:

		/**
		 * @fn	Bullet::Bullet(int _num);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_num	プレイヤー番号
		 */
		Bullet(int _num);
		~Bullet();

		/**
		 * @fn	virtual ObjectBase::OBJECT_TYPE Bullet::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual ObjectBase::OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::BULLET; }

		/**
		 * @fn	void Bullet::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void Bullet::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void Bullet::Damage(Game& _game);
		 *
		 * @brief	オブジェクトを消去
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Damage(Game& _game);

		/**
		 * @fn	void Bullet::Draw(Game& _game) override;
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void Bullet::Hit(Game& _game);
		 *
		 * @brief	弾同士の当たり判定
		 *
		 * @param [in,out]	_game	The game.
		 */
		void Hit(Game& _game);

		/**
		 * @fn	void Bullet::SetDirection(Game& _game, int _num, bool _turn_flag) override;
		 *
		 * @brief	弾を発射する方向と当たり判定の位置を設定
		 *
		 * @param [in,out]	_game	  		ゲームクラスの参照
		 * @param 		  		_num	  		プレイヤー番号
		 * @param 		  		_turn_flag		左方向だとtrue
		 */
		void SetDirection(Game& _game, int _num, bool _turn_flag) override;

	private:
		bool m_turn_flag = false;   //!< 画像を反転するかどうか（左向きでtrue）
	};
}