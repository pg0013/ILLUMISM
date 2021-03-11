/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeServer.h.
 *
 * @brief	モード管理を行うサーバー
 */

#pragma once
#include <list>
#include "../Mode/ModeBase.h"

namespace illumism
{
	class Game;

	/**
	 * @class	ModeServer
	 *
	 * @brief	A mode server.
	 *
	 */
	class	ModeServer
	{
		typedef	std::list<ModeBase*>		lstModeBase;

	public:

		/**
		 * @fn	ModeServer::ModeServer(Game& g);
		 *
		 * @brief	Constructor
		 *
		 * @param [in,out]	g	A Game to process.
		 */
		ModeServer(Game& g);
		virtual	~ModeServer();
		static ModeServer* _lpInstance;

		/**
		 * @fn	static ModeServer* ModeServer::GetInstance()
		 *
		 * @brief	モードサーバーのインスタンスを取得
		 *
		 * @returns	モードサーバーインスタンス
		 */
		static ModeServer* GetInstance() { return (ModeServer*)_lpInstance; }

		/**
		 * @fn	int ModeServer::Add(ModeBase* mode, int layer, const char* name);
		 *
		 * @brief	モードを追加
		 * 	@detail	登録はするが、一度メインを回さないといけない
		 *


		 *
		 * @param [in,out]	mode 	追加するモード.
		 * @param 		  	layer	表示するレイヤー.
		 * @param 		  	name 	追加するモードの名前.
		 *
		 * @returns	uid.
		 */
		int Add(ModeBase* mode, int layer, const char* name);

		/**
		 * @fn	int ModeServer::Del(ModeBase* mode);
		 *
		 * @brief	指定したモードを削除予約する
		 *
		 * @param [in,out]	mode	削除するモード
		 *
		 * @returns	0
		 */
		int Del(ModeBase* mode);

		/**
		 * @fn	ModeBase* ModeServer::Get(int uid);
		 *
		 * @brief	uidから指定したモードを取得
		 *
		 * @param 	uid	The UID to get.
		 *
		 * @return		指定したuidを持つモード
		 */
		ModeBase* Get(int uid);

		/**
		 * @fn	ModeBase* ModeServer::Get(const char* name);
		 *
		 * @brief	Gets a mode base* using the given name
		 *
		 * @param 	name	The name to get.
		 *
		 * @returns	指定した名前のモード
		 */
		ModeBase* Get(const char* name);

		/**
		 * @fn	int ModeServer::GetId(ModeBase* mode);
		 *
		 * @brief	uidを取得
		 *
		 * @param [in,out]	mode	モードポインタ
		 *
		 * @returns	指定したモードのuid
		 */
		int GetId(ModeBase* mode);

		/**
		 * @fn	int ModeServer::GetId(const char* name);
		 *
		 * @brief	uidを取得
		 *
		 * @param 	name	モード名
		 *
		 * @returns	指定したモードのuid
		 */
		int GetId(const char* name);

		/**
		 * @fn	const char* ModeServer::GetName(ModeBase* mode);
		 *
		 * @brief	モード名を取得
		 *
		 * @param [in,out]	mode	モードポインタ
		 *
		 * @returns	モード名
		 */
		const char* GetName(ModeBase* mode);

		/**
		 * @fn	const char* ModeServer::GetName(int uid);
		 *
		 * @brief	モード名を取得
		 *
		 * @param 	uid	The UID.
		 *
		 * @returns	モード名.
		 */
		const char* GetName(int uid);

		/**
		 * @fn	void ModeServer::Clear();
		 *
		 * @brief	モードサーバーのモードをすべて削除
		 *
		 */
		void Clear();

		/**
		 * @fn	int ModeServer::LayerTop()
		 *
		 * @brief	Layer top
		 *
		 * @returns	An int.
		 */
		int	 LayerTop() { return INT32_MAX; }

