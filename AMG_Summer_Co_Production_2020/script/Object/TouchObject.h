/**
 * @file	AMG_Summer_Co_Production_2020\script\TouchObject.h.
 *
 * @brief	画面上から降ってくるタッチオブジェクト
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ObjectBase.h"

namespace illumism
{
	/**
  * @class	TouchObject
  *
  * @brief	タッチオブジェクトのクラス
  *
  */
	class TouchObject : public ObjectBase
	{
	public:

		/**
		 * @fn	TouchObject::TouchObject(int _num);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_num	タッチオブジェクトの種類
		 */
		TouchObject(int _num);
		~TouchObject();

		/**
		 * @fn	virtual OBJECT_TYPE TouchObject::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual OBJECT_TYPE GetType() { return m_type; }

		/**
		 * @fn	void TouchObject::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void TouchObject::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void TouchObject::Damage(Game& _game);
		 *
		 * @brief	オブジェクトの削除
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Damage(Game& _game);

		/**
		 * @fn	void TouchObject::Draw(Game& _game) override;
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game) override;

	private:
		ObjectBase::OBJECT_TYPE m_type; //!< オブジェクトのタイプを設定

		const int BODY_W = 220; //!< オブジェクトサイズ
		const int BODY_H = 220;
		int m_anim_frame;   //!< アニメーション開始フレームを記録
		int m_anim_graph[5];	//!<画像ハンドル
		bool m_damage_flag; //!<	タッチされたかの可否用フラグ
	};
}