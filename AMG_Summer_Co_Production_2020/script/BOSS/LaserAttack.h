/**
 * @file	AMG_Summer_Co_Production_2020\script\LaserAttack.h.
 *
 * @brief	�v���C���[�Ɍ��������[�U�[�U������
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"
#include"DxLib.h"

namespace illumism
{
	/**
	  * @class	LaserAttack
	  *
	  * @brief	�v���C���[�Ɍ��������[�U�[�U�����s���N���X
	  *
	  */
	class LaserAttack : public ObjectBase
	{
	public:

		/**
		 * @fn	LaserAttack::LaserAttack(int _x,int _y,int _taget_x,int _target_y,int _speed);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_x		 	�{�X�̖ڂ�x���W
		 * @param 	_y		 	�{�X�̖ڂ�y���W
		 * @param 	_taget_x	�v���C���[��x���W
		 * @param 	_target_y	�v���C���[��y���W
		 * @param 	_speed   	���[�U�[�̈ڍs���x
		 */
		LaserAttack(int _x, int _y, int _taget_x, int _target_y, int _speed);
		~LaserAttack();

		/**
		 * @fn	virtual OBJECT_TYPE LaserAttack::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::LASER; }

		/**
		 * @fn	void LaserAttack::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();

		/**
		 * @fn	void LaserAttack::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void LaserAttack::Damage(Game& _game);
		 *
		 * @brief	�v���C���[�ɓ�����ƃI�u�W�F�N�g���폜
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Damage(Game& _game);

		/**
		 * @fn	void LaserAttack::Draw(Game& _game) override;
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void LaserAttack::Hit(Game& _game);
		 *
		 * @brief	�����蔻�菈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Hit(Game& _game);

		/**
		 * @fn	bool LaserAttack::IsHitToCircle(ObjectBase& _object);
		 *
		 * @brief	�~�Ǝl�p�̓����蔻�菈��
		 *
		 * @param [in,out]	_object	�I�u�W�F�N�g�x�[�X�N���X�̎Q��
		 *
		 * @returns	�v���C���[�Ƃ̓����蔻��̉�
		 */
		bool IsHitToCircle(ObjectBase& _object);

		/**
		 * @fn	void LaserAttack::OffScreen(Game& _game);
		 *
		 * @brief	��ʊO�ɓ��B������폜
		 *
		 * @param [in,out]	_game	The game.
		 */
		void OffScreen(Game& _game);

	private:
		VECTOR target;  //!< �ڕW�v���C���[�̍��W
		VECTOR position;	//!< �{�X�̖ڂ̍��W

		float m_speed_x, m_speed_y;
		double e_x, e_y;//!<�v���C���[�Ɍ������x�N�g���̐��K���ۑ��ϐ�
		double m_angle;

		int hit_r[3];   //!< �~�̓����蔻��p�p�����[�^
		int hit_cx[3];
		int hit_cy[3];
	};
}