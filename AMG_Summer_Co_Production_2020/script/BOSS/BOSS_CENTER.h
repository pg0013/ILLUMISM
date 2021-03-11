/**
 * @file	AMG_Summer_Co_Production_2020\script\BOSS_CENTER.h.
 *
 * @brief	ボス中央パーツを管理
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
 * @class	BOSS_CENTER
 *
 * @brief	ボス中央パーツを管理
 *
 */
	class BOSS_CENTER : public ObjectBase
	{
	public:
		BOSS_CENTER();
		~BOSS_CENTER();

		/**
		 * @fn	virtual OBJECT_TYPE BOSS_CENTER::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::BOSS; }

		/**
		 * @fn	void BOSS_CENTER::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void BOSS_CENTER::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void BOSS_CENTER::Draw(Game& _game) override;
		 *
		 * @brief	ボス中央パーツを描画
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void BOSS_CENTER::Damage(Game& _game) override;
		 *
		 * @brief	ダメージ画像を描画
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Damage(Game& _game) override;

		/**
		 * @fn	void BOSS_CENTER::DrawHand(Game& _game,int _state,bool damage);
		 *
		 * @brief	腕のアニメーションを描画
		 *
		 * @param [in,out]	_game 		ゲームクラスの参照.
		 * @paam				  	_state		ボスの攻撃状態
		 * @param 		  		damage		ダメージを受けたか
		 */
		void DrawHand(Game& _game, int _state, bool damage);

		/**
		 * @fn	void BOSS_CENTER::SwithEyeGraph(Game& _game, int _state, bool damage);
		 *
		 * @brief	目の画像を切り替える処理
		 *
		 * @param [in,out]	_game 		ゲームクラスの参照.
		 * @paam				  	_state		ボスの攻撃状態
		 * @param 		  		damage		ダメージを受けたか
		 */
		void SwithEyeGraph(Game& _game, int _state, bool damage);

	private:

		int m_pyram_up_graph[2];	//!< 画像ハンドル
		int m_pyram_down_graph[2];
		int m_gear_graph[2];
		int m_eye_graph[9];
		int m_scrap_graph[2];
		int m_righthand_graph[2];
		int m_lefthand_graph[2];
		int m_fallhand_graph[13];
		int m_groundhand_graph[11];

		int m_startanim_frame;  //!< アニメーション開始フレームを記録
		int eye;	//!<	描画する目の種類を保存
		bool once_flag; //!< 状態移行時の初期化処理用フラグ
	};
}