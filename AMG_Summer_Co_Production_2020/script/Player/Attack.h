/**
 * @file	AMG_Summer_Co_Production_2020\script\Attack.h.
 *
 * @brief	プレイヤーのATTACK攻撃用当たり判定処理
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
	 * @class	Attack
	 *
	 * @brief	ATTACK用当たり判定のクラス
	 *
	 */
	class Attack : public ObjectBase
	{
	public:

		/**
		 * @fn	Attack::Attack(int _player_num);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_player_num	プレイヤー番号
		 */
		Attack(int _player_num);
		~Attack();

		/**
		 * @fn	virtual ObjectBase::OBJECT_TYPE Attack::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual ObjectBase::OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::ATTACK; }

		/**
		 * @fn	void Attack::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void Attack::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void Attack::Damage(Game& _game);
		 *
		 * @brief	当たり判定を削除
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Damage(Game& _game);

		/**
		 * @fn	void Attack::Draw(Game& _game) override;
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void Attack::AttackActivate(Game& _game,const int _startframe,const int _activetime);
		 *
		 * @brief	ATTACK用当たり判定を指定時間内有効にする
		 *
		 * @param [in,out]	_game	   	ゲームクラスの参照
		 * @param 		  	_startframe	当たり判定を有効開始時間
		 * @param 		  	_activetime	当たり判定有効を継続する時間
		 */
		void AttackActivate(Game& _game, const int _startframe, const int _activetime);

		/**
		 * @fn	void Attack::SetDirection(Game& _game, int _num, bool _turn_flag) override;
		 *
		 * @brief	当たり判定を出す方向を設定
		 *
		 * @param [in,out]	_game	  	ゲームクラスの参照
		 * @param 		  	_num	  	プレイヤー番号
		 * @param 		  	_turn_flag	左方向だとtrue
		 */
		void SetDirection(Game& _game, int _num, bool _turn_flag) override;
	};
}