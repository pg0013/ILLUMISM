/**
 * @file	AMG_Summer_Co_Production_2020\script\Attack.h.
 *
 * @brief	�v���C���[��ATTACK�U���p�����蔻�菈��
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
	 * @class	Attack
	 *
	 * @brief	ATTACK�p�����蔻��̃N���X
	 *
	 */
	class Attack : public ObjectBase
	{
	public:

		/**
		 * @fn	Attack::Attack(int _player_num);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_player_num	�v���C���[�ԍ�
		 */
		Attack(int _player_num);
		~Attack();

		/**
		 * @fn	virtual ObjectBase::OBJECT_TYPE Attack::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual ObjectBase::OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::ATTACK; }

		/**
		 * @fn	void Attack::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();

		/**
		 * @fn	void Attack::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void Attack::Damage(Game& _game);
		 *
		 * @brief	�����蔻����폜
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Damage(Game& _game);

		/**
		 * @fn	void Attack::Draw(Game& _game) override;
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void Attack::AttackActivate(Game& _game,const int _startframe,const int _activetime);
		 *
		 * @brief	ATTACK�p�����蔻����w�莞�ԓ��L���ɂ���
		 *
		 * @param [in,out]	_game	   	�Q�[���N���X�̎Q��
		 * @param 		  	_startframe	�����蔻���L���J�n����
		 * @param 		  	_activetime	�����蔻��L�����p�����鎞��
		 */
		void AttackActivate(Game& _game, const int _startframe, const int _activetime);

		/**
		 * @fn	void Attack::SetDirection(Game& _game, int _num, bool _turn_flag) override;
		 *
		 * @brief	�����蔻����o��������ݒ�
		 *
		 * @param [in,out]	_game	  	�Q�[���N���X�̎Q��
		 * @param 		  	_num	  	�v���C���[�ԍ�
		 * @param 		  	_turn_flag	����������true
		 */
		void SetDirection(Game& _game, int _num, bool _turn_flag) override;
	};
}