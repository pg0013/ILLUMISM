/**
 * @file	AMG_Summer_Co_Production_2020\script\SPmove_UI.h.
 *
 * @brief	必殺技ゲージを表示
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	class Game;//二重インクルード防止

	/**
	 * @class	SPmove_UI
	 *
	 * @brief	必殺技ゲージのUIを表示するクラス
	 *
	 */
	class SPmove_UI : public ObjectBase
	{
	public:
		SPmove_UI();
		~SPmove_UI();

		/**
		 * @fn	virtual ObjectBase::OBJECT_TYPE SPmove_UI::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual ObjectBase::OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::UI; }

		/**
		 * @fn	void SPmove_UI::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void SPmove_UI::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void SPmove_UI::Draw(Game& _game) override;
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void SPmove_UI::DrawAura();
		 *
		 * @brief	必殺技が撃てることを知らせるオーラを表示する
		 *
		 */
		void DrawAura();

		/**
		 * @fn	void SPmove_UI::SetMP(const int _player_num, const int _mp);
		 *
		 * @brief	MPを設定
		 *
		 * @param 	_player_num	プレイヤー番号
		 * @param 	_mp		   		MP
		 */
		void SetMP(const int _player_num, const int _mp);

	private:
		int m_mp[2];
		int m_graph_aura;
	};
}