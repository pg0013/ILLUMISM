/**
 * @file	AMG_Summer_Co_Production_2020\script\ResourceServer.cpp.
 *
 * @brief	�摜�≹���t�@�C����⊮���郊�\�[�X�T�[�o�̃N���X
 */

#include "DxLib.h"
#include "../Server/ResourceServer.h"
using namespace illumism;

 // �ÓI�����o����
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
	// �L�[�̌���
	auto itr = m_mapGraph.find(_filename);
	if (itr != m_mapGraph.end())
	{
		// �L�[��������
		return itr->second;
	}
	// �L�[������������L�[�ƃf�[�^��map�ɓo�^
	int cg = ::LoadGraph(_filename);
	m_mapGraph[_filename] = cg;

	return cg;
}

int ResourceServer::LoadDivGraph(const TCHAR* _filename, int _allnum,
	int _xnum, int _ynum, int _xsize, int _ysize,
	int* _handle)
{
	// �L�[�̌���
	auto itr = m_mapDivGraph.find(_filename);
	if (itr != m_mapDivGraph.end())
	{
		//�L�[���L������f�[�^���R�s�[
		for (int i = 0; i < itr->second.AllNum; i++)
		{
			_handle[i] = itr->second.graph_handle[i];
		}
		return 0;
	}

	//�L�[���Ȃ������烁�������쐬
	int* tmp_handle = new int[_allnum];
	int error = ::LoadDivGraph(_filename, _allnum, _xnum, _ynum, _xsize, _ysize, tmp_handle);
	if (error == 0)//����
	{
		//�}�b�v�ɃL�[�ƃf�[�^��o�^
		m_mapDivGraph[_filename].AllNum = _allnum;
		m_mapDivGraph[_filename].graph_handle = tmp_handle;
		//�f�[�^���R�s�[
		for (int i = 0; i < _allnum; i++)
			_handle[i] = tmp_handle[i];
	}
	return error;
}

sound::WAVEReader ResourceServer::LoadSound(const TCHAR* _filename)
{
	//�L�[�̌���
	auto itr = m_mapSound.find(_filename);
	if (itr != m_mapSound.end())
	{
		//�L�[����
		return itr->second;
	}
	//�L�[���Ȃ������特���t�@�C����ǂݍ���
	sound::WAVEReader _wavereader;
	_wavereader.LoadWAVE(_filename);

	m_mapSound[_filename] = _wavereader;
	return _wavereader;
}

void ResourceServer::RegisterGraph(const TCHAR* _filename)
{
	// �L�[�̌���
	auto itr = m_mapGraph.find(_filename);
	if (itr != m_mapGraph.end())
	{
		//�o�^�ς݂Ȃ̂łȂɂ����Ȃ�
		return;
	}

	//�񓯊��ŉ摜��ǂݍ���
	SetUseASyncLoadFlag(TRUE);
	int cg = ::LoadGraph(_filename);
	SetUseASyncLoadFlag(FALSE);

	// �L�[�ƃf�[�^��map�ɓo�^
	m_mapGraph[_filename] = cg;
}

void ResourceServer::RegisterDivGraph(const TCHAR* _filename, int _allnum,
	int _xnum, int _ynum, int _xsize, int _ysize)
{
	// �L�[�̌���
	auto itr = m_mapDivGraph.find(_filename);
	if (itr != m_mapDivGraph.end())
	{
		//�o�^�ς݂Ȃ̂łȂɂ����Ȃ�
		return;
	}
	int* tmp_handle = new int[_allnum];

	//�񓯊��ŉ摜��ǂݍ���
	SetUseASyncLoadFlag(TRUE);
	int error = ::LoadDivGraph(_filename, _allnum, _xnum, _ynum, _xsize, _ysize, tmp_handle);
	SetUseASyncLoadFlag(FALSE);

	if (error == 0)//����
	{
		//�}�b�v�ɃL�[�ƃf�[�^��o�^
		m_mapDivGraph[_filename].AllNum = _allnum;
		m_mapDivGraph[_filename].graph_handle = tmp_handle;
	}
}