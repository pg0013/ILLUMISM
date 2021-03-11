/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeGame.h.
 *
 * @brief	ゲームモード
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ModeBase.h"
#include"../Object/BackGround.h"
#include"../Player/Player.h"
#include"../BOSS/BOSS.h"
#include"../Game.h"
#include"../Sound/PlayWAVE.h"
#include"../Server/ObjectServer.h"
#include"../Controller/TouchObjectController.h"
#include"../Controller/CoopMoveController.h"
#include"../Controller/GameUIController.h"
#include"../Controller/SpotlightController.h"
#include"../Object/Camera.h"
#include"../UI/Time_UI.h"
#include"Dxlib.h"

namespace illumism
{
	//<画像表示用座標
	namespace
	{
		constexpr int READY_pos_x = 1920 / 2;
		constexpr int READY_pos_y = 1080 / 2;
		constexpr int FIGHT_pos_x = 1920 / 2;
		constexpr int FIGHT_pos_y = 1080 / 2;
		constexpr int FINISH_pos_x = 1920 / 2;
		constexpr int FINISH_pos_y = 1080 / 2;
		constexpr int COUNT_pos_x = 1920 / 2;
		constexpr int COUNT_pos_y = 1080 / 3 + 75;
	}

	/**
	 * @class	ModeGame
	 *
	 * @brief	インゲーム
	 *
	 */
	class ModeGame : public ModeBase
	{
	public:
		/**
		 * @fn	ModeGame::ModeGame(const int _P1charactor, const int _P2charactor);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_P1charactor		プレイヤー1のキャラクター種類
		 * @param 	_P2charactor		プレイヤー2のキャラクター種類
		 */
		ModeGame(const int _P1charactor, const int _P2charactor);

		/**
		 * @fn	virtual bool ModeGame::Initialize(Game& _game);
		 *
		 * @brief	初期化処理
		 * @detail	ModeServer接続時に一度だけ呼ばれる
		 *
		 * @param [in,out]	_game	Gameクラスの参照
		 *
		 * @returns	初期化成功の可否
		 */
		virtual bool Initialize(Game& _game);

		/**
		 * @fn	virtual bool ModeGame::Terminate(Game& _game);
		 *
		 * @brief	終了処理
		 * @detail	ModeServerから削除される際、一度だけ呼ばれる
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 *
		 * @returns	終了処理成功の可否
		 */
		virtual bool Terminate(Game& _game);

		/**
		 * @fn	virtual bool ModeGame::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 *
		 * @returns	演算処理成功の可否
		 */
		virtual bool Process(Game& _game);

		/**
		 * @fn	virtual bool ModeGame::Draw(Game& _game);
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game ゲームクラスの参照
		 *
		 * @returns	描画処理成功の可否
		 */
		virtual bool Draw(Game& _game);

		/**
		 * @fn	void ModeGame::SetPlayerPoint(const int _player_num, const int _player_point);
		 *
		 * @brief	プレイヤーの所持ポイントを記録
		 *
		 * @param 	_player_num  	The player number.
		 * @param 	_player_point	The player point.
		 */
		void SetPlayerPoint(const int _player_num, const int _player_point);

		/**
		 * @fn	const int ModeGame::GetPlayerPoint(int _num)
		 *
		 * @brief	Gets player point
		 *
		 * @param 	_num	プレイヤー番号
		 *
		 * @returns	The player point.
		 */
		const int GetPlayerPoint(int _num) { return m_player_point[_num - 1]; }

		/**
		 * @fn	const int ModeGame::GetPlayerCharactor(int _num)
		 *
		 * @brief	プレイヤーのキャラクター種類を記録
		 *
		 * @param 	_num	プレイヤー番号
		 *
		 * @returns	The player charactor.
		 */
		const int GetPlayerCharactor(int _num) { return m_player_charactor[_num - 1]; }

		/**
		 * @struct	BONUS_PARAM
		 *
		 * @brief	ボーナスモード用パラメータ
		 *
		 */
		struct BONUS_PARAM
		{
			int BOSS_DAMAGE;	//!< ボスに与えたダメージ量
			int MAX_COMBO;  //!< 最大コンボ数
			int DEATH_COUNT;	//!< 死亡回数
		};
		BONUS_PARAM m_bonus_param[2] = { 0,0,0 };

