/**
 * @file	AMG_Summer_Co_Production_2020\script\Combo.h.
 *
 * @brief	タッチオブジェクトのコンボを表示
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
	 * @class	Combo
	 *
	 * @brief	コンボを表示するクラス
	 *
	 */
	class Combo : public ObjectBase
	{
	public:

		/**
		 * @fn	Combo::Combo(const int _player_num, const int _combo);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_player_num	プレイヤー番号
		 * @param 	_combo	   	コンボ数
		 */
		Combo(const int _player_num, const int _combo);
		~Combo();

		/**
		 * @fn	virtual OBJECT_TYPE Combo::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual OBJECT_TYPE GetType() { return OBJECT_TYPE::UI; }

		/**
		 * @fn	void Combo::Init();
		 *
		 * @brief 初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void Combo::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void Combo::Draw(Game& _game) override;
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void Combo::SetCombo();
		 *
		 * @brief	コンボ数を設定
		 *
		 */
		void SetCombo();

	private:
		int m_number_graph[10];	//!<画像ハンドル
		int m_combo_graph;
		int m_combo;	//!< プレイヤーコンボ数
		int onerank, tenrank;//!<一の位、十の位
		int m_count;	//!<コンボ表示時間カウンタ
	};
}