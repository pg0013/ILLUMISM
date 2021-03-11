/**
 * @file	AMG_Summer_Co_Production_2020\script\BOSS_RIGHT.h.
 *
 * @brief	ボスの右パーツを管理
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
  * @class	BOSS_RIGHT
  *
  * @brief	ボスの右パーツを描画するクラス
  *
  */
	class BOSS_RIGHT : public ObjectBase
	{
	public:
		BOSS_RIGHT();
		~BOSS_RIGHT();

		/**
		 * @fn	virtual OBJECT_TYPE BOSS_RIGHT::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::BOSS; }

		/**
		 * @fn	void BOSS_RIGHT::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void BOSS_RIGHT::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void BOSS_RIGHT::Draw(Game& _game) override;
		 *
		 * @brief	ボスの右パーツを描画
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void BOSS_RIGHT::Damage(Game& _game) override;
		 *
		 * @brief	ダメージ画像を描画
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Damage(Game& _game) override;

	private:
		int m_right_a_graph[2]; //!< 画像ハンドル
		int m_right_b_graph[2];
		int m_right_c_graph[2];
		int m_rightgear1_graph[2];
		int m_rightgear2_graph[2];
		int m_rightgear3_graph[2];
	};
}