		/**
		 * @fn	void ModeGame::AddPlayerDamage(int _num, int _damage)
		 *
		 * @brief	ボスに与えたダメージ量を記録
		 *
		 * @param 	_num   	プレイヤー番号
		 * @param 	_damage	ダメージ量
		 */
		void AddPlayerDamage(int _num, int _damage) { m_bonus_param[_num - 1].BOSS_DAMAGE += _damage; }

		/**
		 * @fn	const int ModeGame::GetPlayerDamage(int _num)
		 *
		 * @brief	ボスに与えたダメージ量を取得
		 *
		 * @param 	_num   	プレイヤー番号
		 * @returns	ダメージ量
		 */
		const int GetPlayerDamage(int _num) { return m_bonus_param[_num - 1].BOSS_DAMAGE; }

		/**
		 * @fn	void ModeGame::AddMaxCombo(int _num, int _combo)
		 *
		 * @brief	最大コンボ数を記録
		 *
		 * @param 	_num  	プレイヤー番号
		 * @param 	_combo		最大コンボ数
		 */
		void AddMaxCombo(int _num, int _combo) { m_bonus_param[_num - 1].MAX_COMBO = _combo; }

		/**
		 * @fn	const int ModeGame::GetMaxCombo(int _num)
		 *
		 * @brief	最大コンボ数を取得
		 *
		 * @param 	_num	プレイヤー番号
		 *
		 * @returns	最大コンボ数
		 */
		const int GetMaxCombo(int _num) { return m_bonus_param[_num - 1].MAX_COMBO; }

		/**
		 * @fn	void ModeGame::AddDeathCount(int _num, int _count)
		 *
		 * @brief	死亡回数を記録
		 *
		 * @param 	_num  	プレイヤー番号
		 * @param 	_count	死亡回数
		 */
		void AddDeathCount(int _num, int _count) { m_bonus_param[_num - 1].DEATH_COUNT += _count; }

		/**
		 * @fn	const int ModeGame::GetDeathCount(int _num)
		 *
		 * @brief	死亡回数を取得
		 *
		 * @param 	_num	プレイヤー番号
		 *
		 * @returns	死亡回数
		 */
		const int GetDeathCount(int _num) { return m_bonus_param[_num - 1].DEATH_COUNT; }

		/**
		 * @fn	const BONUS_PARAM ModeGame::GetBonusParam(int _num)
		 *
		 * @brief	ボーナスパラメータを取得
		 *
		 * @param 	_num	プレイヤー番号
		 *
		 * @returns	The bonus parameter.
		 */
		const BONUS_PARAM GetBonusParam(int _num) { return m_bonus_param[_num - 1]; }

		Camera m_camera;

		BackGround m_background;

		TouchObjectController m_touch_object_controller;

		SpotlightController m_spotlight_controller;

		CoopMoveController m_coopmove_controller;

		GameUIController m_gameUI_controller;

		Time_UI m_timeUI;

		bool	m_stopObjProcess;   //!< オブジェクト処理をストップする.

	private:

		/**
		 * @fn	void ModeGame::DrawGameSign(Game& _game);
		 *
		 * @brief	READY?,FIGHT!!,FINISHを描画
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void DrawGameSign(Game& _game);

		/**
		 * @fn	void ModeGame::DrawGameCount(Game& _game);
		 *
		 * @brief	ゲーム終了までのカウントを描画
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void DrawGameCount(Game& _game);

		/**
		 * @fn	void ModeGame::GenerateGameCount(const char* _filename, const int _count, Game& _game);
		 *
		 * @brief	ゲーム終了カウントを生成
		 *
		 * @param 		  	_filename	ファイル名
		 * @param 		  	_count		ゲーム終了から何秒前か
		 * @param [in,out]	_game	 ゲームクラスの参照
		 */
		void GenerateGameCount(const char* _filename, const int _count, Game& _game);

		int m_player_point[2] = { 0 };  //!< プレイヤー所持ポイント
		int m_player_charactor[2] = { 0 };  //!< キャラクター種類
		int m_vignette_graph;   //!< ビネット画像ハンドル
	};
}