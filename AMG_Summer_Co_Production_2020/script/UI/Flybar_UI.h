/**
 * @file	AMG_Summer_Co_Production_2020\script\Flybar_UI.h.
 *
 * @brief	飛行可能時間を表示するUI
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	class Game;//!<二重インクルード防止

	/**
	 * @class	Flybar_UI
	 *
	 * @brief	飛行時間表示クラス
	 *
	 */
	class Flybar_UI : public ObjectBase
	{
	public:
		Flybar_UI();
		~Flybar_UI();

		/**
		 * @fn	virtual ObjectBase::OBJECT_TYPE Flybar_UI::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual ObjectBase::OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::UI; }

		/**
		 * @fn	void Flybar_UI::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void Flybar_UI::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void Flybar_UI::Draw(Game& _game) override;
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void Flybar_UI::SetFlyTime(const int _player_num, int _time);
		 *
		 * @brief	表示する飛行時間を設定
		 *
		 * @param 	_player_num	プレイヤー番号
		 * @param 	_time			飛行時間
		 */
		void SetFlyTime(const int _player_num, int _time);

	private:
		int m_graph_up; //!< 画像ハンドル
		int m_flytime[2];   //!< 飛行時間
	};
}