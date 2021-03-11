/**
 * @file	AMG_Summer_Co_Production_2020\script\ObjectServer.cpp.
 *
 * @brief	���ׂẴI�u�W�F�N�g���Ǘ�����N���X
				vector�R���e�i�ŃI�u�W�F�N�g�̐����A���Z�A�`��A�����̊Ǘ����s��
 */

#include"DxLib.h"
#include"../Server/ObjectServer.h"
using namespace illumism;

ObjectServer::ObjectServer()
{
	m_vObject.clear();
	m_vAdd.clear();
	m_vDelete.clear();
}

ObjectServer::~ObjectServer()
{
	Clear();
}

void ObjectServer::Clear()
{
	for (auto iter = m_vObject.begin(); iter != m_vObject.end(); iter++)
	{
		delete(*iter);
	}
	m_vObject.clear();
}

void ObjectServer::Add(ObjectBase* _object)
{
	m_vAdd.push_back(_object);
}

void ObjectServer::Insert(ObjectBase* _object)
{
	m_vInsert.push_back(_object);
}

void ObjectServer::Delete(ObjectBase* _object)
{
	m_vDelete.push_back(_object);
}

void ObjectServer::AddListObject()
{
	for (auto iterAdd = m_vAdd.begin(); iterAdd != m_vAdd.end(); iterAdd++)
	{
		m_vObject.push_back((*iterAdd));
	}
	m_vAdd.clear();
}

void ObjectServer::InsertListObject()
{
	for (auto iterInsert = m_vInsert.begin(); iterInsert != m_vInsert.end(); iterInsert++)
	{
		//�^�b�`�I�u�W�F�N�g�͍őO�ʂɕ\��
		if ((*iterInsert)->GetType() == ObjectBase::OBJECT_TYPE::TOUCH_S ||
			(*iterInsert)->GetType() == ObjectBase::OBJECT_TYPE::TOUCH_C)
		{
			auto iter = m_vObject.end() - 2;
			iter = m_vObject.insert(iter, (*iterInsert));
			iter++;
			continue;
		}

		auto iter = m_vObject.begin();
		iter = m_vObject.insert(iter, (*iterInsert));
		iter++;
	}
	m_vInsert.clear();
}

void ObjectServer::DeleteListObject()
{
	for (auto iterDel = m_vDelete.begin(); iterDel != m_vDelete.end(); iterDel++)
	{
		for (auto iter = m_vObject.begin(); iter != m_vObject.end();)
		{
			if ((*iter) == (*iterDel))
			{
				delete (*iter);
				iter = m_vObject.erase(iter);//erase�͍폜�������̃C�e���[�^��Ԃ�
			}
			else
			{
				iter++;
			}
		}
	}
	m_vDelete.clear();
}

void ObjectServer::Process(Game& _game)
{
	//�ǉ����X�g�̃I�u�W�F�N�g��ǉ�
	AddListObject();
	InsertListObject();

	//�I�u�W�F�N�g��Process�֐����Ăяo��
	for (auto iter = m_vObject.begin(); iter != m_vObject.end(); iter++)
	{
		(*iter)->Process(_game);
	}

	//�폜���X�g�̃I�u�W�F�N�g���i�[�R���e�i����폜
	DeleteListObject();
}

void ObjectServer::Draw(Game& _game)
{
	//�I�u�W�F�N�g��Draw�֐����Ăяo��
	for (auto iter = m_vObject.begin(); iter != m_vObject.end(); iter++)
	{
		(*iter)->Draw(_game);
	}
}