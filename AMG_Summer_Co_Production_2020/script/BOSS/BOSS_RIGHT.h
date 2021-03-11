/**
 * @file	AMG_Summer_Co_Production_2020\script\BOSS_RIGHT.h.
 *
 * @brief	�{�X�̉E�p�[�c���Ǘ�
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
  * @class	BOSS_RIGHT
  *
  * @brief	�{�X�̉E�p�[�c��`�悷��N���X
  *
  */
	class BOSS_RIGHT : public ObjectBase
	{
	public:
		BOSS_RIGHT();
		~BOSS_RIGHT();

		/**
		 * @fn	virtual OBJECT_TYPE BOSS_RIGHT::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::BOSS; }

		/**
		 * @fn	void BOSS_RIGHT::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();

		/**
		 * @fn	void BOSS_RIGHT::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void BOSS_RIGHT::Draw(Game& _game) override;
		 *
		 * @brief	�{�X�̉E�p�[�c��`��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void BOSS_RIGHT::Damage(Game& _game) override;
		 *
		 * @brief	�_���[�W�摜��`��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Damage(Game& _game) override;

	private:
		int m_right_a_graph[2]; //!< �摜�n���h��
		int m_right_b_graph[2];
		int m_right_c_graph[2];
		int m_rightgear1_graph[2];
		int m_rightgear2_graph[2];
		int m_rightgear3_graph[2];
	};
}