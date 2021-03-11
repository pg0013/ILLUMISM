/**
 * @file	AMG_Summer_Co_Production_2020\script\CoopMoveObject.h.
 *
 * @brief	�A�s�[���𓯎��ɍs���ƌ���鋦�͋Z�N���X
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ObjectBase.h"

namespace illumism
{
	/**
	 * @class	CoopMoveObject
	 *
	 * @brief	���͋Z�̃I�u�W�F�N�g�N���X
	 *
	 */
	class CoopMoveObject : public ObjectBase
	{
	public:
		CoopMoveObject();
		~CoopMoveObject();

		/**
		 * @fn	virtual OBJECT_TYPE CoopMoveObject::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual OBJECT_TYPE GetType() { return OBJECT_TYPE::COOP; }

		/**
		 * @fn	void CoopMoveObject::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();

		/**
		 * @fn	void CoopMoveObject::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void CoopMoveObject::Draw(Game& _game) override;
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void CoopMoveObject::Damage(Game& _game) override;
		 *
		 * @brief	�I�u�W�F�N�g���폜
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Damage(Game& _game) override;
	};
}