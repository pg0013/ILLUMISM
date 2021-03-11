/**
 * @file	AMG_Summer_Co_Production_2020\script\ObjectServer.h.
 *
 * @brief	オブジェクトを管理するサーバ
 */

#pragma once
#include<vector>
#include"../Object/ObjectBase.h"

namespace illumism
{
	class Game;	//!<二重インクルード防止

	/**
	 * @class	ObjectServer
	 *
	 * @brief		すべてのオブジェクトを管理するクラス
	 * 	@detail		vectorコンテナでオブジェクトの生成、演算、描画、消去の管理を行う
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
		 * @brief	コンテナの中身をすべて削除
		 *
		 */
		void Clear();

		/**
		 * @fn	void ObjectServer::Add(ObjectBase* _object);
		 *
		 * @brief	コンテナに追加（最前面に表示）
		 *
		 * @param [in,out]	_object	追加するオブジェクトのポインタ
		 */
		void Add(ObjectBase* _object);

		/**
		 * @fn	void ObjectServer::Insert(ObjectBase* _object);
		 *
		 * @brief	コンテナに挿入（プレイヤーより後ろに表示）
		 *


		 *
		 * @param [in,out]	挿入するオブジェクトのポインタ
		 */
		void Insert(ObjectBase* _object);

		/**
		 * @fn	void ObjectServer::Delete(ObjectBase* _object);
		 *
		 * @brief	コンテナから削除
		 *
		 * @param [in,out]	削除するオブジェクトのポインタ
		 */
		void Delete(ObjectBase* _object);

		/**
		 * @fn	void ObjectServer::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void ObjectServer::Draw(Game& _game);
		 *
		 * @brief	描画処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Draw(Game& _game);

		/**
		 * @fn	std::vector<ObjectBase*> ObjectServer::*List()
		 *
		 * @brief	ObjectBaseを格納してるコンテナへのゲッター
		 *
		 * @returns	コンテナ
		 */
		std::vector<ObjectBase*>* List() { return &m_vObject; }

	private:

		/**
		 * @fn	void ObjectServer::AddListObject();
		 *
		 * @brief	追加リストのオブジェクトをm_vObjectに追加
		 */
		void AddListObject();

		/**
		 * @fn	void ObjectServer::InsertListObject();
		 *
		 * @brief	挿入リストのオブジェクトをm_vObjectに挿入
		 *	@author	Takuya Fujisawa
		 */
		void InsertListObject();

		/**
		 * @fn	void ObjectServer::DeleteListObject();
		 *
		 * @brief	削除リストのオブジェクトを削除
		 */
		void DeleteListObject();

		std::vector<ObjectBase*> m_vObject; //!< オブジェクト格納コンテナ
		std::vector<ObjectBase*> m_vAdd;	//!< 追加用コンテナ
		std::vector<ObjectBase*> m_vInsert; //!< 挿入用コンテナ
		std::vector<ObjectBase*> m_vDelete; //!< 削除用コンテナ
	};
}