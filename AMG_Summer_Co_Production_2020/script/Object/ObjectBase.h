#pragma once
/**
 * @file	AMG_Summer_Co_Production_2020\script\ObjectBase.h.
 *
 * @brief	**オブジェクトの基底クラス
 * @author	Takuya Fujisawa
 */

namespace illumism
{
	class Game;	//二重インクルード防止

	/**
	 * @class	ObjectBase
	 *
	 * @brief	オブジェクトの基底クラス
	 *
	 */
	class ObjectBase
	{
	public:
		ObjectBase();
		~ObjectBase();

		/**
		 * @enum	OBJECT_TYPE
		 *
		 * @brief	オブジェクトの種類用定数
		 */
		enum class OBJECT_TYPE
		{
			PLAYER, FLY, BULLET, TOUCH_S, TOUCH_C, COOP, POINT,
			NOHIT, UI, ATTACK, SPOTLIGHT, SPMOVE, PARTICLE,
			BOSS, FALLATTACK, GROUNDATTACK, CROSSBEAM, LASER
		};

		/**
		 * @fn	virtual OBJECT_TYPE ObjectBase::GetType() = 0;
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual OBJECT_TYPE GetType() = 0;

		/**
		 * @struct	PARAMS
		 *
		 * @brief	プレイヤー用パラメータ
		 *
		 */
		struct PARAMS
		{
			int HP;
			int MP;
			int POINT;
		};

		/**
		 * @fn	void ObjectBase::AddHP(int _value)
		 *
		 * @brief	HPに加算
		 *
		 * @param 	_value	ダメージ量.
		 */
		void AddHP(int _value) { m_params.HP += _value; }

		/**
		 * @fn	void ObjectBase::AddMP(int _value)
		 *
		 * @brief	MPに値を加算
		 *
		 * @param 	_value	加算する値
		 */
		void AddMP(int _value) { m_params.MP += _value; }

		/**
		 * @fn	void ObjectBase::AddPOINT(int _value)
		 *
		 * @brief	ポイントを加算
		 *
		 * @param 	_value	加算する値
		 */
		void AddPOINT(int _value) { m_params.POINT += _value; }

		/**
		 * @fn	int ObjectBase::GetHP()
		 *
		 * @brief	HPを返す
		 *
		 * @returns	The hp.
		 */
		int GetHP() { return m_params.HP; }

		/**
		 * @fn	int ObjectBase::GetMP()
		 *
		 * @brief	MPを返す
		 *
		 * @returns	The mp.
		 */
		int GetMP() { return m_params.MP; }

		/**
		 * @fn	int ObjectBase::GetPOINT()
		 *
		 * @brief	所持ポイント数を返す
		 *
		 * @returns	The point
		 */
		int GetPOINT() { return m_params.POINT; }

		/**
		 * @fn	virtual void ObjectBase::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		virtual void Init();

		/**
		 * @fn	virtual void ObjectBase::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		virtual void Process(Game& _game);

		/**
		 * @fn	virtual void ObjectBase::Draw(Game& _game);
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		virtual void Draw(Game& _game);

		/**
		 * @fn	virtual void ObjectBase::SetDirection(Game& _game, int _num, bool _turn_flag)
		 *
		 * @brief	オブジェクトの方向を設定
		 *
		 * @param [in,out]	_game	  	ゲームクラスの参照
		 * @param 		  	_num	  		プレイヤー番号
		 * @param 		  	_turn_flag		画像反転フラグ
		 */
		virtual void SetDirection(Game& _game, int _num, bool _turn_flag) {}

		/**
		 * @fn	virtual bool ObjectBase::IsHit(ObjectBase& _object);
		 *
		 * @brief	オブジェクト同士の当たり判定処理
		 *
		 * @param [in,out]	_object	オブジェクトベースの参照
		 *
		 * @returns	当たり判定の可否
		 */
		virtual bool IsHit(ObjectBase& _object);

