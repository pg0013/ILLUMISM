/**
 * @file	AMG_Summer_Co_Production_2020\script\ObjectServer.h.
 *
 * @brief	�I�u�W�F�N�g���Ǘ�����T�[�o
 */

#pragma once
#include<vector>
#include"../Object/ObjectBase.h"

namespace illumism
{
	class Game;	//!<��d�C���N���[�h�h�~

	/**
	 * @class	ObjectServer
	 *
	 * @brief		���ׂẴI�u�W�F�N�g���Ǘ�����N���X
	 * 	@detail		vector�R���e�i�ŃI�u�W�F�N�g�̐����A���Z�A�`��A�����̊Ǘ����s��
	 *
	 */
	class ObjectServer
	{
	public:
		ObjectServer();
		~ObjectServer();

		/**
		 * @fn	void ObjectServer::Clear();
		 *
		 * @brief	�R���e�i�̒��g�����ׂč폜
		 *
		 */
		void Clear();

		/**
		 * @fn	void ObjectServer::Add(ObjectBase* _object);
		 *
		 * @brief	�R���e�i�ɒǉ��i�őO�ʂɕ\���j
		 *
		 * @param [in,out]	_object	�ǉ�����I�u�W�F�N�g�̃|�C���^
		 */
		void Add(ObjectBase* _object);

		/**
		 * @fn	void ObjectServer::Insert(ObjectBase* _object);
		 *
		 * @brief	�R���e�i�ɑ}���i�v���C���[�����ɕ\���j
		 *


		 *
		 * @param [in,out]	�}������I�u�W�F�N�g�̃|�C���^
		 */
		void Insert(ObjectBase* _object);

		/**
		 * @fn	void ObjectServer::Delete(ObjectBase* _object);
		 *
		 * @brief	�R���e�i����폜
		 *
		 * @param [in,out]	�폜����I�u�W�F�N�g�̃|�C���^
		 */
		void Delete(ObjectBase* _object);

		/**
		 * @fn	void ObjectServer::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void ObjectServer::Draw(Game& _game);
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game);

		/**
		 * @fn	std::vector<ObjectBase*> ObjectServer::*List()
		 *
		 * @brief	ObjectBase���i�[���Ă�R���e�i�ւ̃Q�b�^�[
		 *
		 * @returns	�R���e�i
		 */
		std::vector<ObjectBase*>* List() { return &m_vObject; }

	private:

		/**
		 * @fn	void ObjectServer::AddListObject();
		 *
		 * @brief	�ǉ����X�g�̃I�u�W�F�N�g��m_vObject�ɒǉ�
		 */
		void AddListObject();

		/**
		 * @fn	void ObjectServer::InsertListObject();
		 *
		 * @brief	�}�����X�g�̃I�u�W�F�N�g��m_vObject�ɑ}��
		 *	@author	Takuya Fujisawa
		 */
		void InsertListObject();

		/**
		 * @fn	void ObjectServer::DeleteListObject();
		 *
		 * @brief	�폜���X�g�̃I�u�W�F�N�g���폜
		 */
		void DeleteListObject();

		std::vector<ObjectBase*> m_vObject; //!< �I�u�W�F�N�g�i�[�R���e�i
		std::vector<ObjectBase*> m_vAdd;	//!< �ǉ��p�R���e�i
		std::vector<ObjectBase*> m_vInsert; //!< �}���p�R���e�i
		std::vector<ObjectBase*> m_vDelete; //!< �폜�p�R���e�i
	};
}