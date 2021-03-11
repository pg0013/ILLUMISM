/**
 * @file	AMG_Summer_Co_Production_2020\script\SPMove.h.
 *
 * @brief	必殺技オブジェクト
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"
#include"../Sound/PlayWAVE.h"

namespace illumism
{
	/**
	 * @class	SPMove
	 *
	 * @brief	必殺技のオブジェクトクラス
	 *
	 */
	class SPMove : public ObjectBase
	{
	public:
		SPMove(int _num);
		~SPMove();

		/**
		 * @fn	virtual ObjectBase::OBJECT_TYPE SPMove::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual ObjectBase::OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::SPMOVE; }

		/**
		 * @fn	void SPMove::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void SPMove::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void SPMove::Damage(Game& _game);
		 *
		 * @brief	オブジェクトを削除
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Damage(Game& _game);

		/**
		 * @fn	void SPMove::Draw(Game& _game) override;
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void SPMove::SPMoveActivate(Game& _game, const int _startframe, const int _activetime);
		 *
		 * @brief	必殺技用指定時間内当たり判定を有効にする
		 *
		 * @param [in,out]	_game	   	ゲームクラスの参照
		 * @param 		  	_startframe	当たり判定を有効開始時間
		 * @param 		  	_activetime	当たり判定有効を継続する時間
		 */
		void SPMoveActivate(Game& _game, const int _startframe, const int _activetime);

		/**
		 * @fn	void SPMove::SetDirection(Game& _game, int _num, bool _turn_flag) override;
		 *
		 * @brief	Sets a direction
		 *
		 * @param [in,out]	_game	  	ゲームクラスの参照
		 * @param 		  	_num	  	プレイヤー番号
		 * @param 		  	_turn_flag	左方向だとtrue
		 */
		void SetDirection(Game& _game, int _num, bool _turn_flag) override;
	};
}