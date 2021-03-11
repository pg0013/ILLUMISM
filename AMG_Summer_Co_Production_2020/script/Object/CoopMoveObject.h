/**
 * @file	AMG_Summer_Co_Production_2020\script\CoopMoveObject.h.
 *
 * @brief	アピールを同時に行うと現れる協力技クラス
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ObjectBase.h"

namespace illumism
{
	/**
	 * @class	CoopMoveObject
	 *
	 * @brief	協力技のオブジェクトクラス
	 *
	 */
	class CoopMoveObject : public ObjectBase
	{
	public:
		CoopMoveObject();
		~CoopMoveObject();

		/**
		 * @fn	virtual OBJECT_TYPE CoopMoveObject::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual OBJECT_TYPE GetType() { return OBJECT_TYPE::COOP; }

		/**
		 * @fn	void CoopMoveObject::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void CoopMoveObject::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void CoopMoveObject::Draw(Game& _game) override;
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void CoopMoveObject::Damage(Game& _game) override;
		 *
		 * @brief	オブジェクトを削除
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Damage(Game& _game) override;
	};
}