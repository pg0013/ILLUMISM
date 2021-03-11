/**
 * @file	AMG_Summer_Co_Production_2020\script\ResourceServer.cpp.
 *
 * @brief	画像や音声ファイルを補完するリソースサーバのクラス
 */

#include "DxLib.h"
#include "../Server/ResourceServer.h"
using namespace illumism;

 // 静的メンバ実体
std::unordered_map<std::string, int>	ResourceServer::m_mapGraph;
std::unordered_map<std::string, sound::WAVEReader> ResourceServer::m_mapSound;
std::unordered_map < std::string, ResourceServer::DIVGRAPH> ResourceServer::m_mapDivGraph;


void ResourceServer::Init()
{
	m_mapGraph.clear();
	m_mapSound.clear();
}

void ResourceServer::Release()
{
	ClearMap();
}

void ResourceServer::ClearMap()
{
	for (auto itr = m_mapGraph.begin(); itr != m_mapGraph.end(); itr++)
	{
		DeleteGraph(itr->second);
	}

	for (auto itr = m_mapSound.begin(); itr != m_mapSound.end(); itr++)
	{
		free(itr->second.GetpBuffer());
	}

	m_mapGraph.clear();
	m_mapSound.clear();
}

int	 ResourceServer::LoadGraph(const TCHAR* _filename)
{
	// キーの検索
	auto itr = m_mapGraph.find(_filename);
	if (itr != m_mapGraph.end())
	{
		// キーがあった
		return itr->second;
	}
	// キーが無かったらキーとデータをmapに登録
	int cg = ::LoadGraph(_filename);
	m_mapGraph[_filename] = cg;

	return cg;
}

int ResourceServer::LoadDivGraph(const TCHAR* _filename, int _allnum,
	int _xnum, int _ynum, int _xsize, int _ysize,
	int* _handle)
{
	// キーの検索
	auto itr = m_mapDivGraph.find(_filename);
	if (itr != m_mapDivGraph.end())
	{
		//キーが有ったらデータをコピー
		for (int i = 0; i < itr->second.AllNum; i++)
		{
			_handle[i] = itr->second.graph_handle[i];
		}
		return 0;
	}

	//キーがなかったらメモリを作成
	int* tmp_handle = new int[_allnum];
	int error = ::LoadDivGraph(_filename, _allnum, _xnum, _ynum, _xsize, _ysize, tmp_handle);
	if (error == 0)//成功
	{
		//マップにキーとデータを登録
		m_mapDivGraph[_filename].AllNum = _allnum;
		m_mapDivGraph[_filename].graph_handle = tmp_handle;
		//データをコピー
		for (int i = 0; i < _allnum; i++)
			_handle[i] = tmp_handle[i];
	}
	return error;
}

sound::WAVEReader ResourceServer::LoadSound(const TCHAR* _filename)
{
	//キーの検索
	auto itr = m_mapSound.find(_filename);
	if (itr != m_mapSound.end())
	{
		//キー発見
		return itr->second;
	}
	//キーがなかったら音声ファイルを読み込み
	sound::WAVEReader _wavereader;
	_wavereader.LoadWAVE(_filename);

	m_mapSound[_filename] = _wavereader;
	return _wavereader;
}

void ResourceServer::RegisterGraph(const TCHAR* _filename)
{
	// キーの検索
	auto itr = m_mapGraph.find(_filename);
	if (itr != m_mapGraph.end())
	{
		//登録済みなのでなにもしない
		return;
	}

	//非同期で画像を読み込む
	SetUseASyncLoadFlag(TRUE);
	int cg = ::LoadGraph(_filename);
	SetUseASyncLoadFlag(FALSE);

	// キーとデータをmapに登録
	m_mapGraph[_filename] = cg;
}

void ResourceServer::RegisterDivGraph(const TCHAR* _filename, int _allnum,
	int _xnum, int _ynum, int _xsize, int _ysize)
{
	// キーの検索
	auto itr = m_mapDivGraph.find(_filename);
	if (itr != m_mapDivGraph.end())
	{
		//登録済みなのでなにもしない
		return;
	}
	int* tmp_handle = new int[_allnum];

	//非同期で画像を読み込む
	SetUseASyncLoadFlag(TRUE);
	int error = ::LoadDivGraph(_filename, _allnum, _xnum, _ynum, _xsize, _ysize, tmp_handle);
	SetUseASyncLoadFlag(FALSE);

	if (error == 0)//成功
	{
		//マップにキーとデータを登録
		m_mapDivGraph[_filename].AllNum = _allnum;
		m_mapDivGraph[_filename].graph_handle = tmp_handle;
	}
}