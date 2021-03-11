/**
 * @file	AMG_Summer_Co_Production_2020\script\ResourceServer.h.
 *
 * @brief	�摜�≹���t�@�C����⊮���郊�\�[�X�T�[�o�̃N���X
 * 	@detail	�ÓI�����o�Ȃ̂ŁA�ǂ��ł����s�\
 */

#pragma once
#include	<unordered_map>
#include"../Sound/WAVEReader.h"

namespace illumism
{
	/**
	 * @class	ResourceServer
	 *
	 * @brief	�摜�≹���t�@�C����⊮���郊�\�[�X�T�[�o�̃N���X
	 */
	class ResourceServer
	{
	public:

		/**
		 * @fn	static void ResourceServer::Init();
		 *
		 * @brief	����������
		 *
		 */
		static void	Init();

		/**
		 * @fn	static void ResourceServer::Release();
		 *
		 * @brief	�T�[�o�̉������
		 */
		static void	Release();

		/**
		 * @fn	static void ResourceServer::ClearMap();
		 *
		 * @brief	���ׂẴf�[�^���폜
		 */
		static void	ClearMap();

		/**
		 * @fn	static int ResourceServer::LoadGraph(const TCHAR* _filename);
		 *
		 * @brief	�摜�����[�h
		 * @param 	_filename	�摜��
		 *
		 * @returns	�摜�n���h��
		 */
		static int LoadGraph(const TCHAR* _filename);

		/**
		 * @fn	static int ResourceServer::LoadDivGraph(const TCHAR* _filename,int _allnum, int _xnum,int _ynum,int _xsize,int _ysize, int* _handle);
		 *
		 * @brief	�摜�𕪊��ǂݍ���
		 *
		 * @author	Takuya Fujisawa
		 *
		 * @param 		  	_filename	�t�@�C����
		 * @param 		  	_allnum  	��������
		 * @param 		  	_xnum	 	x�����̕�����
		 * @param 		  	_ynum	 	y�����̕�����
		 * @param 		  	_xsize   	�����摜�̉摜��
		 * @param 		  	_ysize   	�����摜�̉摜�̍���
		 * @param [in,out]	_handle �n���h����ۑ�����擪�|�C���^
		 *
		 * @returns	�摜�n���h��
		 */
		static int LoadDivGraph(const TCHAR* _filename, int _allnum,
			int _xnum, int _ynum, int _xsize, int _ysize,
			int* _handle);

		/**
		 * @fn	static void ResourceServer::RegisterGraph(const TCHAR* _filename);
		 *
		 * @brief	�摜��񓯊��ǂݍ��݂��A���\�[�X�T�[�o�ɓo�^
		 *
		 * @author	Takuya Fujisawa
		 *
		 * @param 	_filename	�摜��
		 */
		static void RegisterGraph(const TCHAR* _filename);

		/**
		 * @fn	static void ResourceServer::RegisterDivGraph(const TCHAR* _filename, int _allnum, int _xnum, int _ynum, int _xsize, int _ysize);
		 *
		 * @brief	�摜��񓯊��ŕ����ǂݍ��݂��A���\�[�X�T�[�o�ɓo�^
		 * @author	Takuya Fujisawa
		 *
		 * @param 		  	_filename	�t�@�C����
		 * @param 		  	_allnum  	��������
		 * @param 		  	_xnum	 	x�����̕�����
		 * @param 		  	_ynum	 	y�����̕�����
		 * @param 		  	_xsize   	�����摜�̉摜��
		 * @param 		  	_ysize   	�����摜�̉摜�̍���
		 */
		static void RegisterDivGraph(const TCHAR* _filename, int _allnum,
			int _xnum, int _ynum, int _xsize, int _ysize);

		/**
		 * @fn	static WAVEReader ResourceServer::LoadSound(const TCHAR* _filename);
		 *
		 * @brief	�����t�@�C����ǂݍ���
		 *
		 * @author	Takuya Fujisawa
		 *
		 * @param 	_filename	�t�@�C����
		 *
		 * @returns	�����f�[�^
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

		static std::unordered_map<std::string, int>	m_mapGraph; //!< �摜�p�}�b�v
		static std::unordered_map<std::string, sound::WAVEReader> m_mapSound;  //!< �����p�}�b�v
		static std::unordered_map < std::string, DIVGRAPH> m_mapDivGraph;//�����p�摜�}�b�v
	};
}