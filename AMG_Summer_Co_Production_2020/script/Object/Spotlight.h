/**
 * @file	AMG_Summer_Co_Production_2020\script\Spotlight.h.
 *
 * @brief	�X�|�b�g���C�g�I�u�W�F�N�g
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ObjectBase.h"

namespace illumism
{
	/**
  * @class	Spotlight
  *
  * @brief	�Q�[���M�~�b�N�ł���X�|�b�g���C�g�̃N���X
  *
  */
	class Spotlight : public ObjectBase
	{
	public:
		/**
		 * @fn	Spotlight::Spotlight(int _num,int _move_time);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_num	  	�X�|�b�g���C�g�̐F�p�ϐ�
		 * @param 	_move_time	�ړ�����
		 */
		Spotlight(int _num, int _move_time);
		~Spotlight();

		/**
		 * @fn	virtual OBJECT_TYPE Spotlight::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual OBJECT_TYPE GetType() { return OBJECT_TYPE::NOHIT; }

		/**
		 * @fn	void Spotlight::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();

		/**
		 * @fn	void Spotlight::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void Spotlight::Damage(Game& _game);
		 *
		 * @brief	�I�u�W�F�N�g�̍폜
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Damage(Game& _game);

		/**
		 * @fn	void Spotlight::Draw(Game& _game) override;
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void Spotlight::SetSpeed(const int _speed)
		 *
		 * @brief	�ړ����x��ݒ�
		 *
		 * @param 	_speed	�ړ����x
		 */
		void SetSpeed(const int _speed) { m_speed = _speed; }

		/**
		 * @fn	void Spotlight::SetTime(const int _time)
		 *
		 * @brief	��~����܂ł̎��Ԃ�ݒ�
		 *
		 * @param 	_time	�ړ�����
		 */
		void SetTime(const int _time) { m_move_time = _time; }

		/**
		 * @fn	int Spotlight::Move();
		 *
		 * @brief	�ړ�������Ԃ�
		 *
		 * @returns	�ړ�����
		 */
		int Move();

	private:
		const int BODY_W = 1213;	//!< �ړ�����
		const int BODY_H = 1224;

		int m_move_x;   //!<	x�����̈ړ�����
		int m_move_time;	//!< �ړ�����

		ObjectBase* spotlight_hit;  //!< �X�|�b�g���C�g�̓����蔻��
	};
}