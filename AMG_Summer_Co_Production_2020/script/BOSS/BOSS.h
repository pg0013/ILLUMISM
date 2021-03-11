/**
 * @file	AMG_Summer_Co_Production_2020\script\BOSS.h.
 *
 * @brief	ボスオブジェクト
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"
#include"BOSS_CENTER.h"
#include"BOSS_LEFT.h"
#include"BOSS_RIGHT.h"
#include"../Sound/PlayWAVE.h"

namespace illumism
{
	class Game;	//<二重インクルード防止

/**
 * @class	BOSS
 *
 * @brief	ボスオブジェクトクラス
 *
 */
	class BOSS : public ObjectBase
	{
	public:
		BOSS();
		~BOSS();

		/**
		 * @fn	virtual OBJECT_TYPE BOSS::GetType()
		 *
		 * @brief	オブジェクトの種類を返す
		 *
		 * @returns	オブジェクトの種類
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::BOSS; }

		/**
		 * @enum	BOSS_STATE
		 *
		 * @brief	ボスの状態遷移用変数
		 */
		enum BOSS_STATE
		{
			APPEAR, DEFAULT, MOVE, FALL_ATTACK, LASER_ATTACK, SIMPLE_LASER, GROUND_ATTACK, CROSS_LASER,
			DAMAGE, DESTROY
		};

		/**
		 * @fn	void BOSS::AddHP(int _damage)
		 *
		 * @brief	ダメージ量をHPに加算
		 *
		 * @param 	_damage	The damage.
		 */
		void AddHP(int _damage) { m_params.HP += _damage; }

		/**
		 * @fn	void BOSS::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		void Init();

		/**
		 * @fn	void BOSS::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void BOSS::Draw(Game& _game) override;
		 *
		 * @brief	ボスを描画
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void BOSS::Hit(Game& _game);
		 *
		 * @brief 当たり判定
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Hit(Game& _game);

		/**
		 * @fn	void BOSS::Damage(Game& _game);
		 *
		 * @brief	ダメージを受けたときにダメージ画像へ切り替え
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Damage(Game& _game);

		/**
		 * @fn	void BOSS::Destroy(Game& _game);
		 *
		 * @brief	ボス撃破時の処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Destroy(Game& _game);

	private:
		/**
		 * @fn	void BOSS::State(Game& _game);
		 *
		 * @brief ボスの状態遷移
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void State(Game& _game);

		/**
		 * @fn	void BOSS::SelectNextAttack();
		 *
		 * @brief	行う攻撃を選ぶ処理
		 * @detail	初めは FALL_ATTACK, LASER_ATTACK, SIMPLE_LASER, GROUND_ATTACK, CROSS_LASER
		 * 				の順で攻撃を行い、すべての攻撃を行ったら前回の攻撃以外の4種からランダムで選ぶ
		 *
		 */
		void SelectNextAttack();

		/**
		 * @fn	void BOSS::Appear(Game& _game);
		 *
		 * @brief	ボス出現処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Appear(Game& _game);

		/**
		 * @fn	void BOSS::Move(Game& _game);
		 *
		 * @brief	ボス移動処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Move(Game& _game);

		/**
		 * @fn	void BOSS::FallAttack(Game& _game);
		 *
		 * @brief　落ちもの攻撃処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void FallAttack(Game& _game);

		/**
		 * @fn	void BOSS::GenerateFallAttack(Game& _game);
		 *
		 * @brief	落ちもの攻撃を生成
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void GenerateFallAttack(Game& _game);

		/**
		 * @fn	void BOSS::GroundAttack(Game& _game);
		 *
		 * @brief	地面から棘攻撃処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void GroundAttack(Game& _game);

		/**
		 * @fn	void BOSS::GenerateGroundAttack(Game& _game);
		 *
		 * @brief	棘攻撃を生成
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void GenerateGroundAttack(Game& _game);

		/**
		 * @fn	void BOSS::SimpleLaser(Game& _game);
		 *
		 * @brief	一方向のみのレーザー攻撃処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void SimpleLaser(Game& _game);

		/**
		 * @fn	void BOSS::GenerateSimpleLaser(Game& _game);
		 *
		 * @brief	一方向のみレーザー攻撃を生成
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void GenerateSimpleLaser(Game& _game);

		/**
		 * @fn	void BOSS::CrossLaser(Game& _game);
		 *
		 * @brief	複数方向レーザー攻撃処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void CrossLaser(Game& _game);

		/**
		 * @fn	void BOSS::GenerateCrossLaser(Game& _game);
		 *
		 * @brief	複数方向レーザー攻撃を生成
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void GenerateCrossLaser(Game& _game);

		/**
		 * @fn	void BOSS::LaserAttack(Game& _game);
		 *
		 * @brief	プレイヤーに向かうレーザー攻撃処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void LaserAttack(Game& _game);

		/**
		 * @fn	void BOSS::GenerateLaserAttack(Game& _game);
		 *
		 * @brief	プレイヤーに向かうレーザー攻撃を生成
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void GenerateLaserAttack(Game& _game);

		/**
		 * @fn	void BOSS::PlaySE(const char* _filename, const float _pan, Game& _game);
		 *
		 * @brief	効果音再生
		 *
		 * @param 		  	_filename	音声ファイル名
		 * @param 		  	_pan	 		左右バランス設定、x座標を入れる
		 * @param [in,out]	_game	 ゲームクラスの参照
		 */
		void PlaySE(const char* _filename, Game& _game);

		BOSS_CENTER m_center;   //!< ボス中央パーツを描画
		BOSS_LEFT m_left;   //!< ボス左パーツを描画
		BOSS_RIGHT m_right; //!< ボス右パーツを描画

		sound::PlayWAVE m_se;  //!< 効果音

	private:
		int m_boss_state;   //!< 状態遷移用変数
		int m_pre_boss_state;   //!< 前回の状態遷移を記録

		int m_speed_x;  //!< 移動速度
		int m_speed_y;

		bool once_flag; //!< 状態遷移移行時に一度だけ行われる初期化処理用フラグ
		bool once_death_flag;   //!< 撃破時用フラグ
		bool attack_random_flag;	//!< 攻撃をランダムで行うフラグ
		bool m_damage_flag; //!< ダメージを受けたときのフラグ

		int m_start_frame;  //!< 状態移行時のフレームを記録
		int m_damage_frame; //!< ダメージを受けたときのフレームを記録

		bool m_blinking_flag;   //!< ボス撃破時の点滅カウント用フラグ
	};
}