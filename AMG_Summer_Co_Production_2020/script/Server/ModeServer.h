/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeServer.h.
 *
 * @brief	���[�h�Ǘ����s���T�[�o�[
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
		 * @brief	���[�h�T�[�o�[�̃C���X�^���X���擾
		 *
		 * @returns	���[�h�T�[�o�[�C���X�^���X
		 */
		static ModeServer* GetInstance() { return (ModeServer*)_lpInstance; }

		/**
		 * @fn	int ModeServer::Add(ModeBase* mode, int layer, const char* name);
		 *
		 * @brief	���[�h��ǉ�
		 * 	@detail	�o�^�͂��邪�A��x���C�����񂳂Ȃ��Ƃ����Ȃ�
		 *


		 *
		 * @param [in,out]	mode 	�ǉ����郂�[�h.
		 * @param 		  	layer	�\�����郌�C���[.
		 * @param 		  	name 	�ǉ����郂�[�h�̖��O.
		 *
		 * @returns	uid.
		 */
		int Add(ModeBase* mode, int layer, const char* name);

		/**
		 * @fn	int ModeServer::Del(ModeBase* mode);
		 *
		 * @brief	�w�肵�����[�h���폜�\�񂷂�
		 *
		 * @param [in,out]	mode	�폜���郂�[�h
		 *
		 * @returns	0
		 */
		int Del(ModeBase* mode);

		/**
		 * @fn	ModeBase* ModeServer::Get(int uid);
		 *
		 * @brief	uid����w�肵�����[�h���擾
		 *
		 * @param 	uid	The UID to get.
		 *
		 * @return		�w�肵��uid�������[�h
		 */
		ModeBase* Get(int uid);

		/**
		 * @fn	ModeBase* ModeServer::Get(const char* name);
		 *
		 * @brief	Gets a mode base* using the given name
		 *
		 * @param 	name	The name to get.
		 *
		 * @returns	�w�肵�����O�̃��[�h
		 */
		ModeBase* Get(const char* name);

		/**
		 * @fn	int ModeServer::GetId(ModeBase* mode);
		 *
		 * @brief	uid���擾
		 *
		 * @param [in,out]	mode	���[�h�|�C���^
		 *
		 * @returns	�w�肵�����[�h��uid
		 */
		int GetId(ModeBase* mode);

		/**
		 * @fn	int ModeServer::GetId(const char* name);
		 *
		 * @brief	uid���擾
		 *
		 * @param 	name	���[�h��
		 *
		 * @returns	�w�肵�����[�h��uid
		 */
		int GetId(const char* name);

		/**
		 * @fn	const char* ModeServer::GetName(ModeBase* mode);
		 *
		 * @brief	���[�h�����擾
		 *
		 * @param [in,out]	mode	���[�h�|�C���^
		 *
		 * @returns	���[�h��
		 */
		const char* GetName(ModeBase* mode);

		/**
		 * @fn	const char* ModeServer::GetName(int uid);
		 *
		 * @brief	���[�h�����擾
		 *
		 * @param 	uid	The UID.
		 *
		 * @returns	���[�h��.
		 */
		const char* GetName(int uid);

		/**
		 * @fn	void ModeServer::Clear();
		 *
		 * @brief	���[�h�T�[�o�[�̃��[�h�����ׂč폜
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
		 * @brief	���C���[���Ƀ\�[�g����
		 * @param 	x	ModeBase
		 * @param 	y	ModeBase
		 *
		 * @returns	x��y��背�C���[�����������ǂ���
		 */
		static bool modeSort(const ModeBase* x, const ModeBase* y)
		{
			return x->_layer < y->_layer;
		}

		/**
		 * @fn	int ModeServer::ProcessInit();
		 *
		 * @brief	�v���Z�X���񂷂��߂̏�����
		 *
		 * @returns	An int.
		 */
		int ProcessInit();

		/**
		 * @fn	int ModeServer::Process();
		 *
		 * @brief	���C���[�̏�̕����珈��
		 *
		 * @returns	An int.
		 */
		int Process();

		/**
		 * @fn	int ModeServer::ProcessFinish();
		 *
		 * @brief	�v���Z�X���񂵂���̌�n��
		 *
		 * @returns	An int.
		 */
		int ProcessFinish();

		/**
		 * @fn	int ModeServer::DrawInit();
		 *
		 * @brief	�`����񂷂��߂̏�����
		 *
		 * @returns	An int.
		 */
		int DrawInit();

		/**
		 * @fn	int ModeServer::Draw();
		 *
		 * @brief	���C���[�̉��̕����珈��
		 *
		 * @returns	An int.
		 */
		int Draw();

		/**
		 * @fn	int ModeServer::DrawFinish();
		 *
		 * @brief	�`����񂵂���̌�n��
		 *
		 * @returns	An int.
		 */
		int DrawFinish();

		/**
		 * @fn	int ModeServer::SkipProcessUnderLayer();
		 *
		 * @brief	��Process�ŁA���������Ă��郌�C���[��艺�̃��C���[�́A�������Ă΂Ȃ�
		 *
		 * @returns	An int.
		 */
		int SkipProcessUnderLayer();

		/**
		 * @fn	int ModeServer::SkipDrawUnderLayer();
		 *
		 * @brief	��Process�ŁA���������Ă��郌�C���[��艺�̃��C���[�́A�`����Ă΂Ȃ�
		 *
		 * @returns	An int.
		 */
		int SkipDrawUnderLayer();

		/**
		 * @fn	int ModeServer::PauseProcessUnderLayer();
		 *
		 * @brief	��Process�ŁA���������Ă��郌�C���[��艺�̃��C���[�́A���Ԍo�߂��~�߂�
		 *
		 * @returns	An int.
		 */
		int PauseProcessUnderLayer();

	private:

		/**
		 * @fn	int ModeServer::Release(ModeBase* mode);
		 *
		 * @brief	�폜��delete
		 *
		 * @param [in,out]	mode	���[�h�x�[�X�|�C���^
		 *
		 * @returns	An int.
		 */
		int Release(ModeBase* mode);

		/**
		 * @fn	bool ModeServer::IsDelRegist(ModeBase* mode);
		 *
		 * @brief	�폜�\�񂳂�Ă��邩�H
		 *
		 * @param [in,out]	mode	���[�h�x�[�X�|�C���^
		 *
		 * @returns	�폜�\��̉�
		 */
		bool IsDelRegist(ModeBase* mode);

		/**
		 * @fn	bool ModeServer::IsAdd(ModeBase* mode);
		 *
		 * @brief	���X�g�ɂ��邩�H
		 *
		 * @param [in,out]	mode	���[�h�x�[�X�|�C���^
		 *
		 * @returns	�ǉ��\��̉�
		 */
		bool IsAdd(ModeBase* mode);

	public:
		Game& _game;

	private:
		lstModeBase		_vMode; //!< ���[�h���X�g
		int				_uid_count; //!< uid�J�E���^
		lstModeBase		_vModeAdd;  //!< �ǉ��\��
		lstModeBase		_vModeDel;  //!< �폜�\��

		ModeBase* _nowMode; //!< ���݌Ăяo�����̃��[�h
		ModeBase* _skipProcessMode; //!< ���̃��[�h��艺��Process���Ă΂Ȃ�
		ModeBase* _skipDrawMode;	//!< ���̃��[�h��艺��Draw���Ă΂Ȃ�
		ModeBase* _pauseProcessMode;	//!< ���̃��[�h��艺��Process���Ɏ��Ԍo�߂������Ȃ�
	};
}