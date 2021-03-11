/**
 * @file	AMG_Summer_Co_Production_2020\script\CrossLaser.h.
 *
 * @brief	��ʒ[����̃��[�U�[�U�����s��
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
 * @class	CrossLaser
 *
 * @brief	��ʒ[����̃��[�U�[�U���s���N���X
 *
 */
	class CrossLaser : public ObjectBase
	{
	public:
		CrossLaser(int _num);
		~CrossLaser();

		/**
		 * @fn	virtual OBJECT_TYPE CrossLaser::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::CROSSBEAM; }

		/**
		 * @fn	void CrossLaser::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();

		/**
		 * @fn	void CrossLaser::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void CrossLaser::Draw(Game& _game) override;
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void CrossLaser::Damage(Game& _game)override;
		 *
		 * @brief	�����ꏊ���甽�Α��̉�ʒ[�܂œ��B����ƁA�I�u�W�F�N�g���폜
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Damage(Game& _game)override;

		/**
		 * @fn	inline void CrossLaser::SetSpeed(int _speed)
		 *
		 * @brief	�ړ����x��ݒ�
		 *
		 * @param 	_speed	The speed.
		 */
		inline void SetSpeed(int _speed) { m_speed = _speed; }

	private:
		int	 direction;	//!< �㉺���E���������肷��ϐ�
		int m_speed;	//!< �ړ����x
	};
}