		/**
		 * @fn	static bool ModeServer::modeSort(const ModeBase* x, const ModeBase* y)
		 *
		 * @brief	レイヤー順にソートする
		 * @param 	x	ModeBase
		 * @param 	y	ModeBase
		 *
		 * @returns	xがyよりレイヤーが小さいかどうか
		 */
		static bool modeSort(const ModeBase* x, const ModeBase* y)
		{
			return x->_layer < y->_layer;
		}

		/**
		 * @fn	int ModeServer::ProcessInit();
		 *
		 * @brief	プロセスを回すための初期化
		 *
		 * @returns	An int.
		 */
		int ProcessInit();

		/**
		 * @fn	int ModeServer::Process();
		 *
		 * @brief	レイヤーの上の方から処理
		 *
		 * @returns	An int.
		 */
		int Process();

		/**
		 * @fn	int ModeServer::ProcessFinish();
		 *
		 * @brief	プロセスを回した後の後始末
		 *
		 * @returns	An int.
		 */
		int ProcessFinish();

		/**
		 * @fn	int ModeServer::DrawInit();
		 *
		 * @brief	描画を回すための初期化
		 *
		 * @returns	An int.
		 */
		int DrawInit();

		/**
		 * @fn	int ModeServer::Draw();
		 *
		 * @brief	レイヤーの下の方から処理
		 *
		 * @returns	An int.
		 */
		int Draw();

		/**
		 * @fn	int ModeServer::DrawFinish();
		 *
		 * @brief	描画を回した後の後始末
		 *
		 * @returns	An int.
		 */
		int DrawFinish();

		/**
		 * @fn	int ModeServer::SkipProcessUnderLayer();
		 *
		 * @brief	現Processで、今処理しているレイヤーより下のレイヤーは、処理を呼ばない
		 *
		 * @returns	An int.
		 */
		int SkipProcessUnderLayer();

		/**
		 * @fn	int ModeServer::SkipDrawUnderLayer();
		 *
		 * @brief	現Processで、今処理しているレイヤーより下のレイヤーは、描画を呼ばない
		 *
		 * @returns	An int.
		 */
		int SkipDrawUnderLayer();

		/**
		 * @fn	int ModeServer::PauseProcessUnderLayer();
		 *
		 * @brief	現Processで、今処理しているレイヤーより下のレイヤーは、時間経過を止める
		 *
		 * @returns	An int.
		 */
		int PauseProcessUnderLayer();

	private:

		/**
		 * @fn	int ModeServer::Release(ModeBase* mode);
		 *
		 * @brief	削除＆delete
		 *
		 * @param [in,out]	mode	モードベースポインタ
		 *
		 * @returns	An int.
		 */
		int Release(ModeBase* mode);

		/**
		 * @fn	bool ModeServer::IsDelRegist(ModeBase* mode);
		 *
		 * @brief	削除予約されているか？
		 *
		 * @param [in,out]	mode	モードベースポインタ
		 *
		 * @returns	削除予約の可否
		 */
		bool IsDelRegist(ModeBase* mode);

		/**
		 * @fn	bool ModeServer::IsAdd(ModeBase* mode);
		 *
		 * @brief	リストにあるか？
		 *
		 * @param [in,out]	mode	モードベースポインタ
		 *
		 * @returns	追加予約の可否
		 */
		bool IsAdd(ModeBase* mode);

	public:
		Game& _game;

	private:
		lstModeBase		_vMode; //!< モードリスト
		int				_uid_count; //!< uidカウンタ
		lstModeBase		_vModeAdd;  //!< 追加予約
		lstModeBase		_vModeDel;  //!< 削除予約

		ModeBase* _nowMode; //!< 現在呼び出し中のモード
		ModeBase* _skipProcessMode; //!< このモードより下はProcessを呼ばない
		ModeBase* _skipDrawMode;	//!< このモードより下はDrawを呼ばない
		ModeBase* _pauseProcessMode;	//!< このモードより下はProcess時に時間経過をさせない
	};
}