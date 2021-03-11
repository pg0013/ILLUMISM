/**
 * @file	AMG_Summer_Co_Production_2020\script\ResourceServer.h.
 *
 * @brief	画像や音声ファイルを補完するリソースサーバのクラス
 * 	@detail	静的メンバなので、どこでも実行可能
 */

#pragma once
#include	<unordered_map>
#include"../Sound/WAVEReader.h"

namespace illumism
{
	/**
	 * @class	ResourceServer
	 *
	 * @brief	画像や音声ファイルを補完するリソースサーバのクラス
	 */
	class ResourceServer
	{
	public:

		/**
		 * @fn	static void ResourceServer::Init();
		 *
		 * @brief	初期化処理
		 *
		 */
		static void	Init();

		/**
		 * @fn	static void ResourceServer::Release();
		 *
		 * @brief	サーバの解放処理
		 */
		static void	Release();

		/**
		 * @fn	static void ResourceServer::ClearMap();
		 *
		 * @brief	すべてのデータを削除
		 */
		static void	ClearMap();

		/**
		 * @fn	static int ResourceServer::LoadGraph(const TCHAR* _filename);
		 *
		 * @brief	画像をロード
		 * @param 	_filename	画像名
		 *
		 * @returns	画像ハンドル
		 */
		static int LoadGraph(const TCHAR* _filename);

		/**
		 * @fn	static int ResourceServer::LoadDivGraph(const TCHAR* _filename,int _allnum, int _xnum,int _ynum,int _xsize,int _ysize, int* _handle);
		 *
		 * @brief	画像を分割読み込み
		 *
		 * @author	Takuya Fujisawa
		 *
		 * @param 		  	_filename	ファイル名
		 * @param 		  	_allnum  	分割総数
		 * @param 		  	_xnum	 	x方向の分割数
		 * @param 		  	_ynum	 	y方向の分割数
		 * @param 		  	_xsize   	分割画像の画像幅
		 * @param 		  	_ysize   	分割画像の画像の高さ
		 * @param [in,out]	_handle ハンドルを保存する先頭ポインタ
		 *
		 * @returns	画像ハンドル
		 */
		static int LoadDivGraph(const TCHAR* _filename, int _allnum,
			int _xnum, int _ynum, int _xsize, int _ysize,
			int* _handle);

		/**
		 * @fn	static void ResourceServer::RegisterGraph(const TCHAR* _filename);
		 *
		 * @brief	画像を非同期読み込みし、リソースサーバに登録
		 *
		 * @author	Takuya Fujisawa
		 *
		 * @param 	_filename	画像名
		 */
		static void RegisterGraph(const TCHAR* _filename);

		/**
		 * @fn	static void ResourceServer::RegisterDivGraph(const TCHAR* _filename, int _allnum, int _xnum, int _ynum, int _xsize, int _ysize);
		 *
		 * @brief	画像を非同期で分割読み込みし、リソースサーバに登録
		 * @author	Takuya Fujisawa
		 *
		 * @param 		  	_filename	ファイル名
		 * @param 		  	_allnum  	分割総数
		 * @param 		  	_xnum	 	x方向の分割数
		 * @param 		  	_ynum	 	y方向の分割数
		 * @param 		  	_xsize   	分割画像の画像幅
		 * @param 		  	_ysize   	分割画像の画像の高さ
		 */
		static void RegisterDivGraph(const TCHAR* _filename, int _allnum,
			int _xnum, int _ynum, int _xsize, int _ysize);

		/**
		 * @fn	static WAVEReader ResourceServer::LoadSound(const TCHAR* _filename);
		 *
		 * @brief	音声ファイルを読み込み
		 *
		 * @author	Takuya Fujisawa
		 *
		 * @param 	_filename	ファイル名
		 *
		 * @returns	音声データ
		 */
		static sound::WAVEReader LoadSound(const TCHAR* _filename);

	private:
		/**
		 * @struct	DIVGRAPH
		 *
		 * @brief	A divgraph.
		 *
		 */
		typedef struct
		{
			int AllNum;
			int* graph_handle;
		}DIVGRAPH;

		static std::unordered_map<std::string, int>	m_mapGraph; //!< 画像用マップ
		static std::unordered_map<std::string, sound::WAVEReader> m_mapSound;  //!< 音声用マップ
		static std::unordered_map < std::string, DIVGRAPH> m_mapDivGraph;//分割用画像マップ
	};
}