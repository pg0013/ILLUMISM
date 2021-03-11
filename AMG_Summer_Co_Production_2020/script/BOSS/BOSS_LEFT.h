/**
 * @file	AMG_Summer_Co_Production_2020\script\BOSS_LEFT.h.
 *
 * @brief	�{�X�̍��p�[�c���Ǘ�
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
  * @class	BOSS_LEFT
  *
  * @brief	�{�X�̍��p�[�c��`�悷��N���X
  *
  */
	class BOSS_LEFT : public ObjectBase
	{
	public:
		BOSS_LEFT();
		~BOSS_LEFT();

		/**
		 * @fn	virtual OBJECT_TYPE BOSS_LEFT::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::BOSS; }

		/**
		 * @fn	void BOSS_LEFT::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();

		/**
		 * @fn	void BOSS_LEFT::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void BOSS_LEFT::Draw(Game& _game) override;
		 *
		 * @brief	�{�X�̍��p�[�c��`��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void BOSS_LEFT::Damage(Game& _game) override;
		 *
		 * @brief	�{�X�̃_���[�W�摜��`��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Damage(Game& _game) override;
	private:
		int m_leftsand_graph[2];	//!< �摜�n���h��
		int m_leftclock_graph[2];
		int m_leftgear1_graph[2];
		int m_leftgear2_graph[2];
		int m_leftgear3_graph[2];
	};
}