		/**
		 * @fn	virtual void ObjectBase::Damage(Game& _game)
		 *
		 * @brief	オブジェクトの削除
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		virtual void Damage(Game& _game) {}

		/**
		 * @fn	inline void ObjectBase::SetPosition(int _x, int _y)
		 *
		 * @brief	座標を設定
		 *
		 * @param 	_x		x座標
		 * @param 	_y		y座標
		 */
		inline void SetPosition(int _x, int _y) { m_x = _x; m_y = _y; }

		/**
		 * @fn	inline int ObjectBase::GetWidth()
		 *
		 * @brief	Gets the width
		 *
		 * @returns	The width.
		 */
		inline int GetWidth() { return m_width; }

		/**
		 * @fn	inline int ObjectBase::GetHeight()
		 *
		 * @brief	Gets the height
		 *
		 * @returns	The height.
		 */
		inline int GetHeight() { return m_height; }

		/**
		 * @fn	inline int ObjectBase::GetPosX()
		 *
		 * @brief	X座標を返す
		 *
		 * @returns	The position x coordinate.
		 */
		inline int  GetPosX() { return m_x; }

		/**
		 * @fn	inline int ObjectBase::GetPosY()
		 *
		 * @brief	Y座標を返す
		 *
		 * @returns	The position y coordinate.
		 */
		inline int  GetPosY() { return m_y; }

		/**
		 * @fn	inline int ObjectBase::GetPosHit_x()
		 *
		 * @brief	当たり判定の左上x座標を返す
		 *
		 * @returns	The position hit x coordinate.
		 */
		inline int  GetPosHit_x() { return m_hit_x; }

		/**
		 * @fn	inline int ObjectBase::GetPosHit_y()
		 *
		 * @brief	当たり判定の左上y座標を返す
		 *
		 * @returns	The position hit y coordinate.
		 */
		inline int  GetPosHit_y() { return m_hit_y; }

		/**
		 * @fn	inline int ObjectBase::GetPosHit_w()
		 *
		 * @brief	当たり判定の幅を返す
		 *
		 * @returns	当たり判定の幅.
		 */
		inline int  GetPosHit_w() { return m_hit_w; }

		/**
		 * @fn	inline int ObjectBase::GetPosHit_h()
		 *
		 * @brief	当たり判定の高さを返す
		 *
		 * @returns	当たり判定の高さ
		 */
		inline int  GetPosHit_h() { return m_hit_h; }

		/**
		 * @fn	inline int ObjectBase::GetHitNoCount()
		 *
		 * @brief	当たり判定無効時間を返す
		 *
		 * @returns	当たり判定無効カウンタ
		 */
		inline int GetHitNoCount() { return m_hit_no_count; }

		/**
		 * @fn	inline bool ObjectBase::GetIsHitFlag()
		 *
		 * @brief	当たり判定が有効か返す
		 *
		 * @returns	当たり判定有効フラグ
		 */
		inline bool GetIsHitFlag() { return m_ishit_flag; }

		/**
		 * @fn	inline int ObjectBase::GetPlayerNum()
		 *
		 * @brief	プレイヤー番号を返す
		 * @detail	オブジェクトがどのプレイヤーに属したものか調べるため
		 *
		 * @returns	プレイヤー番号
		 */
		inline int GetPlayerNum() { return m_player_num; }

		/**
		 * @brief　オブジェクトの向きを返す.
		 * 
		 * @return オブジェクトの向き
		 */
		inline int GetDirection_x() { return m_direction_x; }

	protected:
		PARAMS m_params;	//!<	プレイヤー用パラメータ

		int m_graph;	//!< 描画用グラフィックハンドル
		int m_x, m_y;				//!<座標
		int m_width, m_height;	//!<幅、高さ
		int m_speed;					//!<速さ

		//!<当たり判定用座標
		int m_hit_x, m_hit_y;
		int m_hit_w, m_hit_h;

		int m_direction_x;  //!< 方向
		int m_direction_y;

		bool m_turn_flag;   //!< 描画反転フラグ
		bool m_ishit_flag;  //!< 当たり判定有効フラグ

		int m_frame_count;  //!< フレームカウンタ
		int m_hit_no_count; //!< 無敵時間カウンタ

		int m_player_num;   //!< playerごとにbossに与えたダメージ記録用変数
	};
}