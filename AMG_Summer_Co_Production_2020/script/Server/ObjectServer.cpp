/**
 * @file	AMG_Summer_Co_Production_2020\script\ObjectServer.cpp.
 *
 * @brief	すべてのオブジェクトを管理するクラス
				vectorコンテナでオブジェクトの生成、演算、描画、消去の管理を行う
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
		//タッチオブジェクトは最前面に表示
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
				iter = m_vObject.erase(iter);//eraseは削除した次のイテレータを返す
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
	//追加リストのオブジェクトを追加
	AddListObject();
	InsertListObject();

	//オブジェクトのProcess関数を呼び出し
	for (auto iter = m_vObject.begin(); iter != m_vObject.end(); iter++)
	{
		(*iter)->Process(_game);
	}

	//削除リストのオブジェクトを格納コンテナから削除
	DeleteListObject();
}

void ObjectServer::Draw(Game& _game)
{
	//オブジェクトのDraw関数を呼び出し
	for (auto iter = m_vObject.begin(); iter != m_vObject.end(); iter++)
	{
		(*iter)->Draw(_game);
	}
}