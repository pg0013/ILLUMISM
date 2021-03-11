/**
 * @file	AMG_Summer_Co_Production_2020\script\FallAttack.h.
 *
 * @brief	��ʏォ�痎���Ă���U������
  * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
  * @class	FallAttack
  *
  * @brief	�������̍U���N���X
  *
  */
	class FallAttack : public ObjectBase
	{
	public:
		FallAttack(int _num);
		~FallAttack();

		/**
		 * @fn	virtual OBJECT_TYPE FallAttack::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::FALLATTACK; }

		/**
		 * @fn	void FallAttack::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();

		/**
		 * @fn	void FallAttack::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void FallAttack::Draw(Game& _game) override;
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void FallAttack::Damage(Game& _game);
		 *
		 * @brief	�v���C���[�ɓ����邩�A�n�ʂ܂œ��B����ƃI�u�W�F�g���폜
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Damage(Game& _game);

		/**
		 * @fn	inline void FallAttack::SetSpeed(int _speed)
		 *
		 * @brief	�ړ����x��ݒ�
		 *
		 * @param 	_speed	The speed.
		 */
		inline void SetSpeed(int _speed) { m_speed = _speed; }

	private:
		const int BODY_W = 220; //!< �摜�T�C�Y
		const int BODY_H = 220;
		int m_speed;	//!< �ړ����x
	};
}