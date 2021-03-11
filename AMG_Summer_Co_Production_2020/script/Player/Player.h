/**
 * @file	AMG_Summer_Co_Production_2020\script\Player.h.
 *
 * @brief	プレイヤーに関する処理
  * @author	Takuya Fujisawa
 */

#pragma once
#include"../Object/ObjectBase.h"
#include"../Sound/PlayWAVE.h"

namespace illumism
{
	/**
	 * @class	Player
	 *
	 * @brief	プレイヤークラス
	 *
	 */
	class Player :public ObjectBase
	{
	public:

		/**
		 * @fn	Player::Player(const int _num,const int _charatype);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_num	  	プレイヤー番号
		 * @param 	_charatype	選択キャラクター
		 */
		Player(const int _num, const int _charatype);
		~Player();

		/**
		 * @fn	virtual OBJECT_TYPE Player::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual OBJECT_TYPE GetType() { return m_object_type; }

		/**
		 * @fn	void Player::SetType(OBJECT_TYPE _object_type)
		 *
		 * @brief	オブジェクトの種類を設定
		 *
		 * @param 	_object_type	オブジェクトの種類
		 */
		void SetType(OBJECT_TYPE _object_type) { m_object_type = _object_type; }

		/**
		 * @enum	PLAYER_STATE
		 *
		 * @brief	プレイヤーの状態遷移用定数
		 */
		enum PLAYER_STATE
		{
			APPEAR, MOVE, JUMP, SHOOT, ATTACK, FLY, TOUCH, DAMAGE, HIT, APPEAL, SPMOVE, RESPOWN
		};

		/**
		 * @fn	void Player::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void Player::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void Player::Draw(Game& _game) override;
		 *
		 * @brief	プレイヤーを描画
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game) override;

	private:
		/**
		 * @fn	void Player::Input(Game& _game);
		 *
		 * @brief	コントローラーから入力を検知し、状態を遷移する処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Input(Game& _game);

		/**
		 * @fn	void Player::State(Game& _game);
		 *
		 * @brief	状態遷移を行う処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void State(Game& _game);

		/**
		 * @fn	void Player::Appear(Game& _game);
		 *
		 * @brief	プレイヤー登場時の処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Appear(Game& _game);

		/**
		 * @fn	void Player::Move(Game& _game);
		 *
		 * @brief	移動処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Move(Game& _game);

		/**
		 * @fn	void Player::Jump(Game& _game);
		 *
		 * @brief	ジャンプ処理（Aボタン）
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Jump(Game& _game);

		/**
		 * @fn	void Player::Shoot(Game& _game);
		 *
		 * @brief	弾丸を発射する攻撃処理(RT)
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Shoot(Game& _game);

		/**
		 * @fn	void Player::Attack(Game& _game);
		 *
		 * @brief	ATTACK攻撃を行う処理（Bボタン）
		 *
		 * @param [in,out]	_game	ゲームクラスの参照.
		 */
		void Attack(Game& _game);

		/**
		 * @fn	void Player::Fly(Game& _game);
		 *
		 * @brief	飛行モード処理（LT）
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Fly(Game& _game);

		/**
		 * @fn	void Player::Touch(Game& _game);
		 *
		 * @brief	タッチアクションの処理（Xボタン）
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Touch(Game& _game);

		/**
		 * @fn	void Player::Appeal(Game& _game);
		 *
		 * @brief	アピールアクションの処理（LB）
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Appeal(Game& _game);

		/**
		 * @fn	void Player::SPMove(Game& _game);
		 *
		 * @brief	必殺技アクションの処理（Yボタン）
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void SPMove(Game& _game);

		/**
		 * @fn	void Player::Hit(Game& _game);
		 *
		 * @brief	他オブジェクトとの当たり判定処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Hit(Game& _game);

		/**
		 * @fn	void Player::Damage(Game& _game);
		 *
		 * @brief	ダメージを受けたときの処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Damage(Game& _game);

		/**
		 * @brief	ダメージを受けたときにプレイヤー方向をダメージ元の位置によって変える処理.
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void SetDamagedDirection(Game& _game);
		/**
		 * @fn	void Player::Respawn(Game& _game);
		 *
		 * @brief	HP=0になった時のリスポーン処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Respawn(Game& _game);

		/**
		 * @fn	void Player::UpdatePlayerUI(Game& _game);
		 *
		 * @brief	プレイヤーUIのパラメータを更新
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void UpdatePlayerUI(Game& _game);

		/**
		 * @fn	void Player::OffScreen();
		 *
		 * @brief	画面外への移動を制限する処理
		 *
		 */
		void OffScreen();

		/**
		 * @fn	void Player::ParamsProcess(Game& _game);
		 *
		 * @brief	プレイヤーのパラメータに関する処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void ParamsProcess(Game& _game);

		/**
		 * @fn	void Player::LoadCharaGraph(const int _charatype);
		 *
		 * @brief	キャラクター画像をロードする処理
		 *
		 * @param 	_charatype	プレイヤー選択キャラ
		 */
		void LoadCharaGraph(const int _charatype);

