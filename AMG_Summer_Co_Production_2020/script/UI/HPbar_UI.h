/**
 * @file	AMG_Summer_Co_Production_2020\script\HPbar_UI.h.
 *
 * @brief	プレイヤーのHPを表示するUI
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	class Game;	//二重インクルード防止

	/**
	 * @class	HPbar_UI
	 *
	 * @brief	プレイヤーのHPを表示するクラス
	 *
	 */
	class HPbar_UI : public ObjectBase
	{
	public:
		HPbar_UI();
		~HPbar_UI();

		/**
		 * @fn	virtual ObjectBase::OBJECT_TYPE HPbar_UI::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual ObjectBase::OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::UI; }

		/**
		 * @fn	void HPbar_UI::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void HPbar_UI::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void HPbar_UI::Draw(Game& _game) override;
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void HPbar_UI::SetHP(const int _player_num, const int _hp);
		 *
		 * @brief	表示するHPを設定
		 *
		 * @param 	_player_num	プレイヤー番号
		 * @param 	_hp				表示するHP
		 */
		void SetHP(const int _player_num, const int _hp);

	private:
		int m_graph_up; //!< 画像ハンドル
		int m_hp[2];	//!< プレイヤーのHP
	};
}