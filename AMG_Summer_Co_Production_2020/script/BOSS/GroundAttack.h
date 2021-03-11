/**
 * @file	AMG_Summer_Co_Production_2020\script\GroundAttack.h.
 *
 * @brief	�n�ʂ���˂��o���U������
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
 * @class	GroundAttack
 *
 * @brief	�n�ʂ���˂��o���U�����s���N���X
 *
 */
	class GroundAttack : public ObjectBase
	{
	public:
		GroundAttack(int _x, int _y, int _angle, int _type);
		~GroundAttack();

		/**
		 * @fn	virtual OBJECT_TYPE GroundAttack::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::GROUNDATTACK; }

		/**
		 * @fn	void GroundAttack::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();

		/**
		 * @fn	void GroundAttack::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void GroundAttack::Draw(Game& _game) override;
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void GroundAttack::Hit(Game& _game);
		 *
		 * @brief	�����蔻�菈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Hit(Game& _game);

		/**
		 * @fn	void GroundAttack::SwitchDirection();
		 *
		 * @brief	�����ő�܂œ˂��o������A�������܂��鏈��
		 *
		 */
		void SwitchDirection();

		/**
		 * @fn	bool GroundAttack::IsHitToCircle(ObjectBase& _object);
		 *
		 * @brief	�~�Ǝl�p�̓����蔻�菈��
		 *
		 * @param [in,out]	_object	�I�u�W�F�N�g�x�[�X�N���X�̎Q��
		 *
		 * @returns	�v���C���[�Ɠ����蔻���
		 */
		bool IsHitToCircle(ObjectBase& _object);

		/**
		 * @fn	inline void GroundAttack::SetSpeed(int _speed)
		 *
		 * @brief	Sets a speed
		 *
		 * @param 	_speed	The speed.
		 */
		inline void SetSpeed(int _speed) { m_speed = _speed; }

		/**
		 * @fn	inline void GroundAttack::SetAngle(int _angle)
		 *
		 * @brief	�˂��o���p�x��ݒ�
		 *
		 * @param 	_angle	The angle.
		 */
		inline void SetAngle(int _angle) { m_angle = _angle; }

	private:
		int m_speed_x;
		int m_speed_y;
		int m_angle;

		float vector_x; //!< �p�x����Z�o����ړ��x�N�g��
		float vector_y;

		int m_stop_count;   //!< �ő�܂œ˂��o�����Ƃ��̎~�܂鎞��

		int hit_cx[18]; //!< �����蔻��̒��S���W
		int hit_cy[18];
		int hit_r[18];  //!< �����蔻��̔��a
		int hit_circle_num;
	};
}