/**
 * @file	AMG_Summer_Co_Production_2020\script\SpotLightHit.h.
 *
 * @brief	スポットライト停止時の当たり判定
 * @author	Takuya Fujisawa
 */

#pragma once
#include"ObjectBase.h"

namespace illumism
{
	/**
 * @class	SpotLightHit
 *
 * @brief	スポットライト用当たり判定クラス
 *
 */
	class SpotLightHit : public ObjectBase
	{
	public:
		SpotLightHit();
		~SpotLightHit();

		/**
		 * @fn	virtual ObjectBase::OBJECT_TYPE SpotLightHit::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual ObjectBase::OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::SPOTLIGHT; }

		/**
		 * @fn	void SpotLightHit::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void SpotLightHit::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void SpotLightHit::Damage(Game& _game);
		 *
		 * @brief	オブジェクトを削除
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Damage(Game& _game);

		/**
		 * @fn	void SpotLightHit::Draw(Game& _game) override;
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void SpotLightHit::SpotlightHitActivate(Game& _game, const int _startframe, const int _activetime);
		 *
		 * @brief	スポットライト用指定時間内当たり判定を有効にする.
		 *
		 * @param [in,out]	_game	   	ゲームクラスの参照
		 * @param 		  	_startframe	当たり判定を有効開始時間
		 * @param 		  	_activetime	当たり判定有効を継続する時間
		 */
		void SpotlightHitActivate(Game& _game, const int _startframe, const int _activetime);
	};
}