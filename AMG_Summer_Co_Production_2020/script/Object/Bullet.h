/**
 * @file	AMG_Summer_Co_Production_2020\script\Bullet.h.
 *
 * @brief	�v���C���[�����˂���e��
 * @author	Takuya Fujisawa
 */

#pragma once
#include"ObjectBase.h"
#include"../Sound/PlayWAVE.h"

namespace illumism
{
	namespace
	{
		constexpr int BULLET_SPEED = 28;		//�e�ۃX�s�[�h
	}

	/**
	 * @class	Bullet
	 *
	 * @brief	�v���C���[�����˂���e�ۃI�u�W�F�N�g�̃N���X
	 *
	 */
	class Bullet : public ObjectBase
	{
	public:

		/**
		 * @fn	Bullet::Bullet(int _num);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_num	�v���C���[�ԍ�
		 */
		Bullet(int _num);
		~Bullet();

		/**
		 * @fn	virtual ObjectBase::OBJECT_TYPE Bullet::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual ObjectBase::OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::BULLET; }

		/**
		 * @fn	void Bullet::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();

		/**
		 * @fn	void Bullet::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void Bullet::Damage(Game& _game);
		 *
		 * @brief	�I�u�W�F�N�g������
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Damage(Game& _game);

		/**
		 * @fn	void Bullet::Draw(Game& _game) override;
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void Bullet::Hit(Game& _game);
		 *
		 * @brief	�e���m�̓����蔻��
		 *
		 * @param [in,out]	_game	The game.
		 */
		void Hit(Game& _game);

		/**
		 * @fn	void Bullet::SetDirection(Game& _game, int _num, bool _turn_flag) override;
		 *
		 * @brief	�e�𔭎˂�������Ɠ����蔻��̈ʒu��ݒ�
		 *
		 * @param [in,out]	_game	  		�Q�[���N���X�̎Q��
		 * @param 		  		_num	  		�v���C���[�ԍ�
		 * @param 		  		_turn_flag		����������true
		 */
		void SetDirection(Game& _game, int _num, bool _turn_flag) override;

	private:
		bool m_turn_flag = false;   //!< �摜�𔽓]���邩�ǂ����i��������true�j
	};
}