/**
 * @file	AMG_Summer_Co_Production_2020\script\SPMove.h.
 *
 * @brief	�K�E�Z�I�u�W�F�N�g
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"
#include"../Sound/PlayWAVE.h"

namespace illumism
{
	/**
	 * @class	SPMove
	 *
	 * @brief	�K�E�Z�̃I�u�W�F�N�g�N���X
	 *
	 */
	class SPMove : public ObjectBase
	{
	public:
		SPMove(int _num);
		~SPMove();

		/**
		 * @fn	virtual ObjectBase::OBJECT_TYPE SPMove::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual ObjectBase::OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::SPMOVE; }

		/**
		 * @fn	void SPMove::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();

		/**
		 * @fn	void SPMove::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void SPMove::Damage(Game& _game);
		 *
		 * @brief	�I�u�W�F�N�g���폜
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Damage(Game& _game);

		/**
		 * @fn	void SPMove::Draw(Game& _game) override;
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void SPMove::SPMoveActivate(Game& _game, const int _startframe, const int _activetime);
		 *
		 * @brief	�K�E�Z�p�w�莞�ԓ������蔻���L���ɂ���
		 *
		 * @param [in,out]	_game	   	�Q�[���N���X�̎Q��
		 * @param 		  	_startframe	�����蔻���L���J�n����
		 * @param 		  	_activetime	�����蔻��L�����p�����鎞��
		 */
		void SPMoveActivate(Game& _game, const int _startframe, const int _activetime);

		/**
		 * @fn	void SPMove::SetDirection(Game& _game, int _num, bool _turn_flag) override;
		 *
		 * @brief	Sets a direction
		 *
		 * @param [in,out]	_game	  	�Q�[���N���X�̎Q��
		 * @param 		  	_num	  	�v���C���[�ԍ�
		 * @param 		  	_turn_flag	����������true
		 */
		void SetDirection(Game& _game, int _num, bool _turn_flag) override;
	};
}