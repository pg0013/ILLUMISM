/**
 * @file	AMG_Summer_Co_Production_2020\script\Game.h.
 *
 * @brief	ゲームシーン
 * @author	Takuya Fujisawa
 */

#pragma once
#include"Server/ObjectServer.h"
#include"Server/ModeServer.h"
#include"Sound/PlayWAVE.h"
#include"Dxlib.h"

namespace illumism
{

	namespace
	{
		constexpr auto SCREEN_WIDTH = 1920; //!< 画面設定
		constexpr auto SCREEN_HEIGHT = 1080;
		constexpr auto SCREEN_DEPTH = 32;

		constexpr auto THUMB_MAX = 32767.0f;
		constexpr auto ANALOG_MIN = 0.1f;

		constexpr auto GROUND = 925;
		constexpr auto GAME_PLAYER_NUM = 2; //!< プレイヤー人数

		constexpr auto STAGE_WIDTH_LEFT = 170;  //!< ステージ幅
		constexpr auto STAGE_WIDTH_RIGHT = 1840;

		constexpr auto START_TIME = 180;	//!< ゲーム開始時間

		constexpr int LEFT = -1;
		constexpr int RIGHT = 1;
		constexpr int UP = -1;
		constexpr int DOWN = 1;

		constexpr int JUMP_HEIGHT = 27; //!< ジャンプの高さ
		constexpr int BULLET_MAX = 99;  //!< 弾丸描画可能数
		constexpr int ANIM_FRAME = 10;  //!< アニメーション再生可能フレーム

		constexpr int  MOVE_SPEED = 12; //!< 移動速度

		constexpr int FLY_SPEED = 25;   //!< 飛行スピード
		constexpr int FLY_TIME = 40;	//!< 飛行時間

		constexpr int BULLET_DAMAGE = -5;   //!< 弾丸ダメージ
		constexpr int ATTACK_DAMAGE = -10;  //!< アタックダメージ
		constexpr int SPMOVE_DAMAGE = -30; //!< 必殺技ダメージ
		constexpr int BOSS_ATTACK_DAMAGE = -10; //!< ボス攻撃のダメージ

		constexpr int MP_MAX = 100; //!< HP最大値

		float SE_VOLUME = 0.8f; //!< SE音量
		float BGM_VOLUME = 0.6f;	//!< BGM音量

		/**
		 * @enum	CHARACTOR
		 *
		 * @brief	キャラクター種類定数
		 */
		enum CHARACTOR
		{
			NARI1, NONAME1, NARI2, NONAME2
		};
	}

	/**
	 * @class	Game
	 *
	 * @brief	ゲームシーンクラス
	 *
	 */
	class Game
	{
	public:
		Game();
		~Game();

		/**
		 * @fn	void Game::Input();
		 *
		 * @brief	コントローラーからの入力処理
		 *
		 */
		void Input();

		/**
		 * @fn	void Game::Process();
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 */
		void Process();

		/**
		 * @fn	void Game::Draw();
		 *
		 * @brief	描画処理
		 *
		 */
		void Draw();

		/**
		 * @fn	const void Game::SetExitFlag(const bool _flag)
		 *
		 * @brief	メインループを抜けるフラグを設定
		 *
		 * @param 	_flag		メインループを抜けるフラグ
		 */
		const void SetExitFlag(const bool _flag) { m_exit_flag = _flag; }

		/**
		 * @fn	const bool Game::GetExitFlag()
		 *
		 * @brief	メインループを抜けるフラグを取得
		 *
		 * @returns	メインループを抜けるフラグ
		 */
		const bool GetExitFlag() { return m_exit_flag; }

		int m_gkey[GAME_PLAYER_NUM] = { 0 };	//!< ゲームパッド入力
		int m_trigger_key[GAME_PLAYER_NUM] = { 0 }; //!< ゲームパッドのトリガー入力

		//DINPUT_JOYSTATE m_dinput_state[GAME_PLAYER_NUM];	//!< Lトリガー,Rトリガー,スティック入力用
		XINPUT_STATE m_xinput_state[GAME_PLAYER_NUM]; //!< Lトリガー,Rトリガー,スティック入力用

		ObjectServer m_objectserver;	//!< オブジェクトサーバ

		ModeServer* m_modeserver;   //!<モードサーバ

		sound::PlayWAVE m_bgm; //!< BGM

		sound::PlayWAVE m_se;  //!< SE
	private:
		int m_gframe_count; //!< ゲームシーン内のフレームカウンタ
		bool m_exit_flag;   //!< メインループを抜けるフラグ
	};
}