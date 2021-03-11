/**
 * @file	AMG_Summer_Co_Production_2020\script\PointObject.h.
 *
 * @brief	�v���C���[��HP<0�ɂȂ������ɕ��o����|�C���g�I�u�W�F�N�g�̃N���X
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ObjectBase.h"

namespace illumism
{
	class Game;	//!<��d�C���N���[�h�h�~

	namespace
	{
		//��ԑJ�ڗp�ϐ�
		constexpr int DIFFUSION = 0;
		constexpr int VIBRATION = 1;
	}

	/**
	 * @class	PointObject
	 *
	 * @brief	�v���C���[��HP<0�ɂȂ������ɕ��o����|�C���g�I�u�W�F�N�g�̃N���X
	 *
	 */
	class PointObject : public ObjectBase
	{
	public:
		PointObject();
		~PointObject();

		/**
		 * @fn	virtual OBJECT_TYPE PointObject::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual OBJECT_TYPE GetType() { return OBJECT_TYPE::POINT; }

		/**
		 * @fn	void PointObject::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();

		/**
		 * @fn	void PointObject::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void PointObject::Diffusion(Game& _game);
		 *
		 * @brief	�|�C���g�I�u�W�F�N�g�̊g�U����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Diffusion(Game& _game);

		/**
		 * @fn	void PointObject::SimpleVibration(Game& _game);
		 *
		 * @brief	�|�C���g�I�u�W�F�N�g�̒P�U������
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void SimpleVibration(Game& _game);

		/**
		 * @fn	void PointObject::ApproachToPlayer(Game& _game);
		 *
		 * @brief	�v���C���[���߂Â�����v���C���[�ɋz���񂹂��鏈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void ApproachToPlayer(Game& _game);

		/**
		 * @fn	void PointObject::Draw(Game& _game) override;
		 *
		 * @brief	���Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void PointObject::Damage(Game& _game);
		 *
		 * @brief	�I�u�W�F�N�g������
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Damage(Game& _game);

		/**
		 * @fn	void PointObject::OffScreen();
		 *
		 * @brief	�v���C���[�ړ����������o�Ȃ�����
		 *
		 */
		void OffScreen();

	private:
		int m_diffusion_height;	//!<�U��΂鍂��
		int m_falling_speed_x;  //!< �������x
		int m_falling_speed_y;  //!< �������x
		int m_vibration_height; //!< �P�U���̎��̍���
		int m_object_state;		//!< �I�u�W�F�N�g���
	};
}