		/**
		 * @fn	void Player::PlaySE(const char* _filename, Game& _game);
		 *
		 * @brief	効果音再生
		 *
		 * @param 		  	_filename	音声ファイル名
		 * @param 		  	_pan	 		左右バランス設定、x座標を入れる
		 * @param [in,out]	_game	 ゲームクラスの参照
		 */
		void PlaySE(const char* _filename, Game& _game);

		/**
		 * @fn	void Player::GenerateComboEffect(Game& _game);
		 *
		 * @brief	コンボ数表示エフェクトを生成
		 *
		 * @param [in,out]	_game	 ゲームクラスの参照
		 */
		void GenerateComboEffect(Game& _game);

		/**
		 * @fn	void Player::GenerateFlyParticle(Game& _game);
		 *
		 * @brief	飛行モードのパーティクルを生成
		 *
		 * @param [in,out]	_game	 ゲームクラスの参照
		 */
		void GenerateFlyParticle(Game& _game);

		/**
		 * @fn	void Player::GenerateTouchParticle(Game& _game);
		 *
		 * @brief	タッチ成功時のパーティクルを生成
		 *
		 * @param [in,out]	_game	 ゲームクラスの参照
		 */
		void GenerateTouchParticle(Game& _game, ObjectBase* iter);

		/**
		 * @fn	virtual void ObjectBase::SetDirection(Game& _game, int _num, bool _turn_flag)
		 *
		 * @brief	オブジェクトの方向を設定
		 *
		 * @param [in,out]	_game	  	ゲームクラスの参照
		 * @param 		  	_num	  		プレイヤー番号
		 * @param 		  	_turn_flag		画像反転フラグ
		 */
		void SetDirection(Game& _game, int _num, bool _turn_flag) override;

		sound::PlayWAVE m_se;  //!< 効果音

	private:
		int PLAYER_NUM; //!< プレイヤー番号

		OBJECT_TYPE m_object_type;  //!< オブジェクトの種類用変数

		int m_player_state; //!< プレイヤーの状態遷移用変数

		const int BODY_W = 100; //!< プレイヤーサイズ
		const int BODY_H = 150;

		int m_inertia;  //!< 移動時の慣性用変数

		ObjectBase* m_Attack;   //!< ATTACK用当たり判定

		ObjectBase* m_spmove;   //!< 必殺技オブジェクト

		int m_falling_speed;	//!< 空中にいるときの落下速度

		int m_bullet_frame_count;   //!<弾を等間隔で発射するためのフレームカウンタ

		bool m_attack_flag; //!< ATTACKとSHOOT同時押し禁止用のフラグ

		int m_attacked_point;   //!< ATTACKされたら相手にポイントを加算

		int m_move_flag;	//!< 移動制限を行うフラグ

		int m_pushRT_frame; //!< RTが押されたときのフレームを記録（ボタン2度押し用）

		int m_pushRT_count; //!< RTが指定時間内に押された数をカウント

		bool m_RT_flag;//!<トリガー入力検出用フラグ
		bool m_oldRT_flag;//!<トリガー入力検出用フラグ

		// < アニメーションのフレームを記録.
		int m_jump_frame;
		int m_attack_frame;
		int m_spmove_frame;
		int m_touch_frame;
		int m_appeal_frame;
		int m_damage_frame;

		bool m_animation_running_flag;  //!< アニメーションが実行中のフラグ
		bool m_appeal_flag; //!< アピール中にアピールが実行されないためのフラグ
		bool m_spmove_flag; //!< 必殺技中にアピールが実行されないためのフラグ
		bool m_touch_flag;  //!< タッチ中に他アクションが実行されたいためのフラグ
		bool m_fly_flag;	//!< 飛行中に他アクションが実行されないためのフラグ

		int m_fly_time; //!< 飛行時間
		int m_fly_frame;	//!< FLY開始のフレームを記録
		bool m_fly_trigger_flag;	//!< LT用triggerフラグ

		int m_respawn_time; //!< リスポーン時間のカウンタ

		int m_isAlive_flag; //!< リスポーン中はプレイヤーを描画しないフラグ

		int m_combo;	//!< プレイヤーコンボ数
		int m_max_combo;	//!< 最大コンボ記録用変数

		//!<アクションごとの画像ハンドル
		int m_wait_graph[30];
		int m_dash_graph[20];
		int m_shootdash_graph;
		int m_jump_graph[27];
		int m_shoot_graph[5];
		int m_shoot_up_graph[5];
		int m_shoot_upleft_graph[5];
		int m_shoot_downleft_graph[5];
		int m_dashshoot_graph[20];
		int m_dashshoot_up_graph[20];
		int m_dashshoot_upleft_graph[20];
		int m_dashshoot_downleft_graph[20];
		int m_touch_graph[15];
		int m_lightball_graph;
		int m_appeal_graph[40];
		int m_specialmove_graph;
		int m_coopmove_graph;
		int m_damage_graph[15];
		int m_attack_graph[27];
		int m_death_graph[45];
		int m_noname_toucheffect[7] = { 0 };
		int m_return_graph;
	};
}