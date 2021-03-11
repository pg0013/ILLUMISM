/**
 * @file	AMG_Summer_Co_Production_2020\script\BOSS_LEFT.h.
 *
 * @brief	ボスの左パーツを管理
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
  * @class	BOSS_LEFT
  *
  * @brief	ボスの左パーツを描画するクラス
  *
  */
	class BOSS_LEFT : public ObjectBase
	{
	public:
		BOSS_LEFT();
		~BOSS_LEFT();

		/**
		 * @fn	virtual OBJECT_TYPE BOSS_LEFT::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::BOSS; }

		/**
		 * @fn	void BOSS_LEFT::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void BOSS_LEFT::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void BOSS_LEFT::Draw(Game& _game) override;
		 *
		 * @brief	ボスの左パーツを描画
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void BOSS_LEFT::Damage(Game& _game) override;
		 *
		 * @brief	ボスのダメージ画像を描画
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Damage(Game& _game) override;
	private:
		int m_leftsand_graph[2];	//!< 画像ハンドル
		int m_leftclock_graph[2];
		int m_leftgear1_graph[2];
		int m_leftgear2_graph[2];
		int m_leftgear3_graph[2];
	};
}